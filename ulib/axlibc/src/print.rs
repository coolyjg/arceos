use core::ffi::{c_char, c_int};

use arceos_posix_api::{syscall3, Mutex, SyscallId};
use axerrno::LinuxError;

use crate::utils::e;

/// Print a string to the global standard output stream.
#[no_mangle]
pub unsafe extern "C" fn print_str(buf: *const c_char, count: usize) -> c_int {
    if buf.is_null() {
        crate::errno::set_errno(LinuxError::EFAULT as _);
        return -1;
    }
    e(syscall3(SyscallId::WRITE, [1usize, buf as usize, count])) as _
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
    let len = e(syscall3(SyscallId::WRITE, [1usize, buf as usize, count])) as _;
    if len > 0 {
        let brk = b"\n";
        e(syscall3(
            SyscallId::WRITE,
            [1usize, brk.as_ptr() as usize, 1],
        ));
        len
    } else {
        1
    }
}
