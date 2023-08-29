use core::ffi::c_int;

use arceos_posix_api::{syscall1, SyscallId};

use crate::utils::e;

/// Create a pipe
///
/// Return 0 if succeed
#[no_mangle]
pub unsafe extern "C" fn pipe(fd: *mut c_int) -> c_int {
    e(syscall1(SyscallId::PIPE, fd as usize))
}
