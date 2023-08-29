//! `epoll` implementation.
//!
//! TODO: do not support `EPOLLET` flag
use crate::{ctypes, utils::e};
use arceos_posix_api::{syscall1, syscall4, SyscallId};
use core::ffi::c_int;

/// `epoll_create()` creates a new epoll instance.
///
/// `epoll_create()` returns a file descriptor referring to the new epoll instance.
#[no_mangle]
pub unsafe extern "C" fn epoll_create(size: c_int) -> c_int {
    e(syscall1(SyscallId::EPOLL_CREATE, size as usize))
}

/// Control interface for an epoll file descriptor
#[no_mangle]
pub unsafe extern "C" fn epoll_ctl(
    epfd: c_int,
    op: c_int,
    fd: c_int,
    event: *mut ctypes::epoll_event,
) -> c_int {
    e(syscall4(
        SyscallId::EPOLL_CTL,
        [epfd as usize, op as usize, fd as usize, event as usize],
    ))
}

/// `epoll_wait()` waits for events on the epoll instance referred to by the file descriptor epfd.
#[no_mangle]
pub unsafe extern "C" fn epoll_wait(
    epfd: c_int,
    events: *mut ctypes::epoll_event,
    maxevents: c_int,
    timeout: c_int,
) -> c_int {
    e(syscall4(
        SyscallId::EPOLL_WAIT,
        [
            epfd as usize,
            events as usize,
            maxevents as usize,
            timeout as usize,
        ],
    ))
}
