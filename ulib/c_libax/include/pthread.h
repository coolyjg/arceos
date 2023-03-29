#ifndef _PTHREAD_H
#define _PTHREAD_H	1

#include <stddef.h>

typedef unsigned long int pthread_t;
enum
{
  PTHREAD_CANCEL_ENABLE,
#define PTHREAD_CANCEL_ENABLE   PTHREAD_CANCEL_ENABLE
  PTHREAD_CANCEL_DISABLE
#define PTHREAD_CANCEL_DISABLE  PTHREAD_CANCEL_DISABLE
};

enum
{
  PTHREAD_CANCEL_DEFERRED,
#define PTHREAD_CANCEL_DEFERRED	PTHREAD_CANCEL_DEFERRED
  PTHREAD_CANCEL_ASYNCHRONOUS
#define PTHREAD_CANCEL_ASYNCHRONOUS	PTHREAD_CANCEL_ASYNCHRONOUS
};

#define __SIZEOF_PTHREAD_ATTR_T 56

union pthread_attr_t
{
  char __size[__SIZEOF_PTHREAD_ATTR_T];
  long int __align;
};
#ifndef __have_pthread_attr_t
typedef union pthread_attr_t pthread_attr_t;
# define __have_pthread_attr_t 1
#endif

// #if defined(__NEED_pthread_condattr_t) && !defined(__DEFINED_pthread_condattr_t)
typedef struct { unsigned __attr; } pthread_condattr_t;
#define __DEFINED_pthread_condattr_t
// #endif

typedef struct __pthread_internal_list
{
  struct __pthread_internal_list *__prev;
  struct __pthread_internal_list *__next;
} __pthread_list_t;

typedef struct __pthread_internal_slist
{
  struct __pthread_internal_slist *__next;
} __pthread_slist_t;

#define __SIZEOF_PTHREAD_MUTEX_T 40

struct __pthread_mutex_s
{
  int __lock;
  unsigned int __count;
  int __owner;
#ifdef __x86_64__
  unsigned int __nusers;
#endif
  /* KIND must stay at this position in the structure to maintain
     binary compatibility with static initializers.  */
  int __kind;
#ifdef __x86_64__
  short __spins;
  short __elision;
  __pthread_list_t __list;
# define __PTHREAD_MUTEX_HAVE_PREV      1
#else
  unsigned int __nusers;
  __extension__ union
  {
    struct
    {
      short __espins;
      short __eelision;
# define __spins __elision_data.__espins
# define __elision __elision_data.__eelision
    } __elision_data;
    __pthread_slist_t __list;
  };
# define __PTHREAD_MUTEX_HAVE_PREV      0
#endif
};

typedef union
{
  struct __pthread_mutex_s __data;
  char __size[__SIZEOF_PTHREAD_MUTEX_T];
  long int __align;
} pthread_mutex_t;

typedef union
{
  __extension__ unsigned long long int __value64;
  struct
  {
    unsigned int __low;
    unsigned int __high;
  } __value32;
} __atomic_wide_counter;

#define __LOCK_ALIGNMENT
#define __SIZEOF_PTHREAD_COND_T 48
#define __SIZEOF_PTHREAD_MUTEXATTR_T 4

struct __pthread_cond_s
{
  __atomic_wide_counter __wseq;
  __atomic_wide_counter __g1_start;
  unsigned int __g_refs[2] __LOCK_ALIGNMENT;
  unsigned int __g_size[2];
  unsigned int __g1_orig_size;
  unsigned int __wrefs;
  unsigned int __g_signals[2];
};

typedef union
{
  struct __pthread_cond_s __data;
  char __size[__SIZEOF_PTHREAD_COND_T];
  __extension__ long long int __align;
} pthread_cond_t;

#ifndef __have_pthread_attr_t
typedef union pthread_attr_t pthread_attr_t;
# define __have_pthread_attr_t 1
#endif

#define PTHREAD_MUTEX_INITIALIZER {0}

//TODO: this is not a musl-like struct
typedef union
{
  char __size[__SIZEOF_PTHREAD_MUTEXATTR_T];
  int __align;
} pthread_mutexattr_t;

int pthread_mutex_init(pthread_mutex_t *__restrict __mutex, const pthread_mutexattr_t *__restrict __attr);
int pthread_mutex_lock(pthread_mutex_t *__mutex);
int pthread_mutex_unlock(pthread_mutex_t *__mutex);
int pthread_mutex_trylock(pthread_mutex_t *__mutex);

int pthread_setcancelstate(int __state, int *__oldstate);
int pthread_setcanceltype(int __type, int *__oldtype);

pthread_t pthread_self(void);
int pthread_setname_np(pthread_t __target_thread, const char *__name);

int pthread_create(pthread_t *__restrict__ __newthread, const pthread_attr_t *__restrict__ __attr, void *(*__start_routine)(void *), void *__restrict__ __arg);
int pthread_cancel(pthread_t __th);
int pthread_join(pthread_t __th, void **__thread_return);

int pthread_cond_init(pthread_cond_t *__restrict__ __cond, const pthread_condattr_t *__restrict__ __cond_attr);
int pthread_cond_signal(pthread_cond_t *__cond);
int pthread_cond_wait(pthread_cond_t *__restrict__ __cond, pthread_mutex_t *__restrict__ __mutex);
int pthread_attr_init(pthread_attr_t *__attr);

int pthread_attr_getstacksize(const pthread_attr_t *__restrict__ __attr, size_t *__restrict__ __stacksize);
int pthread_attr_setstacksize(pthread_attr_t *__attr, size_t __stacksize);

#endif