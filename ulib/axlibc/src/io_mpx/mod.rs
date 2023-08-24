//! I/O multiplexing:
//!
//! * [`select`](select::ax_select)
//! * [`epoll_create`](epoll::epoll_create)
//! * [`epoll_ctl`](epoll::epoll_ctl)
//! * [`epoll_wait`](epoll::epoll_wait)

#[cfg(feature = "epoll")]
mod epoll;
#[cfg(feature = "select")]
mod select;

#[cfg(feature = "epoll")]
pub use self::epoll::{epoll_create, epoll_ctl, epoll_wait};
#[cfg(feature = "select")]
pub use self::select::select;
