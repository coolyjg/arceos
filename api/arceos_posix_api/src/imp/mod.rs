/// cbindgen:ignore
#[rustfmt::skip]
#[path = "./ctypes_gen.rs"]
#[allow(dead_code, non_snake_case, non_camel_case_types, non_upper_case_globals, clippy::upper_case_acronyms)]
mod ctypes;

#[cfg(feature = "fd")]
mod fd_ops;
#[cfg(feature = "multitask")]
mod task;

mod stdio;

#[cfg(feature = "fd")]
pub use fd_ops::*;
#[cfg(feature = "multitask")]
pub use task::*;
