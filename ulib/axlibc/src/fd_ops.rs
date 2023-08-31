use crate::utils::e;
use arceos_posix_api::{sys_close, sys_dup, sys_dup3, sys_fcntl};
use core::ffi::c_int;

pub const AX_FILE_LIMIT: usize = 1024;

/// Close a file by `fd`.
#[no_mangle]
pub unsafe extern "C" fn close(fd: c_int) -> c_int {
    e(sys_close(fd))
}

/// Duplicate a file descriptor
#[no_mangle]
pub unsafe extern "C" fn dup(old_fd: c_int) -> c_int {
    e(sys_dup(old_fd))
}

/// `dup3()` is the same as `dup2()`, except that:
///
/// The caller can force the close-on-exec flag to be set for the new file descriptor by specifying `O_CLOEXEC` in flags.
///
/// If oldfd equals newfd, then `dup3()` fails with the error `EINVAL`.
#[no_mangle]
pub unsafe extern "C" fn dup3(old_fd: c_int, new_fd: c_int, flags: c_int) -> c_int {
    e(sys_dup3(old_fd, new_fd, flags))
}

/// Fcntl implementation
///
/// TODO: `SET/GET` command is ignored
#[no_mangle]
pub unsafe extern "C" fn ax_fcntl(fd: c_int, cmd: c_int, arg: usize) -> c_int {
    e(sys_fcntl(fd, cmd, arg))
}
