#ifndef __STDLIB_H__
#define __STDLIB_H__

#include <stddef.h>

int rand(void);
void srand(unsigned);

// #ifdef AX_CONFIG_ALLOC
void *malloc(size_t size);
void *calloc(size_t __nmemb, size_t __size);
void *realloc(void *memblock, size_t size);
void free(void *addr);
// #endif

long long strtoll(const char *__restrict__ __nptr, char **__restrict__ __endptr, int __base);
long strtol(const char *__restrict__ __nptr, char **__restrict__ __endptr, int __base);

_Noreturn void abort(void);
char *getenv(const char *name);

#endif //__STDLIB_H__
