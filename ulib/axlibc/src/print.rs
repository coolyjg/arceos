use core::ffi::{c_char, c_int, c_void};

use arceos_posix_api::{sys_write, Mutex};
use axerrno::LinuxError;

use crate::utils::e;

/// Print a string to the global standard output stream.
#[no_mangle]
pub unsafe extern "C" fn print_str(buf: *const c_char, count: usize) -> c_int {
    if buf.is_null() {
        crate::errno::set_errno(LinuxError::EFAULT as _);
        return -1;
    }
    e(sys_write(1 as c_int, buf as *const c_void, count) as _)
}

static LOCK: Mutex<()> = Mutex::new(());

/// Print a string to the global standard output stream. Add a line break.
#[no_mangle]
pub unsafe extern "C" fn println_str(buf: *const c_char, count: usize) -> c_int {
    if buf.is_null() {
        crate::errno::set_errno(LinuxError::EFAULT as _);
        return -1;
    }

    let _lock = LOCK.lock();
    let len = e(sys_write(1 as c_int, buf as *const c_void, count) as _);
    if len > 0 {
        let brk = b"\n";
        e(sys_write(1 as c_int, brk.as_ptr() as *const c_void, count) as _);
        len
    } else {
        -1
    }
}
