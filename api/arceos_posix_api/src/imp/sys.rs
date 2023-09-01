use core::ffi::{c_int, c_long};

use crate::ctypes;

const PAGE_SIZE_4K: usize = 4096;

/// Return system configuration infomation
///
/// Notice: currently only support what unikraft covers
pub fn sys_sysconf(name: c_int) -> c_long {
    match name as u32 {
        // Page size
        ctypes::_SC_PAGE_SIZE => PAGE_SIZE_4K as c_long,
        // Total physical pages
        ctypes::_SC_PHYS_PAGES => (axconfig::PHYS_MEMORY_SIZE / PAGE_SIZE_4K) as c_long,
        // Number of processors in use
        ctypes::_SC_NPROCESSORS_ONLN => axconfig::SMP as c_long,
        // Avaliable physical pages
        #[cfg(feature = "alloc")]
        ctypes::_SC_AVPHYS_PAGES => axalloc::global_allocator().available_pages() as c_long,
        // Maximum number of files per process
        #[cfg(feature = "fd")]
        ctypes::_SC_OPEN_MAX => super::fd_ops::AX_FILE_LIMIT as c_long,
        _ => 0,
    }
}