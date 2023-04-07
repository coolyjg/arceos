#ifndef __STDLIB_H__
#define __STDLIB_H__

#include <stddef.h>

#define RAND_MAX (0x7fffffff)

#define WEXITSTATUS(s) (((s)&0xff00) >> 8)
#define WTERMSIG(s)    ((s)&0x7f)
#define WIFEXITED(s)   (!WTERMSIG(s))
#define WIFSIGNALED(s) (((s)&0xffff) - 1U < 0xffu)

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

int rand(void);
void srand(unsigned);
long random(void);

void *malloc(size_t size);
void *calloc(size_t __nmemb, size_t __size);
void *realloc(void *memblock, size_t size);
void free(void *addr);

double strtod(const char *__restrict__ __nptr, char **__restrict__ __endptr);
long long strtoll(const char *__restrict__ __nptr, char **__restrict__ __endptr, int __base);
unsigned long strtoul(const char *__restrict__ __nptr, char **__restrict__ __endptr, int __base);
long strtol(const char *__restrict__ __nptr, char **__restrict__ __endptr, int __base);
long double strtold(const char *__restrict__ __nptr, char **__restrict__ __endptr);
unsigned long long strtoull(const char *__restrict__ __nptr, char **__restrict__ __endptr,
                            int __base);

_Noreturn void abort(void);
_Noreturn void exit(int __status);

char *getenv(const char *name);

void qsort(void *, size_t, size_t, int (*)(const void *, const void *));

long long llabs(long long __x);
int abs(int __x);

int mkostemp(char *__template, int __flags);
long long atoll(const char *__nptr);
int setenv(const char *__name, const char *__value, int __replace);
int unsetenv(const char *__name);
void srandom(unsigned int __seed);

int system (const char *);

#endif //__STDLIB_H__
