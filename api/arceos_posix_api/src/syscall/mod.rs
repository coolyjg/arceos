pub mod syscall_id;

use core::ffi::c_int;

use syscall_id::SyscallId;

use crate::ctypes;

#[allow(improper_ctypes_definitions)]
pub fn syscall(syscall_id: SyscallId, args: [usize; 6]) -> usize {
    if syscall_id != SyscallId::SCHED_YIELD {
        debug!("syscall <= syscall_name: {:?}", syscall_id);
    }
    unsafe {
        match syscall_id {
            SyscallId::INVALID => !0,
            #[cfg(feature = "fd")]
            SyscallId::READ => {
                crate::sys_read(args[0] as c_int, args[1] as *mut core::ffi::c_void, args[2]) as _
            }
            #[cfg(feature = "fd")]
            SyscallId::WRITE => {
                crate::sys_write(args[0] as c_int, args[1] as *mut core::ffi::c_void, args[2]) as _
            }
            #[cfg(feature = "fd")]
            SyscallId::CLOSE => crate::sys_close(args[0] as c_int) as _,
            #[cfg(feature = "fs")]
            SyscallId::STAT => crate::sys_stat(
                args[0] as *const core::ffi::c_char,
                args[1] as *mut ctypes::stat,
            ) as _,
            #[cfg(feature = "fd")]
            SyscallId::FSTAT => {
                crate::sys_fstat(args[0] as c_int, args[1] as *mut ctypes::stat) as _
            }
            #[cfg(feature = "fs")]
            SyscallId::LSTAT => crate::sys_lstat(
                args[0] as *const core::ffi::c_char,
                args[1] as *mut ctypes::stat,
            ) as _,
            #[cfg(feature = "fs")]
            SyscallId::LSEEK => {
                crate::sys_lseek(args[0] as c_int, args[1] as ctypes::off_t, args[2] as c_int) as _
            }
            #[cfg(feature = "fd")]
            SyscallId::WRITEV => crate::sys_writev(
                args[0] as c_int,
                args[1] as *const ctypes::iovec,
                args[2] as c_int,
            ) as _,
            #[cfg(feature = "pipe")]
            SyscallId::PIPE => crate::sys_pipe(args[0] as *mut c_int) as _,
            #[cfg(feature = "select")]
            SyscallId::SELECT => crate::sys_select(
                args[0] as c_int,
                args[1] as *mut ctypes::fd_set,
                args[2] as *mut ctypes::fd_set,
                args[3] as *mut ctypes::fd_set,
                args[4] as *mut ctypes::timeval,
            ) as _,
            SyscallId::SCHED_YIELD => crate::sys_sched_yield() as _,
            #[cfg(feature = "fd")]
            SyscallId::DUP => crate::sys_dup(args[0] as c_int) as _,
            SyscallId::NANO_SLEEP => crate::sys_nanosleep(
                args[0] as *const ctypes::timespec,
                args[1] as *mut ctypes::timespec,
            ) as _,
            #[cfg(feature = "multitask")]
            SyscallId::GETPID => crate::sys_getpid() as _,
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
                args[1] as *const core::ffi::c_void,
                args[2] as ctypes::size_t,
                args[3] as c_int,
                args[4] as *const ctypes::sockaddr,
                args[5] as ctypes::socklen_t,
            ) as _,
            #[cfg(feature = "net")]
            SyscallId::RECVFROM => crate::sys_recvfrom(
                args[0] as c_int,
                args[1] as *mut core::ffi::c_void,
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
            SyscallId::GETSOCKNAME => crate::sys_getsockname(
                args[0] as c_int,
                args[1] as *mut ctypes::sockaddr,
                args[2] as *mut ctypes::socklen_t,
            ) as _,
            #[cfg(feature = "net")]
            SyscallId::GETPEERNAME => crate::sys_getpeername(
                args[0] as c_int,
                args[1] as *mut ctypes::sockaddr,
                args[2] as *mut ctypes::socklen_t,
            ) as _,
            #[allow(unreachable_code)]
            SyscallId::EXIT => crate::sys_exit(args[0] as c_int) as _,
            #[cfg(feature = "fd")]
            SyscallId::FCNTL => crate::sys_fcntl(args[0] as c_int, args[1] as c_int, args[2]) as _,
            #[cfg(feature = "fs")]
            SyscallId::GETCWD => crate::sys_getcwd(args[0] as *mut core::ffi::c_char, args[1]) as _,
            #[cfg(feature = "fs")]
            SyscallId::RENAME => crate::sys_rename(
                args[0] as *const core::ffi::c_char,
                args[1] as *const core::ffi::c_char,
            ) as _,
            #[cfg(feature = "epoll")]
            SyscallId::EPOLL_CREATE => crate::sys_epoll_create(args[0] as c_int) as _,
            SyscallId::CLOCK_GETTIME => crate::sys_clock_gettime(
                args[0] as ctypes::clockid_t,
                args[1] as *mut ctypes::timespec,
            ) as _,
            #[cfg(feature = "epoll")]
            SyscallId::EPOLL_WAIT => crate::sys_epoll_wait(
                args[0] as c_int,
                args[1] as *mut ctypes::epoll_event,
                args[2] as c_int,
                args[3] as c_int,
            ) as _,
            #[cfg(feature = "epoll")]
            SyscallId::EPOLL_CTL => crate::sys_epoll_ctl(
                args[0] as c_int,
                args[1] as c_int,
                args[2] as c_int,
                args[3] as *mut ctypes::epoll_event,
            ) as _,
            #[cfg(feature = "fd")]
            SyscallId::DUP3 => {
                crate::sys_dup3(args[0] as c_int, args[1] as c_int, args[2] as c_int) as _
            }

            #[cfg(feature = "net")]
            SyscallId::SEND => crate::sys_send(
                args[0] as c_int,
                args[1] as *const core::ffi::c_void,
                args[2] as ctypes::size_t,
                args[3] as c_int,
            ) as _,

            #[cfg(feature = "net")]
            SyscallId::RECV => crate::sys_recv(
                args[0] as c_int,
                args[1] as *mut core::ffi::c_void,
                args[2] as ctypes::size_t,
                args[3] as c_int,
            ) as _,
            #[cfg(feature = "net")]
            SyscallId::GETADDRINFO => crate::sys_getaddrinfo(
                args[0] as *const core::ffi::c_char,
                args[1] as *const core::ffi::c_char,
                args[2] as *mut ctypes::sockaddr,
                args[3] as ctypes::size_t,
            ) as _,
            #[cfg(feature = "fs")]
            SyscallId::OPEN => crate::sys_open(
                args[0] as *const core::ffi::c_char,
                args[1] as c_int,
                args[2] as ctypes::mode_t,
            ) as _,
            #[cfg(feature = "multitask")]
            SyscallId::PTHREAD_SELF => crate::sys_pthread_self() as _,
            #[cfg(feature = "multitask")]
            SyscallId::PTHREAD_CREATE => crate::sys_pthread_create(
                args[0] as *mut ctypes::pthread_t,
                args[1] as *const ctypes::pthread_attr_t,
                args[2] as *mut core::ffi::c_void,
                args[3] as *mut core::ffi::c_void,
            ) as _,
            #[allow(unreachable_code)]
            #[cfg(feature = "multitask")]
            SyscallId::PTHREAD_EXIT => {
                crate::sys_pthread_exit(args[0] as *mut core::ffi::c_void) as _
            }
            #[cfg(feature = "multitask")]
            SyscallId::PTHREAD_JOIN => crate::sys_pthread_join(
                args[0] as ctypes::pthread_t,
                args[1] as *mut *mut core::ffi::c_void,
            ) as _,
            #[cfg(feature = "multitask")]
            SyscallId::PTHREAD_MUTEX_INIT => crate::sys_pthread_mutex_init(
                args[0] as *mut ctypes::pthread_mutex_t,
                args[1] as *const ctypes::pthread_mutexattr_t,
            ) as _,
            #[cfg(feature = "multitask")]
            SyscallId::PTHREAD_MUTEX_LOCK => {
                crate::sys_pthread_mutex_lock(args[0] as *mut ctypes::pthread_mutex_t) as _
            }
            #[cfg(feature = "multitask")]
            SyscallId::PTHREAD_MUTEX_UNLOCK => {
                crate::sys_pthread_mutex_unlock(args[0] as *mut ctypes::pthread_mutex_t) as _
            }
        }
    }
}

pub fn syscall0(syscall_id: SyscallId) -> usize {
    syscall(syscall_id, [0usize; 6])
}

pub fn syscall1(syscall_id: SyscallId, args: usize) -> usize {
    syscall(syscall_id, [args, 0, 0, 0, 0, 0])
}

pub fn syscall2(syscall_id: SyscallId, args: [usize; 2]) -> usize {
    syscall(syscall_id, [args[0], args[1], 0, 0, 0, 0])
}

pub fn syscall3(syscall_id: SyscallId, args: [usize; 3]) -> usize {
    syscall(syscall_id, [args[0], args[1], args[2], 0, 0, 0])
}

pub fn syscall4(syscall_id: SyscallId, args: [usize; 4]) -> usize {
    syscall(syscall_id, [args[0], args[1], args[2], args[3], 0, 0])
}

pub fn syscall5(syscall_id: SyscallId, args: [usize; 5]) -> usize {
    syscall(syscall_id, [args[0], args[1], args[2], args[3], args[4], 0])
}

pub fn syscall6(syscall_id: SyscallId, args: [usize; 6]) -> usize {
    syscall(syscall_id, args)
}
