#ifndef _SETJMP_H
#define _SETJMP_H

typedef unsigned long __jmp_buf[8];

typedef struct __jmp_buf_tag {
    __jmp_buf __jb;
    unsigned long __fl;
    unsigned long __ss[128 / sizeof(long)];
} jmp_buf[1];

int setjmp (jmp_buf);
_Noreturn void longjmp (jmp_buf, int);

#endif