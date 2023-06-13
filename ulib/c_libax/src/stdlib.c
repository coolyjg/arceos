#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <libax.h>

char *program_invocation_short_name = "dummy";
char *program_invocation_name = "dummy";

#define __DECONST(type, var) ((type)(uintptr_t)(const void *)(var))

void srand(unsigned s)
{
    ax_srand(s);
}

int rand(void)
{
    return ax_rand_u32();
}

// TODO
long random(void)
{
    return (long)ax_rand_u32();
}

#ifdef AX_CONFIG_ALLOC

void *malloc(size_t size)
{
    void *ret = ax_malloc(size);

    return ret;
}

void *calloc(size_t m, size_t n)
{
    void *mem = ax_malloc(m * n);

    return memset(mem, 0, n * m);
}

void *realloc(void *memblock, size_t size)
{
    // printf("realloc: addr = %p\n", memblock);
    if (!memblock) {
        void *ret = calloc(size, 1);
        // printf("realloc return: addr = %p\n", ret);
        return ret;
    }

    size_t o_size = *(size_t *)(memblock - 8);

    void *mem = ax_malloc(size);
    // printf("realloc return : addr = %p\n", mem);

    for (int i = 0; i < (o_size < size ? o_size : size); i++)
        ((char *)mem)[i] = ((char *)memblock)[i];

    ax_free(memblock);
    return mem;
}

void free(void *addr)
{
    if (!addr) {
        printf("NULL pointer called free\n");
        return;
    }
    return ax_free(addr);
}

#endif

_Noreturn void abort(void)
{
    ax_panic();
    __builtin_unreachable();
}

// TODO:
int __clzdi2(int a)
{
    return 0;
}

long strtol(const char *restrict nptr, char **restrict endptr, int base)
{
    const char *s;
    unsigned long acc;
    unsigned char c;
    unsigned long qbase, cutoff;
    int neg, any, cutlim;

    s = nptr;
    if (base < 0 || base == 1 || base > 36) {
        errno = EINVAL;
        any = 0;
        acc = 0;
        goto exit;
    }

    do {
        c = *s++;
    } while (isspace(c));
    if (c == '-') {
        neg = 1;
        c = *s++;
    } else {
        neg = 0;
        if (c == '+')
            c = *s++;
    }
    if ((base == 0 || base == 16) && c == '0' && (*s == 'x' || *s == 'X')) {
        c = s[1];
        s += 2;
        base = 16;
    }
    if (base == 0)
        base = c == '0' ? 8 : 10;

    qbase = (unsigned int)base;
    cutoff = neg ? (unsigned long)LONG_MAX - (unsigned long)(LONG_MIN + LONG_MAX) : LONG_MAX;
    cutlim = cutoff % qbase;
    cutoff /= qbase;
    for (acc = 0, any = 0;; c = *s++) {
        if (!isascii(c))
            break;
        if (isdigit(c))
            c -= '0';
        else if (isalpha(c))
            c -= isupper(c) ? 'A' - 10 : 'a' - 10;
        else
            break;
        if (c >= base)
            break;
        if (any < 0 || acc > cutoff || (acc == cutoff && c > cutlim))
            any = -1;
        else {
            any = 1;
            acc *= qbase;
            acc += c;
        }
    }

    if (any < 0) {
        acc = neg ? LONG_MIN : LONG_MAX;
        errno = ERANGE;
    } else if (neg)
        acc = -acc;

exit:
    if (endptr != 0)
        *endptr = __DECONST(char *, any ? s - 1 : nptr);
    return acc;
}

unsigned long strtoul(const char *nptr, char **endptr, int base)
{
    const char *s = nptr;
    unsigned long acc;
    unsigned char c;
    unsigned long cutoff;
    int neg = 0, any, cutlim;

    if (base < 0 || base == 1 || base > 36) {
        errno = EINVAL;
        any = 0;
        acc = 0;
        goto exit;
    }

    do {
        c = *s++;
    } while (isspace(c));
    if (c == '-') {
        neg = 1;
        c = *s++;
    } else if (c == '+')
        c = *s++;
    if ((base == 0 || base == 16) && c == '0' && (*s == 'x' || *s == 'X')) {
        c = s[1];
        s += 2;
        base = 16;
    }
    if (base == 0)
        base = c == '0' ? 8 : 10;
    cutoff = (unsigned long)ULONG_MAX / (unsigned long)base;
    cutlim = (unsigned long)ULONG_MAX % (unsigned long)base;

    for (acc = 0, any = 0;; c = *s++) {
        if (!isascii(c))
            break;
        if (isdigit(c))
            c -= '0';
        else if (isalpha(c))
            c -= isupper(c) ? 'A' - 10 : 'a' - 10;
        else
            break;
        if (c >= base)
            break;
        if (any < 0 || acc > cutoff || (acc == cutoff && c > cutlim))
            any = -1;
        else {
            any = 1;
            acc *= base;
            acc += c;
        }
    }
    if (any < 0) {
        acc = ULONG_MAX;
        errno = ERANGE;
    } else if (neg)
        acc = -acc;
exit:
    if (endptr != 0)
        *endptr = __DECONST(char *, any ? s - 1 : nptr);
    return acc;
}

