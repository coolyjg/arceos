use core::ffi::c_int;

use axerrno::LinuxError;

/// Get resources information
#[no_mangle]
pub unsafe extern "C" fn getrlimit(
    resource: c_int,
    rlimits: *mut crate::libctypes::rlimit,
) -> c_int {
    match resource as u32 {
        crate::libctypes::RLIMIT_DATA => {}
        crate::libctypes::RLIMIT_STACK => {}
        crate::libctypes::RLIMIT_NOFILE => {}
        _ => {
            return (LinuxError::EINVAL as c_int).wrapping_neg();
        }
    }
    if rlimits.is_null() {
        return 0;
    }
    match resource as u32 {
        crate::libctypes::RLIMIT_STACK => {
            (*rlimits).rlim_cur = arceos_posix_api::TASK_STACK_SIZE as _;
            (*rlimits).rlim_max = arceos_posix_api::TASK_STACK_SIZE as _;
        }
        #[cfg(feature = "fd")]
        crate::libctypes::RLIMIT_NOFILE => {
            (*rlimits).rlim_cur = arceos_posix_api::AX_FILE_LIMIT as _;
            (*rlimits).rlim_max = arceos_posix_api::AX_FILE_LIMIT as _;
        }
        _ => {}
    }
    0
}

/// Set resource number
#[no_mangle]
pub unsafe extern "C" fn setrlimit(
    resource: c_int,
    _rlimits: *mut crate::libctypes::rlimit,
) -> c_int {
    match resource as u32 {
        crate::libctypes::RLIMIT_DATA => {}
        crate::libctypes::RLIMIT_STACK => {}
        crate::libctypes::RLIMIT_NOFILE => {}
        _ => return (LinuxError::EINVAL as c_int).wrapping_neg(),
    }
    // Currently do not support set resources
    0
}
