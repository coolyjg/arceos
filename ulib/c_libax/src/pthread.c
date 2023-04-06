#include <pthread.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>


int pthread_mutex_init(pthread_mutex_t *restrict m, const pthread_mutexattr_t *restrict a)
{
	*m = (pthread_mutex_t){0};
	if (a) m->_m_type = a->__attr;
	return 0;
}

//TODO
int pthread_mutex_lock(pthread_mutex_t *m)
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

int pthread_setcancelstate(int new, int *old)
{
    if (new > 2U) return EINVAL;
	struct pthread *self = __pthread_self();
	if (old) *old = self->canceldisable;
	self->canceldisable = new;
	return 0;
}

void __pthread_testcancel()
{
	
}

int pthread_setcanceltype(int new, int *old)
{
	struct pthread *self = __pthread_self();
	if (new > 1U) return EINVAL;
	if (old) *old = self->cancelasync;
	self->cancelasync = new;
	if (new) pthread_testcancel();
	return 0;
}

pthread_t pthread_self(void)
{
    return (pthread_t)0;
}

//TODO
int pthread_setname_np(pthread_t thread, const char *name)
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

static void init_cancellation()
{

}

int pthread_cancel(pthread_t t)
{
    static int init;
	if (!init) {
		init_cancellation();
		init = 1;
	}

    t->cancel = 1;
	// a_store(&t->cancel, 1);
	if (t == pthread_self()) {
		if (t->canceldisable == PTHREAD_CANCEL_ENABLE && t->cancelasync)
			pthread_exit(PTHREAD_CANCELED);
		return 0;
	}
	return pthread_kill(t, SIGCANCEL);
}

// TODO
int pthread_join(pthread_t __th, void **__thread_return)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

int pthread_cond_init(pthread_cond_t *restrict c, const pthread_condattr_t *restrict a)
{
	*c = (pthread_cond_t){0};
	if (a) {
		c->_c_clock = a->__attr & 0x7fffffff;
		if (a->__attr>>31) c->_c_shared = (void *)-1;
	}
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

#define DEFAULT_STACK_SIZE 131072
#define DEFAULT_GUARD_SIZE 8192

int pthread_attr_init(pthread_attr_t *a)
{
	*a = (pthread_attr_t){0};
	// __acquire_ptc();
	a->_a_stacksize = DEFAULT_STACK_SIZE;
	a->_a_guardsize = DEFAULT_GUARD_SIZE;
	// __release_ptc();
	return 0;
}

int pthread_attr_getstacksize(const pthread_attr_t *restrict a, size_t *restrict size)
{
	*size = a->_a_stacksize;
	return 0;
}

int pthread_attr_setstacksize(pthread_attr_t *a, size_t size)
{
	if (size-PTHREAD_STACK_MIN > SIZE_MAX/4) return EINVAL;
	a->_a_stackaddr = 0;
	a->_a_stacksize = size;
	return 0;
}
