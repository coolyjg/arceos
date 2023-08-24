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

pub fn e(ret: c_int) -> c_int {
    if ret < 0 {
        crate::errno::set_errno(ret.abs());
        -1
    } else {
        ret as _
    }
}
