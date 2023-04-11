use core::arch::asm;
use memory_addr::VirtAddr;

#[repr(C)]
#[derive(Debug, Default, Clone, Copy)]
pub struct TrapFrame {
    /// General-purpose registers (R0..R30).
    pub r: [u64; 31],
    /// User Stack Pointer (SP_EL0).
    pub usp: u64,
    /// Exception Link Register (ELR_EL1).
    pub elr: u64,
    /// Saved Process Status Register (SPSR_EL1).
    pub spsr: u64,
}

#[repr(C)]
#[derive(Debug)]
pub struct TaskContext {
    pub sp: u64,
    pub tpidr_el0: u64,
    pub r19: u64,
    pub r20: u64,
    pub r21: u64,
    pub r22: u64,
    pub r23: u64,
    pub r24: u64,
    pub r25: u64,
    pub r26: u64,
    pub r27: u64,
    pub r28: u64,
    pub r29: u64,
    pub lr: u64, // r30
    pub q0: u128,
    pub q1: u128,
    pub q2: u128,
    pub q3: u128,
    pub q4: u128,
    pub q5: u128,
    pub q6: u128,
    pub q7: u128,
    pub q8: u128,
    pub q9: u128,
    pub q10: u128,
    pub q11: u128,
    pub q12: u128,
    pub q13: u128,
    pub q14: u128,
    pub q15: u128,
    pub q16: u128,
    pub q17: u128,
    pub q18: u128,
    pub q19: u128,
    pub q20: u128,
    pub q21: u128,
    pub q22: u128,
    pub q23: u128,
    pub q24: u128,
    pub q25: u128,
    pub q26: u128,
    pub q27: u128,
    pub q28: u128,
    pub q29: u128,
    pub q30: u128,
    pub q31: u128,
    pub fpcr: u32,
    pub fpsr: u32,
}

impl TaskContext {
    pub const fn new() -> Self {
        unsafe { core::mem::MaybeUninit::zeroed().assume_init() }
    }

    pub fn init(&mut self, entry: usize, kstack_top: VirtAddr) {
        self.sp = kstack_top.as_usize() as u64;
        self.lr = entry as u64;
    }

    pub fn switch_to(&mut self, next_ctx: &Self) {
        unsafe { context_switch(self, next_ctx) }
    }
}

#[naked]
unsafe extern "C" fn context_switch(_current_task: &mut TaskContext, _next_task: &TaskContext) {
    asm!(
        "
        // save old context (callee-saved registers)
        stp     x29, x30, [x0, 12 * 8]
        stp     x27, x28, [x0, 10 * 8]
        stp     x25, x26, [x0, 8 * 8]
        stp     x23, x24, [x0, 6 * 8]
        stp     x21, x22, [x0, 4 * 8]
        stp     x19, x20, [x0, 2 * 8]
        mov     x19, sp
        mrs     x20, tpidr_el0
        stp     x19, x20, [x0]

        // save fp/neon context
        stp     q0, q1, [x0, 14 * 8]
        stp     q2, q3, [x0, 18 * 8]
        stp     q4, q5, [x0, 22 * 8]
        stp     q6, q7, [x0, 26 * 8]
        stp     q8, q9, [x0, 30 * 8]
        stp     q10, q11, [x0, 34 * 8]
        stp     q12, q13, [x0, 38 * 8]
        stp     q14, q15, [x0, 42 * 8]
        stp     q16, q17, [x0, 46 * 8]
        stp     q18, q19, [x0, 50 * 8]
        stp     q20, q21, [x0, 54 * 8]
        stp     q22, q23, [x0, 58 * 8]
        stp     q24, q25, [x0, 62 * 8]
        stp     q26, q27, [x0, 66 * 8]
        stp     q28, q29, [x0, 70 * 8]
        stp     q30, q31, [x0, 74 * 8]
        mrs     x19, fpcr
        str     x19, [x0, 78 * 8]
        mrs     x20, fpsr
        str     x20, [x0, 79 * 8]

        // restore fp/neon register
        ldp     q0, q1, [x1, 14 * 8]
        ldp     q2, q3, [x1, 18 * 8]
        ldp     q4, q5, [x1, 22 * 8]
        ldp     q6, q7, [x1, 26 * 8]
        ldp     q8, q9, [x1, 30 * 8]
        ldp     q10, q11, [x1, 34 * 8]
        ldp     q12, q13, [x1, 38 * 8]
        ldp     q14, q15, [x1, 42 * 8]
        ldp     q16, q17, [x1, 46 * 8]
        ldp     q18, q19, [x1, 50 * 8]
        ldp     q20, q21, [x1, 54 * 8]
        ldp     q22, q23, [x1, 58 * 8]
        ldp     q24, q25, [x1, 62 * 8]
        ldp     q26, q27, [x1, 66 * 8]
        ldp     q28, q29, [x1, 70 * 8]
        ldp     q30, q31, [x1, 74 * 8]
        ldr     x19, [x1, 78 * 8]
        msr     fpcr, x19
        ldr     x20, [x1, 79 * 8]
        msr     fpsr, x20

        // restore new context
        ldp     x19, x20, [x1]
        mov     sp, x19
        msr     tpidr_el0, x20
        ldp     x19, x20, [x1, 2 * 8]
        ldp     x21, x22, [x1, 4 * 8]
        ldp     x23, x24, [x1, 6 * 8]
        ldp     x25, x26, [x1, 8 * 8]
        ldp     x27, x28, [x1, 10 * 8]
        ldp     x29, x30, [x1, 12 * 8]

        ret",
        options(noreturn),
    )
}
