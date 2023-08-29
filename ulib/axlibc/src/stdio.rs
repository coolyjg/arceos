use core::ffi::{c_char, c_int};

use axerrno::LinuxError;
use axstd::io::{self, Write};

/// Print a string to the global standard output stream.
#[no_mangle]
pub unsafe extern "C" fn ax_print_str(buf: *const c_char, count: usize) -> c_int {
    ax_call_body_no_debug!({
        if buf.is_null() {
            return Err(LinuxError::EFAULT);
        }

        let bytes = unsafe { core::slice::from_raw_parts(buf as *const u8, count as _) };
        let len = io::stdout().write(bytes)?;
        Ok(len as c_int)
    })
}

/// Print a string to the global standard output stream. Add a line break.
#[no_mangle]
pub unsafe extern "C" fn ax_println_str(buf: *const c_char, count: usize) -> c_int {
    ax_call_body_no_debug!({
        if buf.is_null() {
            return Err(LinuxError::EFAULT);
        }

        let bytes = unsafe { core::slice::from_raw_parts(buf as *const u8, count as _) };
        let mut stdout = io::stdout().lock();
        let len = stdout.write(bytes)?;
        let len = stdout.write(b"\n")? + len;
        Ok(len as c_int)
    })
}
