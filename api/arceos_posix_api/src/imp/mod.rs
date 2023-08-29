/// cbindgen:ignore
#[rustfmt::skip]
#[path = "./ctypes_gen.rs"]
#[allow(dead_code, non_snake_case, non_camel_case_types, non_upper_case_globals, clippy::upper_case_acronyms)]
pub mod ctypes;

#[cfg(feature = "fd")]
mod fd_ops;
#[cfg(feature = "fs")]
mod file;
#[cfg(any(feature = "select", feature = "epoll"))]
mod io_mpx;
#[cfg(feature = "pipe")]
mod pipe;
#[cfg(feature = "multitask")]
mod pthread;
#[cfg(feature = "net")]
mod socket;
#[cfg(feature = "fd")]
mod uio;

mod stdio;
mod sync;
mod task;
mod time;

#[cfg(feature = "fd")]
pub use fd_ops::{
    sys_close, sys_dup, sys_dup3, sys_fcntl, sys_fstat, sys_read, sys_write, FileLike,
};
#[cfg(feature = "fs")]
pub use file::{sys_getcwd, sys_lseek, sys_lstat, sys_open, sys_rename, sys_stat};
#[cfg(feature = "select")]
pub use io_mpx::sys_select;
#[cfg(feature = "epoll")]
pub use io_mpx::{sys_epoll_create, sys_epoll_ctl, sys_epoll_wait};
#[cfg(feature = "pipe")]
pub use pipe::sys_pipe;
#[cfg(feature = "multitask")]
pub use pthread::mutex::{
    sys_pthread_mutex_init, sys_pthread_mutex_lock, sys_pthread_mutex_unlock,
};
#[cfg(feature = "multitask")]
pub use pthread::{
    sys_getpid, sys_pthread_create, sys_pthread_exit, sys_pthread_join, sys_pthread_self,
};
#[cfg(feature = "net")]
pub use socket::{
    sys_accept, sys_bind, sys_connect, sys_getaddrinfo, sys_getpeername, sys_getsockname,
    sys_listen, sys_recv, sys_recvfrom, sys_send, sys_sendto, sys_shutdown, sys_socket,
};
#[cfg(feature = "fd")]
pub use uio::sys_writev;

pub use task::sys_sched_yield;
pub use time::{sys_clock_gettime, sys_nanosleep};
