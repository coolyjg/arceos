//! [ArceOS] user program library for C apps.
//!
//! # Cargo Features
//!
//! - `fd`: Enable file descriptor table.
//! - `pipe`: Enable pipe support.
//! - `select`: Enable synchronous I/O multiplexing ([select]) support.
//! - `epoll`: Enable event polling ([epoll]) support.
//!
//! [ArceOS]: https://github.com/rcore-os/arceos
//! [select]: https://man7.org/linux/man-pages/man2/select.2.html
//! [epoll]: https://man7.org/linux/man-pages/man7/epoll.7.html

#![cfg_attr(all(not(test), not(doc)), no_std)]
#![feature(doc_cfg)]
#![feature(doc_auto_cfg)]
#![feature(ip_in_core)]
#![feature(int_roundings)]
#![feature(naked_functions)]
#![feature(result_option_inspect)]
#![allow(clippy::missing_safety_doc)]

#[macro_use]
extern crate axlog;

mod imp;

pub use self::imp::{ax_exit, ax_panic};

pub use self::imp::{ax_rand_u32, ax_srand};

#[cfg(feature = "alloc")]
pub use self::imp::ax_strftime;
#[cfg(feature = "alloc")]
pub use self::imp::{ax_free, ax_malloc};

#[cfg(feature = "fd")]
pub use self::imp::ax_writev;
#[cfg(feature = "fd")]
pub use self::imp::{ax_close, ax_dup, ax_dup3, ax_fcntl, ax_fstat, ax_read, ax_write};

#[cfg(feature = "fs")]
pub use self::imp::{ax_getcwd, ax_lseek, ax_lstat, ax_open, ax_stat};

#[cfg(feature = "net")]
pub use self::imp::{
    ax_accept, ax_bind, ax_connect, ax_getaddrinfo, ax_getpeername, ax_getsockname, ax_listen,
    ax_recv, ax_recvfrom, ax_send, ax_sendto, ax_shutdown, ax_socket,
};

#[cfg(feature = "multitask")]
pub use self::imp::{ax_getpid, ax_pthread_create, ax_pthread_exit, ax_pthread_join};
#[cfg(feature = "multitask")]
pub use self::imp::{ax_pthread_mutex_init, ax_pthread_mutex_lock, ax_pthread_mutex_unlock};

#[cfg(feature = "pipe")]
pub use self::imp::ax_pipe;

#[cfg(feature = "select")]
pub use self::imp::ax_select;

#[cfg(feature = "epoll")]
pub use self::imp::{ax_epoll_create, ax_epoll_ctl, ax_epoll_wait};

#[cfg(feature = "fp_simd")]
pub use self::imp::{ax_strtod, ax_strtof};

pub use self::imp::ax_errno_string;
pub use self::imp::ax_mktime;
pub use self::imp::ax_sysconf;
pub use self::imp::{ax_clock_gettime, ax_nanosleep};
pub use self::imp::{ax_print_str, ax_println_str};
