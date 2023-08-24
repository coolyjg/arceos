#[macro_use]
mod macros;

mod syscall_id;

use syscall_id::SyscallId;

#[no_mangle]
pub fn syscall(syscall_id: usize, _args: [usize; 6]) -> isize {
    let syscall_name = SyscallId::try_from(syscall_id).unwrap_or(SyscallId::INVALID);
    debug!("syscall <= syscall_id: {}, syscall_name: {:?}", syscall_id, syscall_name);
    match syscall_name {
        SyscallId::INVALID => 0,
        SyscallId::READ => 0,
        #[cfg(feature = "multitask")]
        SyscallId::SCHED_YIELD => crate::sys_sched_yield(),
    }
}
