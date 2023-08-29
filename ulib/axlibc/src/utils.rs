#![allow(dead_code)]
#![allow(unused_macros)]

use axerrno::{LinuxError, LinuxResult};
use core::ffi::{c_char, c_int, CStr};

pub fn char_ptr_to_str<'a>(str: *const c_char) -> LinuxResult<&'a str> {
    if str.is_null() {
        Err(LinuxError::EFAULT)
    } else {
        unsafe { CStr::from_ptr(str) }
            .to_str()
            .map_err(|_| LinuxError::EINVAL)
    }
}

pub fn check_null_ptr<T>(ptr: *const T) -> LinuxResult {
    if ptr.is_null() {
        Err(LinuxError::EFAULT)
    } else {
        Ok(())
    }
}

pub fn check_null_mut_ptr<T>(ptr: *mut T) -> LinuxResult {
    if ptr.is_null() {
        Err(LinuxError::EFAULT)
    } else {
        Ok(())
    }
}

// TODO: parse errno more elegantly
const ERRNO_MAX: usize = 4095;

pub fn e(ret: usize) -> c_int {
    // if syscall return -4094 ~ -1
    if ret > ERRNO_MAX.wrapping_neg() {
        crate::errno::set_errno((ret as i32).abs());
        -1
    } else {
        ret as _
    }
}

macro_rules! ax_call_body {
    ($fn: ident, $($stmt: tt)*) => {{
        #[allow(clippy::redundant_closure_call)]
        let res = (|| -> axerrno::LinuxResult<_> { $($stmt)* })();
        match res {
            Ok(_) | Err(axerrno::LinuxError::EAGAIN) => debug!(concat!(stringify!($fn), " => {:?}"),  res),
            Err(_) => info!(concat!(stringify!($fn), " => {:?}"), res),
        }
        match res {
            Ok(v) => v as _,
            Err(e) => {
                crate::errno::set_errno(e.code());
                -1 as _
            }
        }
    }};
}

macro_rules! ax_call_body_no_debug {
    ($($stmt: tt)*) => {{
        #[allow(clippy::redundant_closure_call)]
        let res = (|| -> axerrno::LinuxResult<_> { $($stmt)* })();
        match res {
            Ok(v) => v as _,
            Err(e) => {
                crate::errno::set_errno(e.code());
                -1 as _
            }
        }
    }};
}
