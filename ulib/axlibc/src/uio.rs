use super::ctypes;
use crate::utils::e;
use arceos_posix_api::{syscall3, SyscallId};
use core::ffi::c_int;

/// `writev` implementation
#[no_mangle]
pub unsafe extern "C" fn writev(
    fd: c_int,
    iov: *const ctypes::iovec,
    iocnt: c_int,
) -> ctypes::ssize_t {
    e(syscall3(
        SyscallId::WRITEV,
        [fd as usize, iov as usize, iocnt as usize],
    )) as _
}
