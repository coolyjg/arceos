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
#[cfg(feature = "net")]
mod socket;
#[cfg(feature = "fd")]
mod uio;
#[cfg(feature = "multitask")]
mod pthread;

mod stdio;
mod sync;
mod task;
mod time;

#[cfg(feature = "fd")]
pub use fd_ops::*;
#[cfg(feature = "fs")]
pub use file::*;
#[cfg(feature = "select")]
pub use io_mpx::sys_select;
#[cfg(feature = "epoll")]
pub use io_mpx::{sys_epoll_create, sys_epoll_ctl, sys_epoll_wait};
#[cfg(feature = "pipe")]
pub use pipe::*;
#[cfg(feature = "net")]
pub use socket::*;
#[cfg(feature = "fd")]
pub use uio::*;
#[cfg(feature = "multitask")]
pub use pthread::*;
#[cfg(feature = "multitask")]
pub use pthread::mutex::*;

pub use task::*;
pub use time::*;
