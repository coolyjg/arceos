use arceos_posix_api::{syscall2, SyscallId};
use core::ffi::c_int;

use super::ctypes;
use crate::utils::e;

/// Get clock time since booting
#[no_mangle]
pub unsafe extern "C" fn clock_gettime(clk: ctypes::clockid_t, ts: *mut ctypes::timespec) -> c_int {
    e(syscall2(
        SyscallId::CLOCK_GETTIME,
        [clk as usize, ts as usize],
    ))
}

/// Sleep some nanoseconds
///
/// TODO: should be woken by signals, and set errno
#[no_mangle]
pub unsafe extern "C" fn nanosleep(
    req: *const ctypes::timespec,
    rem: *mut ctypes::timespec,
) -> c_int {
    e(syscall2(
        SyscallId::NANO_SLEEP,
        [req as usize, rem as usize],
    ))
}
