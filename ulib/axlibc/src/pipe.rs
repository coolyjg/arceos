use core::ffi::c_int;

use arceos_posix_api::sys_pipe;

use crate::utils::e;

/// Create a pipe
///
/// Return 0 if succeed
#[no_mangle]
pub unsafe extern "C" fn pipe(fd: *mut c_int) -> c_int {
    e(sys_pipe(fd))
}
