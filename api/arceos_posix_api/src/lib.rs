#![cfg_attr(all(not(test), not(doc)), no_std)]
#![feature(ip_in_core)]
#![feature(int_roundings)]
#![feature(naked_functions)]
#![feature(result_option_inspect)]
#![allow(clippy::missing_safety_doc)]
#![allow(missing_docs)]
#![allow(non_camel_case_types, non_upper_case_globals)]

extern crate axruntime;

#[macro_use]
extern crate axlog;

#[cfg(feature = "alloc")]
extern crate alloc;

#[macro_use]
mod utils;

mod imp;

/// cbindgen:ignore
#[rustfmt::skip]
#[path = "./ctypes_gen.rs"]
#[allow(dead_code, non_snake_case, non_camel_case_types, non_upper_case_globals, clippy::upper_case_acronyms)]
pub mod ctypes;

pub use imp::sync::*;

#[cfg(feature = "fd")]
pub use imp::fd_ops::{sys_close, sys_dup, sys_dup3, sys_fcntl};
#[cfg(feature = "fs")]
pub use imp::file::{sys_getcwd, sys_lseek, sys_lstat, sys_open, sys_rename, sys_stat};
#[cfg(feature = "select")]
pub use imp::io_mpx::sys_select;
#[cfg(feature = "epoll")]
pub use imp::io_mpx::{sys_epoll_create, sys_epoll_ctl, sys_epoll_wait};
#[cfg(feature = "pipe")]
pub use imp::pipe::sys_pipe;
#[cfg(feature = "multitask")]
pub use imp::pthread::mutex::{
    sys_pthread_mutex_init, sys_pthread_mutex_lock, sys_pthread_mutex_unlock,
};
#[cfg(feature = "multitask")]
pub use imp::pthread::{
    sys_getpid, sys_pthread_create, sys_pthread_exit, sys_pthread_join, sys_pthread_self,
};
#[cfg(feature = "net")]
pub use imp::socket::{
    sys_accept, sys_bind, sys_connect, sys_getaddrinfo, sys_getpeername, sys_getsockname,
    sys_listen, sys_recv, sys_recvfrom, sys_send, sys_sendto, sys_shutdown, sys_socket,
};

pub use imp::io_ops::{sys_fstat, sys_read, sys_write};
pub use imp::task::{sys_exit, sys_sched_yield};
pub use imp::time::{sys_clock_gettime, sys_nanosleep};
pub use imp::uio::sys_writev;
