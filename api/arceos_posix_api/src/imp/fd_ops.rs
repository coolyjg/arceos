use alloc::sync::Arc;
use core::ffi::{c_int, c_void};

use axerrno::{LinuxError, LinuxResult};
use axio::PollState;

use flatten_objects::FlattenObjects;
use spin::RwLock;

use super::ctypes;
// use super::stdio::{stdin, stdout};

pub const AX_FILE_LIMIT: usize = 1024;

pub trait FileLike: Send + Sync {
    fn read(&self, buf: &mut [u8]) -> LinuxResult<usize>;
    fn write(&self, buf: &[u8]) -> LinuxResult<usize>;
    fn stat(&self) -> LinuxResult<ctypes::stat>;
    fn into_any(self: Arc<Self>) -> Arc<dyn core::any::Any + Send + Sync>;
    fn poll(&self) -> LinuxResult<PollState>;
    fn set_nonblocking(&self, nonblocking: bool) -> LinuxResult;
}

struct Dummy;

impl FileLike for Dummy {
    fn read(&self, _buf: &mut [u8]) -> LinuxResult<usize> {
        Err(LinuxError::EPERM)
    }

    fn write(&self, _buf: &[u8]) -> LinuxResult<usize> {
        Err(LinuxError::EPERM)
    }

    fn stat(&self) -> LinuxResult<ctypes::stat> {
        Err(LinuxError::EPERM)
    }

    fn into_any(self: Arc<Self>) -> Arc<dyn core::any::Any + Send + Sync> {
        self
    }

    fn poll(&self) -> LinuxResult<PollState> {
        Err(LinuxError::EPERM)
    }

    fn set_nonblocking(&self, _nonblocking: bool) -> LinuxResult {
        Ok(())
    }
}

lazy_static::lazy_static! {
    static ref FD_TABLE: RwLock<FlattenObjects<Arc<dyn FileLike>, AX_FILE_LIMIT>> = {
        let mut fd_table = FlattenObjects::new();
        fd_table.add_at(0, Arc::new(Dummy) as _).unwrap(); // stdin
        fd_table.add_at(1, Arc::new(Dummy) as _).unwrap(); // stdout
        fd_table.add_at(2, Arc::new(Dummy) as _).unwrap(); // stderr
        RwLock::new(fd_table)
    };
}

pub fn get_file_like(fd: c_int) -> LinuxResult<Arc<dyn FileLike>> {
    FD_TABLE
        .read()
        .get(fd as usize)
        .cloned()
        .ok_or(LinuxError::EBADF)
}

pub fn add_file_like(f: Arc<dyn FileLike>) -> LinuxResult<c_int> {
    Ok(FD_TABLE.write().add(f).ok_or(LinuxError::EMFILE)? as c_int)
}

pub fn close_file_like(fd: c_int) -> LinuxResult {
    let f = FD_TABLE
        .write()
        .remove(fd as usize)
        .ok_or(LinuxError::EBADF)?;
    drop(f);
    Ok(())
}

/// Close a file by `fd`.
#[no_mangle]
pub unsafe extern "C" fn sys_close(fd: c_int) -> c_int {
    debug!("sys_close <= {}", fd);
    if (0..=2).contains(&fd) {
        return 0; // stdin, stdout, stderr
    }
    syscall_body!(sys_close, close_file_like(fd).map(|_| 0))
}

/// Read data from the file indicated by `fd`.
///
/// Return the read size if success.
#[no_mangle]
pub unsafe extern "C" fn sys_read(fd: c_int, buf: *mut c_void, count: usize) -> ctypes::ssize_t {
    debug!("sys_read <= {} {:#x} {}", fd, buf as usize, count);
    syscall_body!(sys_read, {
        if buf.is_null() {
            return Err(LinuxError::EFAULT);
        }
        let dst = unsafe { core::slice::from_raw_parts_mut(buf as *mut u8, count) };
        get_file_like(fd)?.read(dst)
    })
}

