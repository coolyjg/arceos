#![cfg_attr(all(not(test), not(doc)), no_std)]
#![feature(doc_cfg)]
#![feature(doc_auto_cfg)]
#![feature(ip_in_core)]
#![feature(int_roundings)]
#![feature(naked_functions)]
#![feature(result_option_inspect)]
#![allow(clippy::missing_safety_doc)]
#![allow(non_camel_case_types, non_upper_case_globals)]

extern crate axruntime;

#[macro_use]
mod utils;

#[macro_use]
extern crate axlog;

#[cfg(feature = "alloc")]
extern crate alloc;

mod errno;

mod imp;
pub mod syscall;

pub use imp::*;
