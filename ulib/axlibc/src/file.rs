use core::ffi::{c_char, c_int};

use arceos_posix_api::{syscall2, syscall3, SyscallId};

use crate::{ctypes, utils::e};

/// Open a file by `filename` and insert it into the file descriptor table.
///
/// Return its index in the file table (`fd`). Return `EMFILE` if it already
/// has the maximum number of files open.
#[no_mangle]
pub unsafe extern "C" fn ax_open(
    filename: *const c_char,
    flags: c_int,
    mode: ctypes::mode_t,
) -> c_int {
    e(syscall3(
        SyscallId::OPEN,
        [filename as usize, flags as usize, mode as usize],
    ))
}

/// Set the position of the file indicated by `fd`.
///
/// Return its position after seek.
#[no_mangle]
pub unsafe extern "C" fn lseek(fd: c_int, offset: ctypes::off_t, whence: c_int) -> ctypes::off_t {
    e(syscall3(
        SyscallId::LSEEK,
        [fd as usize, offset as usize, whence as usize],
    )) as _
}

/// Get the file metadata by `path` and write into `buf`.
///
/// Return 0 if success.
#[no_mangle]
pub unsafe extern "C" fn stat(path: *const c_char, buf: *mut ctypes::stat) -> c_int {
    e(syscall2(SyscallId::STAT, [path as usize, buf as usize])) as _
}

/// Get the metadata of the symbolic link and write into `buf`.
///
/// Return 0 if success.
#[no_mangle]
pub unsafe extern "C" fn lstat(path: *const c_char, buf: *mut ctypes::stat) -> c_int {
    e(syscall2(SyscallId::LSTAT, [path as usize, buf as usize])) as _
}

/// Get the path of the current directory.
#[no_mangle]
pub unsafe extern "C" fn getcwd(buf: *mut c_char, size: usize) -> *mut c_char {
    e(syscall2(SyscallId::GETCWD, [buf as usize, size])) as _
}

/// Rename `old` to `new`
/// If new exists, it is first removed.
///
/// Return 0 if the operation succeeds, otherwise return -1.
#[no_mangle]
pub unsafe extern "C" fn ax_rename(old: *const c_char, new: *const c_char) -> c_int {
    e(syscall2(SyscallId::RENAME, [old as usize, new as usize]))
}
