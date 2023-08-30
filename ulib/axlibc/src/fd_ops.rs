use crate::{
    ctypes,
    stdio_imp::{stdin, stdout},
    utils::e,
};
use arceos_posix_api::{syscall1, syscall2, syscall3, SyscallId};
use axerrno::LinuxError;
use axio::{Read, Write};
use core::ffi::{c_int, c_void};

pub const AX_FILE_LIMIT: usize = 1024;

/// Close a file by `fd`.
#[no_mangle]
pub unsafe extern "C" fn close(fd: c_int) -> c_int {
    e(syscall1(SyscallId::CLOSE, fd as usize))
}

/// Read data from the file indicated by `fd`.
///
/// Return the read size if success.
#[no_mangle]
pub unsafe extern "C" fn read(fd: c_int, buf: *mut c_void, count: usize) -> ctypes::ssize_t {
    if fd == 1 || fd == 2 {
        crate::errno::set_errno(LinuxError::EPERM as _);
        return -1;
    } else if fd == 0 {
        return ax_call_body!(read, {
            if buf.is_null() {
                return Err(LinuxError::EFAULT);
            }
            let dst = unsafe { core::slice::from_raw_parts_mut(buf as *mut u8, count) };
            let len = stdin().read(dst)?;
            Ok(len as ctypes::ssize_t)
        });
    }
    e(syscall3(
        SyscallId::READ,
        [fd as usize, buf as usize, count],
    )) as _
}

/// Write data to the file indicated by `fd`.
///
/// Return the written size if success.
#[no_mangle]
pub unsafe extern "C" fn write(fd: c_int, buf: *const c_void, count: usize) -> ctypes::ssize_t {
    if fd == 0 {
        crate::errno::set_errno(LinuxError::EPERM as _);
        return -1;
    } else if fd == 1 || fd == 2 {
        return ax_call_body!(write, {
            if buf.is_null() {
                return Err(LinuxError::EFAULT);
            }
            let bytes = unsafe { core::slice::from_raw_parts(buf as *const u8, count as _) };
            let len = stdout().write(bytes)?;
            Ok(len as ctypes::ssize_t)
        });
    }
    e(syscall3(
        SyscallId::WRITE,
        [fd as usize, buf as usize, count],
    )) as _
}

/// Get file metadata by `fd` and write into `buf`.
///
/// Return 0 if success.
#[no_mangle]
pub unsafe extern "C" fn fstat(fd: c_int, buf: *mut ctypes::stat) -> c_int {
    if fd == 0 {
        return ax_call_body!(fstat, {
            if buf.is_null() {
                return Err(LinuxError::EFAULT);
            }
            unsafe {
                *buf = stdin().stat()?;
            }
            Ok(0)
        });
    } else if fd == 1 || fd == 2 {
        return ax_call_body!(fstat, {
            if buf.is_null() {
                return Err(LinuxError::EFAULT);
            }
            unsafe {
                *buf = stdout().stat()?;
            }
            Ok(0)
        });
    }
    e(syscall2(SyscallId::FSTAT, [fd as usize, buf as usize])) as _
}

/// Duplicate a file descriptor
#[no_mangle]
pub unsafe extern "C" fn dup(old_fd: c_int) -> c_int {
    e(syscall1(SyscallId::DUP, old_fd as usize))
}

/// `dup3()` is the same as `dup2()`, except that:
///
/// The caller can force the close-on-exec flag to be set for the new file descriptor by specifying `O_CLOEXEC` in flags.
///
/// If oldfd equals newfd, then `dup3()` fails with the error `EINVAL`.
#[no_mangle]
pub unsafe extern "C" fn dup3(old_fd: c_int, new_fd: c_int, flags: c_int) -> c_int {
    e(syscall3(
        SyscallId::DUP3,
        [old_fd as usize, new_fd as usize, flags as usize],
    ))
}

/// Fcntl implementation
///
/// TODO: `SET/GET` command is ignored
#[no_mangle]
pub unsafe extern "C" fn ax_fcntl(fd: c_int, cmd: c_int, arg: usize) -> c_int {
    e(syscall3(SyscallId::FCNTL, [fd as usize, cmd as usize, arg]))
}
