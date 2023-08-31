use crate::utils::e;
use arceos_posix_api::{ctypes, sys_writev};
use core::ffi::c_int;

/// `writev` implementation
#[no_mangle]
pub unsafe extern "C" fn writev(
    fd: c_int,
    iov: *const ctypes::iovec,
    iocnt: c_int,
) -> ctypes::ssize_t {
    e(sys_writev(fd, iov, iocnt) as _) as _
}
