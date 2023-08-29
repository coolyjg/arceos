use crate::{ctypes, utils::e};
use arceos_posix_api::{syscall1, syscall2, syscall3, SyscallId};
use core::ffi::{c_int, c_void};

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
    e(syscall3(
        SyscallId::WRITE,
        [fd as usize, buf as usize, count],
    )) as _
}

/// Get file metadata by `fd` and write into `buf`.
///
/// Return 0 if success.
#[no_mangle]
pub unsafe extern "C" fn fstat(fd: c_int, buf: *mut ctypes::stat) -> ctypes::ssize_t {
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
