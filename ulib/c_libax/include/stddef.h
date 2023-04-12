#ifndef __STDDEF_H__
#define __STDDEF_H__

#include <stdint.h>

/* size_t is used for memory object sizes */
typedef uintptr_t size_t;
typedef intptr_t ssize_t;

typedef long ptrdiff_t;

typedef unsigned gid_t;
typedef unsigned uid_t;

typedef int pid_t;
typedef long loff_t;
typedef long clock_t;
// typedef unsigned long size_t;

typedef int clockid_t;

#define NULL ((void *)0)

#if __GNUC__ > 3
#define offsetof(type, member) __builtin_offsetof(type, member)
#else
#define offsetof(type, member) ((size_t)((char *)&(((type *)0)->member) - (char *)0))
#endif

#endif // __STDDEF_H__
