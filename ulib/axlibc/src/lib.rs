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

#[cfg(feature = "alloc")]
extern crate alloc;

/// cbindgen:ignore
#[rustfmt::skip]
#[path = "./ctypes_gen.rs"]
#[allow(dead_code, non_snake_case, non_camel_case_types, non_upper_case_globals, clippy::upper_case_acronyms)]
mod ctypes;

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
mod mktime;
mod rand;
mod setjmp;
mod stdio;
mod stdio_imp;
mod sys;
mod time;

/// Get current thread ID.
#[no_mangle]
pub unsafe extern "C" fn getpid() -> core::ffi::c_int {
    #[cfg(not(feature = "multitask"))]
    return 2; // `Main` task ID
    #[cfg(feature = "multitask")]
    {
        use crate::utils::e;
        use arceos_posix_api::{syscall0, SyscallId};
        e(syscall0(SyscallId::GETPID))
    }
}

/// Abort the current process.
#[no_mangle]
pub unsafe extern "C" fn ax_panic() -> ! {
    panic!()
}

/// Exits the current thread.
#[no_mangle]
pub unsafe extern "C" fn exit(exit_code: core::ffi::c_int) -> ! {
    crate::utils::e(arceos_posix_api::syscall1(
        arceos_posix_api::SyscallId::EXIT,
        exit_code as usize,
    ));
    unreachable!()
}

pub use self::rand::{ax_rand_u32, ax_srand};

#[cfg(feature = "alloc")]
pub use self::malloc::{free, malloc};
#[cfg(feature = "alloc")]
pub use self::strftime::strftime;

#[cfg(feature = "fd")]
pub use self::fd_ops::{ax_fcntl, close, dup, dup3, fstat, read, write};
#[cfg(feature = "fd")]
pub use self::uio::writev;

#[cfg(feature = "fs")]
pub use self::file::{ax_open, getcwd, lseek, lstat, stat};

#[cfg(feature = "net")]
pub use self::socket::{
    accept, ax_getaddrinfo, ax_recvfrom, ax_sendto, bind, connect, getpeername, getsockname,
    listen, recv, send, shutdown, socket,
};

#[cfg(feature = "multitask")]
pub use self::pthread::mutex::{pthread_mutex_init, pthread_mutex_lock, pthread_mutex_unlock};
#[cfg(feature = "multitask")]
pub use self::pthread::{pthread_create, pthread_exit, pthread_join};

#[cfg(feature = "pipe")]
pub use self::pipe::pipe;

#[cfg(feature = "select")]
pub use self::io_mpx::ax_select;

#[cfg(feature = "epoll")]
pub use self::io_mpx::{epoll_create, epoll_ctl, epoll_wait};

#[cfg(feature = "fp_simd")]
pub use self::strtod::{strtod, strtof};

pub use self::errno::strerror;
pub use self::mktime::mktime;
pub use self::stdio::{ax_println_str, print_str};
pub use self::sys::ax_sysconf;
pub use self::time::{clock_gettime, nanosleep};
