use crate::{ctypes, utils::e};
use arceos_posix_api::{sys_pthread_mutex_init, sys_pthread_mutex_lock, sys_pthread_mutex_unlock};
use core::ffi::c_int;

/// Initialize a mutex.
#[no_mangle]
pub unsafe extern "C" fn pthread_mutex_init(
    mutex: *mut ctypes::pthread_mutex_t,
    attr: *const ctypes::pthread_mutexattr_t,
) -> c_int {
    e(sys_pthread_mutex_init(mutex, attr))
}

/// Lock the given mutex.
#[no_mangle]
pub unsafe extern "C" fn pthread_mutex_lock(mutex: *mut ctypes::pthread_mutex_t) -> c_int {
    e(sys_pthread_mutex_lock(mutex))
}

/// Unlock the given mutex.
#[no_mangle]
pub unsafe extern "C" fn pthread_mutex_unlock(mutex: *mut ctypes::pthread_mutex_t) -> c_int {
    e(sys_pthread_mutex_unlock(mutex))
}
