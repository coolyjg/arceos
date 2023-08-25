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
    #[cfg(feature = "fd")]
    FSTAT = 5,
    #[cfg(feature = "pipe")]
    PIPE = 22,
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
    GETADDRINFO = 51,
    #[cfg(feature = "net")]
    GETPEERNAME = 52,
    #[cfg(feature = "fd")]
    FCNTL = 55,
    #[cfg(feature = "fd")]
    DUP3 = 292,
}
