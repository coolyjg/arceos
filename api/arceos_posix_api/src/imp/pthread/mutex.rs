use crate::imp::sync::Mutex;
use crate::{ctypes, utils::check_null_mut_ptr};
use axerrno::LinuxResult;
use core::ffi::c_int;
use core::mem::ManuallyDrop;

#[repr(C)]
pub struct PthreadMutex(Mutex<()>);

impl PthreadMutex {
    const fn new() -> Self {
        Self(Mutex::new(()))
    }

    fn lock(&self) -> LinuxResult {
        let _guard = ManuallyDrop::new(self.0.lock());
        Ok(())
    }

    fn unlock(&self) -> LinuxResult {
        unsafe { self.0.force_unlock() };
        Ok(())
    }
}

/// Initialize a mutex.
#[no_mangle]
pub unsafe extern "C" fn sys_pthread_mutex_init(
    mutex: *mut ctypes::pthread_mutex_t,
    _attr: *const ctypes::pthread_mutexattr_t,
) -> c_int {
    debug!("sys_pthread_mutex_init <= {:#x}", mutex as usize);
    syscall_body!(sys_pthread_mutex_init, {
        check_null_mut_ptr(mutex)?;
        mutex.cast::<PthreadMutex>().write(PthreadMutex::new());
        Ok(0)
    })
}

/// Lock the given mutex.
#[no_mangle]
pub unsafe extern "C" fn sys_pthread_mutex_lock(mutex: *mut ctypes::pthread_mutex_t) -> c_int {
    debug!("sys_pthread_mutex_lock <= {:#x}", mutex as usize);
    syscall_body!(sys_pthread_mutex_lock, {
        check_null_mut_ptr(mutex)?;
        (*mutex.cast::<PthreadMutex>()).lock()?;
        Ok(0)
    })
}

/// Unlock the given mutex.
#[no_mangle]
pub unsafe extern "C" fn sys_pthread_mutex_unlock(mutex: *mut ctypes::pthread_mutex_t) -> c_int {
    debug!("sys_pthread_mutex_unlock <= {:#x}", mutex as usize);
    syscall_body!(sys_pthread_mutex_unlock, {
        check_null_mut_ptr(mutex)?;
        (*mutex.cast::<PthreadMutex>()).unlock()?;
        Ok(0)
    })
}
