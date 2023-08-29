use axerrno::LinuxError;
use core::ffi::{c_int, c_long};
use core::time::Duration;

use super::ctypes;

impl From<ctypes::timespec> for Duration {
    fn from(ts: ctypes::timespec) -> Self {
        Duration::new(ts.tv_sec as u64, ts.tv_nsec as u32)
    }
}

impl From<ctypes::timeval> for Duration {
    fn from(tv: ctypes::timeval) -> Self {
        Duration::new(tv.tv_sec as u64, tv.tv_usec as u32 * 1000)
    }
}

impl From<Duration> for ctypes::timespec {
    fn from(d: Duration) -> Self {
        ctypes::timespec {
            tv_sec: d.as_secs() as c_long,
            tv_nsec: d.subsec_nanos() as c_long,
        }
    }
}

impl From<Duration> for ctypes::timeval {
    fn from(d: Duration) -> Self {
        ctypes::timeval {
            tv_sec: d.as_secs() as c_long,
            tv_usec: d.subsec_micros() as c_long,
        }
    }
}

/// Get clock time since booting
#[no_mangle]
pub unsafe extern "C" fn sys_clock_gettime(
    _clk: ctypes::clockid_t,
    ts: *mut ctypes::timespec,
) -> c_int {
    syscall_body!(sys_clock_gettime, {
        if ts.is_null() {
            return Err(LinuxError::EFAULT);
        }
        let now = axhal::time::current_time().into();
        unsafe { *ts = now };
        debug!("sys_clock_gettime: {}.{:09}s", now.tv_sec, now.tv_nsec);
        Ok(0)
    })
}

/// Sleep some nanoseconds
///
/// TODO: should be woken by signals, and set errno
#[no_mangle]
pub unsafe extern "C" fn sys_nanosleep(
    req: *const ctypes::timespec,
    rem: *mut ctypes::timespec,
) -> c_int {
    syscall_body!(sys_nanosleep, {
        if req.is_null() || (*req).tv_nsec < 0 || (*req).tv_nsec > 999999999 {
            return Err(LinuxError::EINVAL);
        }

        debug!("sys_nanosleep <= {}.{:09}s", (*req).tv_sec, (*req).tv_nsec);
        let dur = Duration::from(*req);

        let now = axhal::time::current_time();
        super::task::sys_sleep_until(axhal::time::current_time() + dur);
        let after = axhal::time::current_time();
        let actual = after - now;

        if let Some(diff) = dur.checked_sub(actual) {
            if !rem.is_null() {
                unsafe { (*rem) = diff.into() };
            }
            return Err(LinuxError::EINTR);
        }
        Ok(0)
    })
}
