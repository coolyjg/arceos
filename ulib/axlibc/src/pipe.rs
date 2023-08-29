use core::ffi::c_int;

use arceos_posix_api::{syscall2, SyscallId};

use crate::utils::e;

/// Create a pipe
///
/// Return 0 if succeed
#[no_mangle]
pub unsafe extern "C" fn pipe(fd1: *mut c_int, fd2: *mut c_int) -> c_int {
    e(syscall2(SyscallId::PIPE, [fd1 as usize, fd2 as usize]))
}