long long strtoll(const char *nptr, char **endptr, int base)
{
    const char *s;
    unsigned long long acc;
    unsigned char c;
    unsigned long long qbase, cutoff;
    int neg, any, cutlim;

    s = nptr;
    if (base < 0 || base == 1 || base > 36) {
        errno = EINVAL;
        any = 0;
        acc = 0;
        goto exit;
    }

    do {
        c = *s++;
    } while (isspace(c));
    if (c == '-') {
        neg = 1;
        c = *s++;
    } else {
        neg = 0;
        if (c == '+')
            c = *s++;
    }
    if ((base == 0 || base == 16) && c == '0' && (*s == 'x' || *s == 'X')) {
        c = s[1];
        s += 2;
        base = 16;
    }
    if (base == 0)
        base = c == '0' ? 8 : 10;

    qbase = (unsigned int)base;
    cutoff = neg ? (unsigned long long)LLONG_MAX - (unsigned long long)(LLONG_MIN + LLONG_MAX)
                 : LLONG_MAX;
    cutlim = cutoff % qbase;
    cutoff /= qbase;
    for (acc = 0, any = 0;; c = *s++) {
        if (!isascii(c))
            break;
        if (isdigit(c))
            c -= '0';
        else if (isalpha(c))
            c -= isupper(c) ? 'A' - 10 : 'a' - 10;
        else
            break;
        if (c >= base)
            break;
        if (any < 0 || acc > cutoff || (acc == cutoff && c > cutlim))
            any = -1;
        else {
            any = 1;
            acc *= qbase;
            acc += c;
        }
    }

    if (any < 0) {
        errno = ERANGE;
        acc = neg ? LLONG_MIN : LLONG_MAX;
    } else if (neg)
        acc = -acc;

exit:
    if (endptr != 0)
        *endptr = __DECONST(char *, any ? s - 1 : nptr);
    return acc;
}

unsigned long long strtoull(const char *nptr, char **endptr, int base)
{
    const char *s = nptr;
    unsigned long long acc;
    unsigned char c;
    unsigned long long qbase, cutoff;
    int neg, any, cutlim;

    if (base < 0 || base == 1 || base > 36) {
        errno = EINVAL;
        any = 0;
        acc = 0;
        goto exit;
    }

    do {
        c = *s++;
    } while (isspace(c));
    if (c == '-') {
        neg = 1;
        c = *s++;
    } else {
        neg = 0;
        if (c == '+')
            c = *s++;
    }
    if ((base == 0 || base == 16) && c == '0' && (*s == 'x' || *s == 'X')) {
        c = s[1];
        s += 2;
        base = 16;
    }
    if (base == 0)
        base = c == '0' ? 8 : 10;

    qbase = (unsigned int)base;
    cutoff = (unsigned long long)ULLONG_MAX / qbase;
    cutlim = (unsigned long long)ULLONG_MAX % qbase;
    for (acc = 0, any = 0;; c = *s++) {
        if (!isascii(c))
            break;
        if (isdigit(c))
            c -= '0';
        else if (isalpha(c))
            c -= isupper(c) ? 'A' - 10 : 'a' - 10;
        else
            break;
        if (c >= base)
            break;
        if (any < 0 || acc > cutoff || (acc == cutoff && c > cutlim))
            any = -1;
        else {
            any = 1;
            acc *= qbase;
            acc += c;
        }
    }
    if (any < 0) {
        errno = ERANGE;
        acc = ULLONG_MAX;
    } else if (neg)
        acc = -acc;

exit:
    if (endptr != 0)
        *endptr = __DECONST(char *, any ? s - 1 : nptr);
    return acc;
}

_Noreturn void exit(int status)
{
    ax_exit(status);
}

long long llabs(long long a)
{
    return a > 0 ? a : -a;
}

int abs(int a)
{
    return a > 0 ? a : -a;
}

long long atoll(const char *s)
{
    long long n = 0;
    int neg = 0;
    while (isspace(*s)) s++;
    switch (*s) {
    case '-':
        neg = 1;
    case '+':
        s++;
    }
    /* Compute n as a negative number to avoid overflow on LLONG_MIN */
    while (isdigit(*s)) n = 10 * n - (*s++ - '0');
    return neg ? n : -n;
}

#ifdef AX_CONFIG_FP_SIMD
float strtof(const char *restrict s, char **restrict p)
{
    return ax_strtof(s, p);
}

double strtod(const char *restrict s, char **restrict p)
{
    return ax_strtod(s, p);
}

// TODO: precision may not be enough
long double strtold(const char *restrict s, char **restrict p)
{
    return (long double)strtod(s, p);
}

#endif

// TODO
void qsort(void *, size_t, size_t, int (*)(const void *, const void *))
{
    unimplemented();
    return;
}

// TODO
int mkostemp(char *__template, int __flags)
{
    unimplemented();
    return 0;
}

void srandom(unsigned int s)
{
    ax_srand(s);
}

// TODO
int system(const char *)
{
    unimplemented();
    return 0;
}
