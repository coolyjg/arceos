use crate::{ctypes, utils::e};
use arceos_posix_api::{syscall1, syscall2, SyscallId};
use core::ffi::c_int;

/// Initialize a mutex.
#[no_mangle]
pub unsafe extern "C" fn pthread_mutex_init(
    mutex: *mut ctypes::pthread_mutex_t,
    attr: *const ctypes::pthread_mutexattr_t,
) -> c_int {
    e(syscall2(
        SyscallId::PTHREAD_MUTEX_INIT,
        [mutex as usize, attr as usize],
    ))
}

/// Lock the given mutex.
#[no_mangle]
pub unsafe extern "C" fn pthread_mutex_lock(mutex: *mut ctypes::pthread_mutex_t) -> c_int {
    e(syscall1(SyscallId::PTHREAD_MUTEX_LOCK, mutex as usize))
}

/// Unlock the given mutex.
#[no_mangle]
pub unsafe extern "C" fn pthread_mutex_unlock(mutex: *mut ctypes::pthread_mutex_t) -> c_int {
    e(syscall1(SyscallId::PTHREAD_MUTEX_UNLOCK, mutex as usize))
}
