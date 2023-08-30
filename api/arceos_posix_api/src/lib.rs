#![cfg_attr(all(not(test), not(doc)), no_std)]
#![feature(ip_in_core)]
#![feature(int_roundings)]
#![feature(naked_functions)]
#![feature(result_option_inspect)]
#![allow(clippy::missing_safety_doc)]
#![allow(non_camel_case_types, non_upper_case_globals)]

extern crate axruntime;

#[macro_use]
extern crate axlog;

#[cfg(feature = "alloc")]
extern crate alloc;

#[macro_use]
mod utils;

mod imp;
mod syscall;

use imp::*;
pub use syscall::syscall_id::SyscallId;
pub use syscall::{syscall, syscall0, syscall1, syscall2, syscall3, syscall4, syscall5, syscall6};
// pub use imp::{stdin, stdout};
pub use imp::sync::*;
