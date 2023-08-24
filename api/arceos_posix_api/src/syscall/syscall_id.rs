use num_enum::TryFromPrimitive;

#[allow(clippy::upper_case_acronyms)]
#[repr(usize)]
#[derive(Debug, PartialEq, Eq, Clone, Copy, TryFromPrimitive)]
pub enum SyscallId {
    INVALID = 999,
    READ = 0,
    #[cfg(feature = "multitask")]
    SCHED_YIELD = 24,
}
