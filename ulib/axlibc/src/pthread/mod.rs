use crate::{ctypes, utils::e};
use arceos_posix_api::{syscall0, syscall1, syscall2, syscall4, SyscallId};
use core::ffi::{c_int, c_void};

pub mod mutex;

/// Get current thread ID.
#[no_mangle]
pub unsafe extern "C" fn getpid() -> c_int {
    #[cfg(not(feature = "multitask"))]
    return 2; // `Main` task ID
    #[cfg(feature = "multitask")]
    e(syscall0(SyscallId::GETPID))
}

/// Returns the `pthread` struct of current thread.
#[no_mangle]
pub unsafe extern "C" fn pthread_self() -> ctypes::pthread_t {
    e(syscall0(SyscallId::PTHREAD_SELF)) as ctypes::pthread_t
}

/// Create a new thread with the given entry point and argument.
///
/// If successful, it stores the pointer to the newly created `struct __pthread`
/// in `res` and returns 0.
#[no_mangle]
pub unsafe extern "C" fn pthread_create(
    res: *mut ctypes::pthread_t,
    attr: *const ctypes::pthread_attr_t,
    start_routine: extern "C" fn(arg: *mut c_void) -> *mut c_void,
    arg: *mut c_void,
) -> c_int {
    e(syscall4(
        SyscallId::PTHREAD_CREATE,
        [
            res as usize,
            attr as usize,
            start_routine as usize,
            arg as usize,
        ],
    ))
}

/// Exits the current thread. The value `retval` will be returned to the joiner.
#[no_mangle]
pub unsafe extern "C" fn pthread_exit(retval: *mut c_void) -> ! {
    e(syscall1(SyscallId::PTHREAD_EXIT, retval as usize));
    unreachable!()
}

/// Waits for the given thread to exit, and stores the return value in `retval`.
#[no_mangle]
pub unsafe extern "C" fn pthread_join(
    thread: ctypes::pthread_t,
    retval: *mut *mut c_void,
) -> c_int {
    e(syscall2(
        SyscallId::PTHREAD_JOIN,
        [thread as usize, retval as usize],
    ))
}
