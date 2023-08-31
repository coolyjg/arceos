use core::ffi::{c_int, c_void};

use arceos_posix_api::{ctypes, syscall2, syscall3, SyscallId};

use crate::utils::e;

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
pub unsafe extern "C" fn fstat(fd: c_int, buf: *mut ctypes::stat) -> c_int {
    e(syscall2(SyscallId::FSTAT, [fd as usize, buf as usize])) as _
}
