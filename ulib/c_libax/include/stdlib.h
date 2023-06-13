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

#ifdef AX_CONFIG_ALLOC
void *malloc(size_t size);
void free(void *addr);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *memblock, size_t size);
#endif

_Noreturn void abort(void);
char *getenv(const char *name);

#ifdef AX_CONFIG_FP_SIMD
float strtof(const char *__restrict, char **__restrict);
double strtod(const char *__restrict, char **__restrict);
#endif

long strtol(const char *__restrict, char **__restrict, int);
unsigned long strtoul(const char *nptr, char **endptr, int base);
long long strtoll(const char *nptr, char **endptr, int base);
unsigned long long strtoull(const char *nptr, char **endptr, int base);

#ifdef AX_CONFIG_FP_SIMD
float strtof(const char *__restrict, char **__restrict);
double strtod(const char *__restrict, char **__restrict);
long double strtold(const char *__restrict, char **__restrict);
#endif

void qsort(void *, size_t, size_t, int (*)(const void *, const void *));

long long atoll(const char *nptr);

_Noreturn void exit(int);

long long llabs(long long x);
int abs(int x);
int mkostemp(char *__template, int __flags);
int setenv(const char *__name, const char *__value, int __replace);
int unsetenv(const char *__name);
void srandom(unsigned int __seed);

int system(const char *);

#endif //__STDLIB_H__
