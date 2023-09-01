use core::ffi::{c_int, c_void};

use arceos_posix_api::{ctypes, sys_fstat, sys_read, sys_write, sys_writev};

use crate::utils::e;

/// Read data from the file indicated by `fd`.
///
/// Return the read size if success.
#[no_mangle]
pub unsafe extern "C" fn read(fd: c_int, buf: *mut c_void, count: usize) -> ctypes::ssize_t {
    e(sys_read(fd, buf, count) as _) as _
}

/// Write data to the file indicated by `fd`.
///
/// Return the written size if success.
#[no_mangle]
pub unsafe extern "C" fn ax_write(fd: c_int, buf: *const c_void, count: usize) -> ctypes::ssize_t {
    e(sys_write(fd, buf, count) as _) as _
}

/// Get file metadata by `fd` and write into `buf`.
///
/// Return 0 if success.
#[no_mangle]
pub unsafe extern "C" fn fstat(fd: c_int, buf: *mut ctypes::stat) -> c_int {
    e(sys_fstat(fd, buf))
}

/// `writev` implementation
#[no_mangle]
pub unsafe extern "C" fn writev(
    fd: c_int,
    iov: *const ctypes::iovec,
    iocnt: c_int,
) -> ctypes::ssize_t {
    e(sys_writev(fd, iov, iocnt) as _) as _
}
