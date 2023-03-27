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