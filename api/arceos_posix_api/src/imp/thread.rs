use core::{ffi::c_int, time::Duration};

/// Relinquish the CPU, and switches to another task.
///
/// For single-threaded configuration (`multitask` feature is disabled), we just
/// relax the CPU and wait for incoming interrupts.
pub fn sys_sched_yield() -> c_int {
    #[cfg(feature = "multitask")]
    axtask::yield_now();
    #[cfg(not(feature = "multitask"))]
    if cfg!(feature = "irq") {
        axhal::arch::wait_for_irqs();
    } else {
        core::hint::spin_loop();
    }
    0
}

pub fn sys_exit(_exit_code: core::ffi::c_int) -> ! {
    #[cfg(feature = "multitask")]
    axtask::exit(_exit_code);
    #[cfg(not(feature = "multitask"))]
    axhal::misc::terminate();
}

pub fn sys_sleep_until(deadline: Duration) {
    #[cfg(feature = "multitask")]
    axtask::sleep_until(deadline);
    #[cfg(not(feature = "multitask"))]
    axhal::time::busy_wait_until(deadline);
}