/// Write data to the file indicated by `fd`.
///
/// Return the written size if success.
#[no_mangle]
pub unsafe extern "C" fn sys_write(fd: c_int, buf: *const c_void, count: usize) -> ctypes::ssize_t {
    debug!("sys_write <= {} {:#x} {}", fd, buf as usize, count);
    syscall_body!(sys_write, {
        if buf.is_null() {
            return Err(LinuxError::EFAULT);
        }
        let src = unsafe { core::slice::from_raw_parts(buf as *const u8, count) };
        get_file_like(fd)?.write(src)
    })
}

/// Get file metadata by `fd` and write into `buf`.
///
/// Return 0 if success.
#[no_mangle]
pub unsafe extern "C" fn sys_fstat(fd: c_int, buf: *mut ctypes::stat) -> ctypes::ssize_t {
    debug!("sys_fstat <= {} {:#x}", fd, buf as usize);
    syscall_body!(sys_fstat, {
        if buf.is_null() {
            return Err(LinuxError::EFAULT);
        }
        unsafe { *buf = get_file_like(fd)?.stat()? };
        Ok(0)
    })
}

fn dup_fd(old_fd: c_int) -> LinuxResult<c_int> {
    let f = get_file_like(old_fd)?;
    let new_fd = add_file_like(f)?;
    Ok(new_fd)
}

/// Duplicate a file descriptor
#[no_mangle]
pub unsafe extern "C" fn sys_dup(old_fd: c_int) -> c_int {
    debug!("sys_dup <= {}", old_fd);
    syscall_body!(sys_dup, dup_fd(old_fd))
}

/// `dup3()` is the same as `dup2()`, except that:
///
/// The caller can force the close-on-exec flag to be set for the new file descriptor by specifying `O_CLOEXEC` in flags.
///
/// If oldfd equals newfd, then `dup3()` fails with the error `EINVAL`.
#[no_mangle]
pub unsafe extern "C" fn sys_dup3(old_fd: c_int, new_fd: c_int, flags: c_int) -> c_int {
    debug!(
        "sys_dup3 <= old_fd: {}, new_fd: {}, flags: {}",
        old_fd, new_fd, flags
    );

    syscall_body!(sys_dup3, {
        if old_fd == new_fd {
            return Err(LinuxError::EINVAL);
        }
        if new_fd as usize >= AX_FILE_LIMIT {
            return Err(LinuxError::EBADF);
        }

        let f = get_file_like(old_fd)?;
        FD_TABLE
            .write()
            .add_at(new_fd as usize, f)
            .ok_or(LinuxError::EMFILE)?;

        if flags as u32 & ctypes::O_CLOEXEC != 0 {
            sys_fcntl(
                new_fd,
                ctypes::F_SETFD as c_int,
                ctypes::FD_CLOEXEC as usize,
            );
        }
        Ok(new_fd)
    })
}

/// Fcntl implementation
///
/// TODO: `SET/GET` command is ignored, hard-code stdin/stdout
#[no_mangle]
pub unsafe extern "C" fn sys_fcntl(fd: c_int, cmd: c_int, arg: usize) -> c_int {
    debug!("sys_fcntl <= fd: {} cmd: {} arg: {}", fd, cmd, arg);
    syscall_body!(sys_fcntl, {
        match cmd as u32 {
            ctypes::F_DUPFD => dup_fd(fd),
            ctypes::F_DUPFD_CLOEXEC => {
                // TODO: Change fd flags
                dup_fd(fd)
            }
            ctypes::F_SETFL => {
                if fd == 0 || fd == 1 || fd == 2 {
                    return Ok(0);
                }
                get_file_like(fd)?.set_nonblocking(arg & (ctypes::O_NONBLOCK as usize) > 0)?;
                Ok(0)
            }
            _ => {
                warn!("unsupported fcntl parameters: cmd {}", cmd);
                Ok(0)
            }
        }
    })
}
