use crate::utils::e;
use arceos_posix_api::{
    ctypes, sys_pthread_create, sys_pthread_exit, sys_pthread_join, sys_pthread_self,
};
use core::ffi::{c_int, c_void};

pub mod mutex;

/// Returns the `pthread` struct of current thread.
#[no_mangle]
pub unsafe extern "C" fn pthread_self() -> ctypes::pthread_t {
    sys_pthread_self()
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
    e(sys_pthread_create(res, attr, start_routine, arg))
}

/// Exits the current thread. The value `retval` will be returned to the joiner.
#[no_mangle]
pub unsafe extern "C" fn pthread_exit(retval: *mut c_void) -> ! {
    sys_pthread_exit(retval)
}

/// Waits for the given thread to exit, and stores the return value in `retval`.
#[no_mangle]
pub unsafe extern "C" fn pthread_join(
    thread: ctypes::pthread_t,
    retval: *mut *mut c_void,
) -> c_int {
    e(sys_pthread_join(thread, retval))
}
