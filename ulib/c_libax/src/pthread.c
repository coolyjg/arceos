#include <pthread.h>
#include <stdio.h>

// TODO
int pthread_mutex_init(pthread_mutex_t *__restrict __mutex,
                       const pthread_mutexattr_t *__restrict __attr)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO
int pthread_mutex_lock(pthread_mutex_t *__mutex)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO
int pthread_mutex_unlock(pthread_mutex_t *__mutex)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO
int pthread_mutex_trylock(pthread_mutex_t *__mutex)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO
int pthread_setcancelstate(int __state, int *__oldstate)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO
int pthread_setcanceltype(int __type, int *__oldtype)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO
pthread_t pthread_self(void)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO
int pthread_setname_np(pthread_t __target_thread, const char *__name)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO
int pthread_create(pthread_t *__restrict__ __newthread, const pthread_attr_t *__restrict__ __attr,
                   void *(*__start_routine)(void *), void *__restrict__ __arg)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO
int pthread_cancel(pthread_t __th)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO
int pthread_join(pthread_t __th, void **__thread_return)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO
int pthread_cond_init(pthread_cond_t *__restrict__ __cond,
                      const pthread_condattr_t *__restrict__ __cond_attr)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO
int pthread_cond_signal(pthread_cond_t *__cond)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO
int pthread_cond_wait(pthread_cond_t *__restrict__ __cond, pthread_mutex_t *__restrict__ __mutex)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO
int pthread_attr_init(pthread_attr_t *__attr)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO
int pthread_attr_getstacksize(const pthread_attr_t *__restrict__ __attr,
                              size_t *__restrict__ __stacksize)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO
int pthread_attr_setstacksize(pthread_attr_t *__attr, size_t __stacksize)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}