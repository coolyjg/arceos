use crate::{ctypes, utils::e};
use arceos_posix_api::{syscall5, SyscallId};
use core::ffi::c_int;

/// Monitor multiple file descriptors, waiting until one or more of the file descriptors become "ready" for some class of I/O operation
#[no_mangle]
pub unsafe extern "C" fn ax_select(
    nfds: c_int,
    readfds: *mut ctypes::fd_set,
    writefds: *mut ctypes::fd_set,
    exceptfds: *mut ctypes::fd_set,
    timeout: *mut ctypes::timeval,
) -> c_int {
    e(syscall5(
        SyscallId::SELECT,
        [
            nfds as usize,
            readfds as usize,
            writefds as usize,
            exceptfds as usize,
            timeout as usize,
        ],
    ))
}
