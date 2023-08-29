#[cfg(feature = "fd")]
use super::FileLike;
#[cfg(feature = "fd")]
use alloc::sync::Arc;

use axio::{prelude::*, BufReader, Result};

use super::sync::Mutex;

struct StdinRaw;
struct StdoutRaw;

pub struct Stdin {
    inner: &'static Mutex<BufReader<StdinRaw>>,
}

pub struct Stdout {
    inner: &'static Mutex<StdoutRaw>,
}

fn console_read_bytes() -> Option<u8> {
    axhal::console::getchar().map(|c| if c == b'\r' { b'\n' } else { c })
}

fn console_write_bytes(buf: &[u8]) -> axerrno::AxResult<usize> {
    axhal::console::write_bytes(buf);
    Ok(buf.len())
}

impl Read for StdinRaw {
    fn read(&mut self, buf: &mut [u8]) -> axerrno::AxResult<usize> {
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
}

impl Write for StdoutRaw {
    fn write(&mut self, buf: &[u8]) -> axerrno::AxResult<usize> {
        console_write_bytes(buf)
    }

    fn flush(&mut self) -> axerrno::AxResult {
        Ok(())
    }
}

impl Stdin {
    #[allow(dead_code)]
    pub(crate) fn read_locked(&self, buf: &mut [u8]) -> Result<usize> {
        self.inner.lock().read(buf)
    }
}

impl Read for Stdin {
    // Block until at least one byte is read.
    fn read(&mut self, buf: &mut [u8]) -> Result<usize> {
        let read_len = self.inner.lock().read(buf)?;
        if buf.is_empty() || read_len > 0 {
            return Ok(read_len);
        }
        // try again until we get something
        loop {
            let read_len = self.inner.lock().read(buf)?;
            if read_len > 0 {
                return Ok(read_len);
            }
            unsafe {
                super::task::sys_sched_yield();
            }
        }
    }
}

impl Stdout {
    #[allow(dead_code)]
    pub(crate) fn write_locked(&self, buf: &[u8]) -> Result<usize> {
        self.inner.lock().write(buf)
    }
}

impl Write for Stdout {
    fn write(&mut self, buf: &[u8]) -> Result<usize> {
        self.inner.lock().write(buf)
    }
    fn flush(&mut self) -> Result {
        self.inner.lock().flush()
    }
}

/// Constructs a new handle to the standard input of the current process.
pub fn stdin() -> Stdin {
    static INSTANCE: Mutex<BufReader<StdinRaw>> = Mutex::new(BufReader::new(StdinRaw));
    Stdin { inner: &INSTANCE }
}

/// Constructs a new handle to the standard output of the current process.
pub fn stdout() -> Stdout {
    static INSTANCE: Mutex<StdoutRaw> = Mutex::new(StdoutRaw);
    Stdout { inner: &INSTANCE }
}

#[cfg(feature = "fd")]
impl FileLike for Stdin {
    fn read(&self, buf: &mut [u8]) -> axerrno::LinuxResult<usize> {
        Ok(self.read_locked(buf)?)
    }

    fn write(&self, _buf: &[u8]) -> axerrno::LinuxResult<usize> {
        Err(axerrno::LinuxError::EPERM)
    }

    fn stat(&self) -> axerrno::LinuxResult<super::ctypes::stat> {
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

    fn poll(&self) -> axerrno::LinuxResult<axio::PollState> {
        Ok(axio::PollState {
            readable: true,
            writable: true,
        })
    }

    fn set_nonblocking(&self, _nonblocking: bool) -> axerrno::LinuxResult {
        Ok(())
    }
}

#[cfg(feature = "fd")]
impl FileLike for Stdout {
    fn read(&self, _buf: &mut [u8]) -> axerrno::LinuxResult<usize> {
        Err(axerrno::LinuxError::EPERM)
    }

    fn write(&self, buf: &[u8]) -> axerrno::LinuxResult<usize> {
        Ok(self.write_locked(buf)?)
    }

    fn stat(&self) -> axerrno::LinuxResult<super::ctypes::stat> {
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

    fn poll(&self) -> axerrno::LinuxResult<axio::PollState> {
        Ok(axio::PollState {
            readable: true,
            writable: true,
        })
    }

    fn set_nonblocking(&self, _nonblocking: bool) -> axerrno::LinuxResult {
        Ok(())
    }
}
