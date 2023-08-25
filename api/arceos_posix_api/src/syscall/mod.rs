#[macro_use]
mod macros;

mod syscall_id;

use core::ffi::{c_char, c_int, c_void};

use syscall_id::SyscallId;

use crate::ctypes;

#[no_mangle]
pub unsafe extern "C" fn syscall(syscall_id: usize, args: [usize; 6]) -> isize {
    let syscall_name = SyscallId::try_from(syscall_id).unwrap_or(SyscallId::INVALID);
    debug!(
        "syscall <= syscall_id: {}, syscall_name: {:?}",
        syscall_id, syscall_name
    );
    match syscall_name {
        SyscallId::INVALID => -1,
        #[cfg(feature = "fd")]
        SyscallId::READ => crate::sys_read(args[0] as c_int, args[1] as *mut c_void, args[2]) as _,
        #[cfg(feature = "fd")]
        SyscallId::WRITE => crate::sys_write(args[0] as c_int, args[1] as *mut c_void, args[2]),
        #[cfg(feature = "fd")]
        SyscallId::CLOSE => crate::sys_close(args[0] as c_int) as _,
        #[cfg(feature = "fd")]
        SyscallId::FSTAT => crate::sys_fstat(args[0] as c_int, args[1] as *mut ctypes::stat) as _,
        #[cfg(feature = "pipe")]
        SyscallId::PIPE => crate::sys_pipe(args[0] as *mut c_int, args[1] as *mut c_int) as _,
        #[cfg(feature = "multitask")]
        SyscallId::SCHED_YIELD => crate::sys_sched_yield(),
        #[cfg(feature = "fd")]
        SyscallId::DUP => crate::sys_dup(args[0] as c_int) as _,
        #[cfg(feature = "net")]
        SyscallId::SOCKET => {
            crate::sys_socket(args[0] as c_int, args[1] as c_int, args[2] as c_int) as _
        }
        #[cfg(feature = "net")]
        SyscallId::CONNECT => crate::sys_connect(
            args[0] as c_int,
            args[1] as *const ctypes::sockaddr,
            args[2] as ctypes::socklen_t,
        ) as _,
        #[cfg(feature = "net")]
        SyscallId::ACCEPT => crate::sys_accept(
            args[0] as c_int,
            args[1] as *mut ctypes::sockaddr,
            args[2] as *mut ctypes::socklen_t,
        ) as _,
        #[cfg(feature = "net")]
        SyscallId::SENDTO => crate::sys_sendto(
            args[0] as c_int,
            args[1] as *const c_void,
            args[2] as ctypes::size_t,
            args[3] as c_int,
            args[4] as *const ctypes::sockaddr,
            args[5] as ctypes::socklen_t,
        ) as _,
        #[cfg(feature = "net")]
        SyscallId::RECVFROM => crate::sys_recvfrom(
            args[0] as c_int,
            args[1] as *mut c_void,
            args[2] as ctypes::size_t,
            args[3] as c_int,
            args[4] as *mut ctypes::sockaddr,
            args[5] as *mut ctypes::socklen_t,
        ) as _,
        #[cfg(feature = "net")]
        SyscallId::SHUTDOWN => crate::sys_shutdown(args[0] as c_int, args[1] as c_int) as _,
        #[cfg(feature = "net")]
        SyscallId::BIND => crate::sys_bind(
            args[0] as c_int,
            args[1] as *const ctypes::sockaddr,
            args[2] as ctypes::socklen_t,
        ) as _,
        #[cfg(feature = "net")]
        SyscallId::LISTEN => crate::sys_listen(args[0] as c_int, args[1] as c_int) as _,
        #[cfg(feature = "net")]
        SyscallId::GETADDRINFO => crate::sys_getaddrinfo(
            args[0] as *const c_char,
            args[1] as *const c_char,
            args[2] as *mut ctypes::sockaddr,
            args[3] as ctypes::size_t,
        ) as _,
        #[cfg(feature = "net")]
        SyscallId::GETPEERNAME => crate::sys_getpeername(
            args[0] as c_int,
            args[1] as *mut ctypes::sockaddr,
            args[2] as *mut ctypes::socklen_t,
        ) as _,
        #[cfg(feature = "fd")]
        SyscallId::FCNTL => crate::sys_fcntl(args[0] as c_int, args[1] as c_int, args[2]) as _,
        #[cfg(feature = "fd")]
        SyscallId::DUP3 => {
            crate::sys_dup3(args[0] as c_int, args[1] as c_int, args[2] as c_int) as _
        }
    }
}
