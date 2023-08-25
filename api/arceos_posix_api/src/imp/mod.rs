/// cbindgen:ignore
#[rustfmt::skip]
#[path = "./ctypes_gen.rs"]
#[allow(dead_code, non_snake_case, non_camel_case_types, non_upper_case_globals, clippy::upper_case_acronyms)]
pub mod ctypes;

#[cfg(feature = "fd")]
mod fd_ops;
#[cfg(feature = "pipe")]
mod pipe;
#[cfg(feature = "net")]
mod socket;
#[cfg(feature = "multitask")]
mod task;

mod stdio;
mod sync;

#[cfg(feature = "fd")]
pub use fd_ops::*;
#[cfg(feature = "pipe")]
pub use pipe::*;
#[cfg(feature = "net")]
pub use socket::*;
#[cfg(feature = "multitask")]
pub use task::*;
