use crate::{ctypes, utils::e};
use arceos_posix_api::sys_select;
use axerrno::LinuxError;
use core::ffi::{c_int, c_long};

/// Monitor multiple file descriptors, waiting until one or more of the file descriptors become "ready" for some class of I/O operation
#[no_mangle]
pub unsafe extern "C" fn select(
    nfds: c_int,
    readfds: *mut ctypes::fd_set,
    writefds: *mut ctypes::fd_set,
    exceptfds: *mut ctypes::fd_set,
    timeout: *mut ctypes::timeval,
) -> c_int {
    let (mut s, mut us): (ctypes::time_t, c_long) = if !timeout.is_null() {
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
