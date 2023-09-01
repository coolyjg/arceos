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

#[cfg(feature = "alloc")]
extern crate alloc;

#[macro_use]
mod utils;

#[cfg(feature = "fd")]
mod fd_ops;
#[cfg(feature = "fs")]
mod file;
#[cfg(any(feature = "select", feature = "epoll"))]
mod io_mpx;
#[cfg(feature = "alloc")]
mod malloc;
#[cfg(feature = "pipe")]
mod pipe;
#[cfg(feature = "multitask")]
mod pthread;
#[cfg(feature = "net")]
mod socket;
#[cfg(feature = "alloc")]
mod strftime;
#[cfg(feature = "fp_simd")]
mod strtod;
#[cfg(feature = "fd")]
mod uio;

mod errno;
mod io_ops;
mod mktime;
mod print;
mod rand;
mod setjmp;
mod sys;
mod time;

/// Get current thread ID.
#[no_mangle]
pub unsafe extern "C" fn getpid() -> core::ffi::c_int {
    #[cfg(not(feature = "multitask"))]
    return 2; // `Main` task ID
    #[cfg(feature = "multitask")]
    crate::utils::e(arceos_posix_api::sys_getpid())
}

/// Abort the current process.
#[no_mangle]
pub unsafe extern "C" fn ax_panic() -> ! {
    panic!()
}

/// Exits the current thread.
#[no_mangle]
pub unsafe extern "C" fn exit(exit_code: core::ffi::c_int) -> ! {
    sys_exit(exit_code)
}

use arceos_posix_api::sys_exit;

pub use self::rand::{ax_rand_u32, ax_srand};

#[cfg(feature = "alloc")]
pub use self::malloc::{free, malloc};
#[cfg(feature = "alloc")]
pub use self::strftime::strftime;

#[cfg(feature = "fd")]
pub use self::fd_ops::{ax_fcntl, close, dup, dup3};
#[cfg(feature = "fd")]
pub use self::uio::writev;

#[cfg(feature = "fs")]
pub use self::file::{ax_open, getcwd, lseek, lstat, stat};

#[cfg(feature = "net")]
pub use self::socket::{
    accept, ax_getaddrinfo, bind, connect, getpeername, getsockname, listen, recv, recvfrom, send,
    sendto, shutdown, socket,
};

#[cfg(feature = "multitask")]
pub use self::pthread::mutex::{pthread_mutex_init, pthread_mutex_lock, pthread_mutex_unlock};
#[cfg(feature = "multitask")]
pub use self::pthread::{pthread_create, pthread_exit, pthread_join};

#[cfg(feature = "pipe")]
pub use self::pipe::pipe;

#[cfg(feature = "select")]
pub use self::io_mpx::select;

#[cfg(feature = "epoll")]
pub use self::io_mpx::{epoll_create, epoll_ctl, epoll_wait};

#[cfg(feature = "fp_simd")]
pub use self::strtod::{strtod, strtof};

pub use self::errno::strerror;
pub use self::io_ops::{ax_write, fstat, read};
pub use self::mktime::mktime;
pub use self::print::println_str;
pub use self::sys::ax_sysconf;
pub use self::time::{clock_gettime, nanosleep};
