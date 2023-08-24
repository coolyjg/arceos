#[cfg(feature = "fd")]
use super::FileLike;
#[cfg(feature = "fd")]
use alloc::sync::Arc;
#[cfg(feature = "fd")]
use axerrno::{LinuxError, LinuxResult};
#[cfg(feature = "fd")]
use axio::PollState;

// TODO: wrap this with mutex
pub struct Stdin;

impl Stdin {
    pub fn new() -> Self {
        Self {}
    }
}

fn console_read_bytes() -> Option<u8> {
    axhal::console::getchar().map(|c| if c == b'\r' { b'\n' } else { c })
}

fn console_write_bytes(buf: &[u8]) -> axerrno::AxResult<usize> {
    axhal::console::write_bytes(buf);
    Ok(buf.len())
}

// TODO: wrap this with mutex
pub struct Stdout;

impl Stdout {
    pub fn new() -> Self {
        Self {}
    }
}

#[cfg(feature = "fd")]
impl FileLike for Stdin {
    fn read(&self, buf: &mut [u8]) -> LinuxResult<usize> {
        let mut read_len = 0;
        while read_len < buf.len() {
            if let Some(c) = console_read_bytes() {
                buf[read_len] = c;
                read_len += 1;
            } else {
                break;
            }
        }
        Ok(read_len)
    }

    fn write(&self, _buf: &[u8]) -> LinuxResult<usize> {
        Err(LinuxError::EPERM)
    }

    fn stat(&self) -> LinuxResult<super::ctypes::stat> {
        let st_mode = 0o20000 | 0o440u32; // S_IFCHR | r--r-----
        Ok(super::ctypes::stat {
            st_ino: 1,
            st_nlink: 1,
            st_mode,
            ..Default::default()
        })
    }

    fn into_any(self: Arc<Self>) -> Arc<dyn core::any::Any + Send + Sync> {
        self
    }

    fn poll(&self) -> LinuxResult<PollState> {
        Ok(PollState {
            readable: true,
            writable: true,
        })
    }

    fn set_nonblocking(&self, _nonblocking: bool) -> LinuxResult {
        Ok(())
    }
}

#[cfg(feature = "fd")]
impl FileLike for Stdout {
    fn read(&self, _buf: &mut [u8]) -> LinuxResult<usize> {
        Err(LinuxError::EPERM)
    }

    fn write(&self, buf: &[u8]) -> LinuxResult<usize> {
        Ok(console_write_bytes(buf)?)
    }

    fn stat(&self) -> LinuxResult<super::ctypes::stat> {
        let st_mode = 0o20000 | 0o220u32; // S_IFCHR | -w--w----
        Ok(super::ctypes::stat {
            st_ino: 1,
            st_nlink: 1,
            st_mode,
            ..Default::default()
        })
    }

    fn into_any(self: Arc<Self>) -> Arc<dyn core::any::Any + Send + Sync> {
        self
    }

    fn poll(&self) -> LinuxResult<PollState> {
        Ok(PollState {
            readable: true,
            writable: true,
        })
    }

    fn set_nonblocking(&self, _nonblocking: bool) -> LinuxResult {
        Ok(())
    }
}
