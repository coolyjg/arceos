use arceos_posix_api::sys_sysconf;
use core::ffi::{c_int, c_long};

/// This constant is used to fit "resource.c/getrlimit()"
///
/// TODO: This should be a syscall, `prlimit64`, rather than a constant.
#[allow(unused)]
pub const AX_CONFIG_TASK_STACK_SIZE: usize = 0x40000;

/// Return system configuration infomation
///
/// Notice: currently only support what unikraft covers
#[no_mangle]
pub unsafe extern "C" fn sysconf(name: c_int) -> c_long {
    sys_sysconf(name)
}
