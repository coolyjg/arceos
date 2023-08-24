#[cfg(feature = "multitask")]
pub use axsync::{Mutex, MutexGuard};

pub use spinlock as spin;

#[cfg(not(feature = "multitask"))]
pub use spinlock::{SpinNoIrq as Mutex, SpinNoIrqGuard as MutexGuard};
