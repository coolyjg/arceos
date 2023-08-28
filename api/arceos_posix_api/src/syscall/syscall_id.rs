use num_enum::TryFromPrimitive;

#[allow(clippy::upper_case_acronyms)]
#[repr(usize)]
#[derive(Debug, PartialEq, Eq, Clone, Copy, TryFromPrimitive)]
pub enum SyscallId {
    INVALID = 999,
    #[cfg(feature = "fd")]
    READ = 0,
    #[cfg(feature = "fd")]
    WRITE = 1,
    #[cfg(feature = "fd")]
    CLOSE = 3,
    // TODO: This may not be a syscall
    #[cfg(feature = "fd")]
    FSTAT = 5,
    #[cfg(feature = "fd")]
    WRITEV = 20,
    #[cfg(feature = "pipe")]
    PIPE = 22,
    #[cfg(feature = "select")]
    SELECT = 23,
    #[cfg(feature = "multitask")]
    SCHED_YIELD = 24,
    #[cfg(feature = "fd")]
    DUP = 32,
    #[cfg(feature = "net")]
    SOCKET = 41,
    #[cfg(feature = "net")]
    CONNECT = 42,
    #[cfg(feature = "net")]
    ACCEPT = 43,
    #[cfg(feature = "net")]
    SENDTO = 44,
    #[cfg(feature = "net")]
    RECVFROM = 45,
    #[cfg(feature = "net")]
    SHUTDOWN = 48,
    #[cfg(feature = "net")]
    BIND = 49,
    #[cfg(feature = "net")]
    LISTEN = 50,
    #[cfg(feature = "net")]
    GETSOCKNAME = 51,
    #[cfg(feature = "net")]
    GETPEERNAME = 52,
    #[cfg(feature = "fd")]
    FCNTL = 72,
    #[cfg(feature = "epoll")]
    EPOLL_CREATE = 213,
    CLOCK_GETTIME = 228,
    // TODO: epoll_wait or epoll_pwait?
    #[cfg(feature = "epoll")]
    EPOLL_WAIT = 232,
    #[cfg(feature = "epoll")]
    EPOLL_CTL = 233,
    #[cfg(feature = "fd")]
    DUP3 = 292,

    // ArceOS specific syscall, starting from 500
    // `send` should call `sendto`
    #[cfg(feature = "net")]
    SEND = 500,
    // `recv` should call `recvfrom`
    #[cfg(feature = "net")]
    RECV = 501,
    // This is not a syscall, but requires `dns send` in ArceOS
    #[cfg(feature = "net")]
    GETADDRINFO = 502,
}
