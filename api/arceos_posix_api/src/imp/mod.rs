#[cfg(feature = "fd")]
pub mod fd_ops;
#[cfg(feature = "fs")]
pub mod file;
#[cfg(any(feature = "select", feature = "epoll"))]
pub mod io_mpx;
#[cfg(feature = "pipe")]
pub mod pipe;
#[cfg(feature = "multitask")]
pub mod pthread;
#[cfg(feature = "net")]
pub mod socket;

pub mod io_ops;
pub mod sync;
pub mod task;
pub mod time;
pub mod uio;

mod stdio_imp;

#[cfg(feature = "fd")]
pub use fd_ops::{sys_close, sys_dup, sys_dup3, sys_fcntl};
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

pub use io_ops::{sys_fstat, sys_read, sys_write};
pub use sync::*;
pub use task::{sys_exit, sys_sched_yield};
pub use time::{sys_clock_gettime, sys_nanosleep};
pub use uio::sys_writev;
