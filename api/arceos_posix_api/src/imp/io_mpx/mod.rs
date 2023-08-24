//! I/O multiplexing:
//!
//! * [`select`](select::ax_select)
//! * [`epoll_create`](epoll::ax_epoll_create)
//! * [`epoll_ctl`](epoll::ax_epoll_ctl)
//! * [`epoll_wait`](epoll::ax_epoll_wait)

#[cfg(feature = "epoll")]
mod epoll;
#[cfg(feature = "select")]
mod select;

#[cfg(feature = "epoll")]
pub use self::epoll::{sys_epoll_create, sys_epoll_ctl, sys_epoll_wait};
#[cfg(feature = "select")]
pub use self::select::sys_select;
