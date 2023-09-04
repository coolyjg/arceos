use crate::{ctypes, utils::e};

use core::ffi::c_int;

#[cfg(feature = "epoll")]
use arceos_posix_api::{sys_epoll_create, sys_epoll_ctl, sys_epoll_wait};
#[cfg(feature = "select")]
use {arceos_posix_api::sys_select, axerrno::LinuxError};

/// `epoll_create()` creates a new epoll instance.
///
/// `epoll_create()` returns a file descriptor referring to the new epoll instance.
#[cfg(feature = "epoll")]
#[no_mangle]
pub unsafe extern "C" fn epoll_create(size: c_int) -> c_int {
    e(sys_epoll_create(size))
}

/// Control interface for an epoll file descriptor
#[cfg(feature = "epoll")]
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
#[cfg(feature = "epoll")]
#[no_mangle]
pub unsafe extern "C" fn epoll_wait(
    epfd: c_int,
    events: *mut ctypes::epoll_event,
    maxevents: c_int,
    timeout: c_int,
) -> c_int {
    e(sys_epoll_wait(epfd, events, maxevents, timeout))
}

/// Monitor multiple file descriptors, waiting until one or more of the file descriptors become "ready" for some class of I/O operation
#[cfg(feature = "select")]
#[no_mangle]
pub unsafe extern "C" fn select(
    nfds: c_int,
    readfds: *mut ctypes::fd_set,
    writefds: *mut ctypes::fd_set,
    exceptfds: *mut ctypes::fd_set,
    timeout: *mut ctypes::timeval,
) -> c_int {
    let (mut s, mut us): (ctypes::time_t, core::ffi::c_long) = if !timeout.is_null() {
        ((*timeout).tv_sec, (*timeout).tv_usec)
    } else {
        (0, 0)
    };
    let max_time: ctypes::time_t =
        ((1u64 << (8 * core::mem::size_of::<ctypes::time_t>() - 1)) - 1) as _;
    if s < 0 || us < 0 {
        crate::errno::set_errno(LinuxError::EINVAL as _);
        return -1;
    }
    if us / 1_000_000 > max_time - s {
        s = max_time;
        us = 999999;
    } else {
        s += us / 1_000_000;
        us %= 1_000_000;
    }
    if !timeout.is_null() {
        (*timeout).tv_sec = s;
        (*timeout).tv_usec = us;
    }
    e(sys_select(nfds, readfds, writefds, exceptfds, timeout))
}
