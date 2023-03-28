#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <libax.h>

void srand(unsigned s)
{
    ax_srand(s);
}

int rand(void)
{
    return ax_rand_u32();
}

// #ifdef AX_CONFIG_ALLOC

void *malloc(size_t size)
{
    return ax_malloc(size);
}

//TODO
void *calloc(size_t nmemb, size_t size)
{
    void *mem = ax_malloc(nmemb * size);

    for (int i = 0; i< nmemb * size; i++)
        mem[i] = 0;
    
    return mem;
}

void *realloc(void *memblock, size_t size)
{
    size_t o_size = *(size_t *)(memblock - 8);

    void *mem = ax_malloc(size);

    for (int i = 0; i < (o_size < size ? o_size : size); i++)
        ((char *)mem)[i] = ((char *)memblock)[i];

    ax_free(memblock);
    return mem;
}

void free(void *addr)
{
    return ax_free(addr);
}

// #endif

_Noreturn void abort(void)
{
    ax_panic();
    __builtin_unreachable();
}

// TODO:
char *getenv(const char *name)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO:
int __clzdi2(int a)
{
    return 0;
}

//TODO
long long strtoll(const char *__restrict__ __nptr, char **__restrict__ __endptr, int __base)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

//TODO
long strtol(const char *__restrict__ __nptr, char **__restrict__ __endptr, int __base)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

//TODO
unsigned long long strtoull(const char *__restrict__ __nptr, char **__restrict__ __endptr, int __base)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

//TODO
long random(void)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

//TODO
long double strtold(const char *__restrict__ __nptr, char **__restrict__ __endptr)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

//TODO
double strtod(const char *__restrict__ __nptr, char **__restrict__ __endptr)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

//TODO
void qsort (void *, size_t, size_t, int (*)(const void *, const void *))
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return ;
}

//TODO
unsigned long strtoul(const char *__restrict__ __nptr, char **__restrict__ __endptr, int __base)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

_Noreturn void exit(int __status)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    __builtin_unreachable();
}

//TODO
long long llabs(long long __x)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

//TODO
int mkostemp(char *__template, int __flags)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

//TODO
long long atoll(const char *__nptr)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

//TODO
int setenv(const char *__name, const char *__value, int __replace)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

//TODO
int unsetenv(const char *__name)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

//TODO
void srandom(unsigned int __seed)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return ;
}

//TODO
int abs(int __x)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}