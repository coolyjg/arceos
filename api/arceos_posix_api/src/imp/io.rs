use core::ffi::{c_int, c_void};

use crate::ctypes;

#[cfg(feature = "fd")]
use crate::imp::fd_ops::get_file_like;

use axerrno::LinuxError;
#[cfg(not(feature = "fd"))]
use axio::prelude::*;

/// Read data from the file indicated by `fd`.
///
/// Return the read size if success.
pub fn sys_read(fd: c_int, buf: *mut c_void, count: usize) -> ctypes::ssize_t {
    debug!("sys_read <= {} {:#x} {}", fd, buf as usize, count);
    syscall_body!(sys_read, {
        if buf.is_null() {
            return Err(LinuxError::EFAULT);
        }
        if (1..=2).contains(&fd) {
            return Err(LinuxError::EPERM);
        }
        let dst = unsafe { core::slice::from_raw_parts_mut(buf as *mut u8, count) };
        #[cfg(feature = "fd")]
        return Ok(get_file_like(fd)?.read(dst)? as ctypes::ssize_t);
        #[cfg(not(feature = "fd"))]
        match fd {
            0 => {
                let mut ss = crate::imp::stdio::stdin();
                Ok(ss.read(dst)? as ctypes::ssize_t)
            }
            _ => Err(LinuxError::EPERM),
        }
    })
}

/// Write data to the file indicated by `fd`.
///
/// Return the written size if success.
pub fn sys_write(fd: c_int, buf: *const c_void, count: usize) -> ctypes::ssize_t {
    debug!("sys_write <= {} {:#x} {}", fd, buf as usize, count);
    syscall_body!(sys_write, {
        if buf.is_null() {
            return Err(LinuxError::EFAULT);
        }
        if fd == 0 {
            return Err(LinuxError::EPERM);
        }
        let src = unsafe { core::slice::from_raw_parts(buf as *const u8, count) };
        #[cfg(feature = "fd")]
        return Ok(get_file_like(fd)?.write(src)? as ctypes::ssize_t);
        #[cfg(not(feature = "fd"))]
        {
            if (1..=2).contains(&fd) {
                let mut ss = crate::imp::stdio::stdout();
                Ok(ss.write(src)? as ctypes::ssize_t)
            } else {
                Err(LinuxError::EPERM)
            }
        }
    })
}

/// Get file metadata by `fd` and write into `buf`.
///
/// Return 0 if success.
pub fn sys_fstat(fd: c_int, buf: *mut ctypes::stat) -> c_int {
    debug!("sys_fstat <= {} {:#x}", fd, buf as usize);
    syscall_body!(sys_fstat, {
        if buf.is_null() {
            return Err(LinuxError::EFAULT);
        }
        #[cfg(feature = "fd")]
        {
            unsafe { *buf = get_file_like(fd)?.stat()? };
            return Ok(0);
        }
        #[cfg(not(feature = "fd"))]
        {
            if !(0..=2).contains(&fd) {
                return Err(LinuxError::EPERM);
            }
            let st_mode = if fd == 0 {
                0o20000 | 0o440u32
            } else if (1..=2).contains(&fd) {
                0o20000 | 0o220u32
            } else {
                0
            };
            unsafe {
                *buf = ctypes::stat {
                    st_ino: 1,
                    st_nlink: 1,
                    st_mode,
                    ..Default::default()
                };
            }
            return Ok(0);
        }
    })
}
