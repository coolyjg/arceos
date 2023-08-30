use core::ffi::c_int;

use super::{ctypes, sys_write};
use axerrno::LinuxError;

/// `writev` implementation
///
/// TODO: DO NOT let fd = 0/1/2
#[no_mangle]
pub unsafe extern "C" fn sys_writev(
    fd: c_int,
    iov: *const ctypes::iovec,
    iocnt: c_int,
) -> ctypes::ssize_t {
    debug!("sys_writev <= fd: {}", fd);
    syscall_body!(sys_writev, {
        if !(0..=1024).contains(&iocnt) {
            return Err(LinuxError::EINVAL);
        }

        let iovs = core::slice::from_raw_parts(iov, iocnt as usize);
        let mut ret = 0;
        for iov in iovs.iter() {
            ret += sys_write(fd, iov.iov_base, iov.iov_len);
        }

        Ok(ret)
    })
}
