use core::ffi::c_int;

use axerrno::LinuxError;

/// Get resource limitations
///
/// TODO: support more resource types
pub unsafe fn sys_getrlimit(resource: c_int, rlimits: *mut crate::ctypes::rlimit) -> c_int {
    syscall_body!(sys_getrlimit, {
        match resource as u32 {
            crate::ctypes::RLIMIT_DATA => {}
            crate::ctypes::RLIMIT_STACK => {}
            crate::ctypes::RLIMIT_NOFILE => {}
            _ => {
                return Err(LinuxError::EINVAL);
            }
        }
        if rlimits.is_null() {
            return Ok(0);
        }
        match resource as u32 {
            crate::ctypes::RLIMIT_STACK => {
                (*rlimits).rlim_cur = crate::config::TASK_STACK_SIZE as _;
                (*rlimits).rlim_max = crate::config::TASK_STACK_SIZE as _;
            }
            #[cfg(feature = "fd")]
            crate::ctypes::RLIMIT_NOFILE => {
                (*rlimits).rlim_cur = super::fd_ops::AX_FILE_LIMIT as _;
                (*rlimits).rlim_max = super::fd_ops::AX_FILE_LIMIT as _;
            }
            _ => {}
        }
        Ok(0)
    })
}

/// Set resource limitations
///
/// TODO: support more resource types
pub unsafe fn sys_setrlimit(resource: c_int, _rlimits: *mut crate::ctypes::rlimit) -> c_int {
    syscall_body!(sys_setrlimit, {
        match resource as u32 {
            crate::ctypes::RLIMIT_DATA => {}
            crate::ctypes::RLIMIT_STACK => {}
            crate::ctypes::RLIMIT_NOFILE => {}
            _ => return Err(LinuxError::EINVAL),
        }
        // Currently do not support set resources
        Ok(0)
    })
}
