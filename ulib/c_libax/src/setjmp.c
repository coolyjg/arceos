#include <setjmp.h>
#include <stdio.h>

// TODO
_Noreturn void longjmp(jmp_buf, int)
{
    return;
}

// TODO
int setjmp(jmp_buf)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}