use arceos_posix_api::{ctypes, syscall2, syscall3, syscall4, syscall6, SyscallId};
use core::ffi::{c_char, c_int, c_void};

use crate::utils::e;

/// Create an socket for communication.
///
/// Return the socket file descriptor.
#[no_mangle]
pub unsafe extern "C" fn socket(domain: c_int, socktype: c_int, protocol: c_int) -> c_int {
    e(syscall3(
        SyscallId::SOCKET,
        [domain as usize, socktype as usize, protocol as usize],
    ))
}

/// Bind a address to a socket.
///
/// Return 0 if success.
#[no_mangle]
pub unsafe extern "C" fn bind(
    socket_fd: c_int,
    socket_addr: *const ctypes::sockaddr,
    addrlen: ctypes::socklen_t,
) -> c_int {
    e(syscall3(
        SyscallId::BIND,
        [socket_fd as usize, socket_addr as usize, addrlen as usize],
    ))
}

/// Connects the socket to the address specified.
///
/// Return 0 if success.
#[no_mangle]
pub unsafe extern "C" fn connect(
    socket_fd: c_int,
    socket_addr: *const ctypes::sockaddr,
    addrlen: ctypes::socklen_t,
) -> c_int {
    e(syscall3(
        SyscallId::CONNECT,
        [socket_fd as usize, socket_addr as usize, addrlen as usize],
    ))
}

/// Send a message on a socket to the address specified.
///
/// Return the number of bytes sent if success.
#[no_mangle]
pub unsafe extern "C" fn sendto(
    socket_fd: c_int,
    buf_ptr: *const c_void,
    len: ctypes::size_t,
    flag: c_int, // currently not used
    socket_addr: *const ctypes::sockaddr,
    addrlen: ctypes::socklen_t,
) -> ctypes::ssize_t {
    if socket_addr.is_null() && addrlen == 0 {
        return e(syscall4(
            SyscallId::SEND,
            [socket_fd as usize, buf_ptr as usize, len, flag as usize],
        )) as _;
    }
    e(syscall6(
        SyscallId::SENDTO,
        [
            socket_fd as usize,
            buf_ptr as usize,
            len,
            flag as usize,
            socket_addr as usize,
            addrlen as usize,
        ],
    )) as _
}

/// Send a message on a socket to the address connected.
///
/// Return the number of bytes sent if success.
#[no_mangle]
pub unsafe extern "C" fn send(
    socket_fd: c_int,
    buf_ptr: *const c_void,
    len: ctypes::size_t,
    flag: c_int, // currently not used
) -> ctypes::ssize_t {
    e(syscall4(
        SyscallId::SEND,
        [socket_fd as usize, buf_ptr as usize, len, flag as usize],
    )) as _
}

/// Receive a message on a socket and get its source address.
///
/// Return the number of bytes received if success.
#[no_mangle]
pub unsafe extern "C" fn recvfrom(
    socket_fd: c_int,
    buf_ptr: *mut c_void,
    len: ctypes::size_t,
    flag: c_int, // currently not used
    socket_addr: *mut ctypes::sockaddr,
    addrlen: *mut ctypes::socklen_t,
) -> ctypes::ssize_t {
    if socket_addr.is_null() {
        return e(syscall4(
            SyscallId::RECV,
            [socket_fd as usize, buf_ptr as usize, len, flag as usize],
        )) as _;
    }
    e(syscall6(
        SyscallId::RECVFROM,
        [
            socket_fd as usize,
            buf_ptr as usize,
            len,
            flag as usize,
            socket_addr as usize,
            addrlen as usize,
        ],
    )) as _
}

/// Receive a message on a socket.
///
/// Return the number of bytes received if success.
#[no_mangle]
pub unsafe extern "C" fn recv(
    socket_fd: c_int,
    buf_ptr: *mut c_void,
    len: ctypes::size_t,
    flag: c_int, // currently not used
) -> ctypes::ssize_t {
    e(syscall4(
        SyscallId::RECV,
        [socket_fd as usize, buf_ptr as usize, len, flag as usize],
    )) as _
}

/// Listen for connections on a socket
///
/// Return 0 if success.
#[no_mangle]
pub unsafe extern "C" fn listen(
    socket_fd: c_int,
    backlog: c_int, // currently not used
) -> c_int {
    e(syscall2(
        SyscallId::LISTEN,
        [socket_fd as usize, backlog as usize],
    )) as _
}

/// Accept for connections on a socket
///
/// Return file descriptor for the accepted socket if success.
#[no_mangle]
pub unsafe extern "C" fn accept(
    socket_fd: c_int,
    socket_addr: *mut ctypes::sockaddr,
    socket_len: *mut ctypes::socklen_t,
) -> c_int {
    e(syscall3(
        SyscallId::ACCEPT,
        [
            socket_fd as usize,
            socket_addr as usize,
            socket_len as usize,
        ],
    )) as _
}

/// Shut down a full-duplex connection.
///
/// Return 0 if success.
#[no_mangle]
pub unsafe extern "C" fn shutdown(
    socket_fd: c_int,
    flag: c_int, // currently not used
) -> c_int {
    e(syscall2(
        SyscallId::SHUTDOWN,
        [socket_fd as usize, flag as usize],
    )) as _
}

/// Query addresses for a domain name.
///
/// Return address number if success.
#[no_mangle]
pub unsafe extern "C" fn ax_getaddrinfo(
    node: *const c_char,
    service: *const c_char,
    addrs: *mut ctypes::sockaddr,
    len: ctypes::size_t,
) -> c_int {
    e(syscall4(
        SyscallId::GETADDRINFO,
        [node as usize, service as usize, addrs as usize, len],
    ))
}

/// Get current address to which the socket sockfd is bound.
#[no_mangle]
pub unsafe extern "C" fn getsockname(
    sock_fd: c_int,
    addr: *mut ctypes::sockaddr,
    addrlen: *mut ctypes::socklen_t,
) -> c_int {
    e(syscall3(
        SyscallId::GETSOCKNAME,
        [sock_fd as usize, addr as usize, addrlen as usize],
    ))
}

/// Get peer address to which the socket sockfd is connected.
#[no_mangle]
pub unsafe extern "C" fn getpeername(
    sock_fd: c_int,
    addr: *mut ctypes::sockaddr,
    addrlen: *mut ctypes::socklen_t,
) -> c_int {
    e(syscall3(
        SyscallId::GETPEERNAME,
        [sock_fd as usize, addr as usize, addrlen as usize],
    ))
}
