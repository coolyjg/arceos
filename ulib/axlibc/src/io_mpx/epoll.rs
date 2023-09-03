//! `epoll` implementation.
//!
//! TODO: do not support `EPOLLET` flag
use crate::{ctypes, utils::e};
use arceos_posix_api::{sys_epoll_create, sys_epoll_ctl, sys_epoll_wait};
use core::ffi::c_int;

/// `epoll_create()` creates a new epoll instance.
///
/// `epoll_create()` returns a file descriptor referring to the new epoll instance.
#[no_mangle]
pub unsafe extern "C" fn epoll_create(size: c_int) -> c_int {
    e(sys_epoll_create(size))
}

/// Control interface for an epoll file descriptor
#[no_mangle]
pub unsafe extern "C" fn epoll_ctl(
    epfd: c_int,
    op: c_int,
    fd: c_int,
    event: *mut ctypes::epoll_event,
) -> c_int {
    e(sys_epoll_ctl(epfd, op, fd, event))
}

/// `epoll_wait()` waits for events on the epoll instance referred to by the file descriptor epfd.
#[no_mangle]
pub unsafe extern "C" fn epoll_wait(
    epfd: c_int,
    events: *mut ctypes::epoll_event,
    maxevents: c_int,
    timeout: c_int,
) -> c_int {
    e(sys_epoll_wait(epfd, events, maxevents, timeout))
}
