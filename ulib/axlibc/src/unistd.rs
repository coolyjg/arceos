use arceos_posix_api::sys_exit;
use core::ffi::c_int;

/// Get current thread ID.
#[no_mangle]
pub unsafe extern "C" fn getpid() -> c_int {
    #[cfg(not(feature = "multitask"))]
    return 2; // `Main` task ID
    #[cfg(feature = "multitask")]
    crate::utils::e(arceos_posix_api::sys_getpid())
}

/// Abort the current process.
#[no_mangle]
pub unsafe extern "C" fn abort() -> ! {
    panic!()
}

/// Exits the current thread.
#[no_mangle]
pub unsafe extern "C" fn exit(exit_code: c_int) -> ! {
    sys_exit(exit_code)
}
