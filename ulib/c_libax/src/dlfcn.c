#include <dlfcn.h>
#include <stdio.h>
#include <pthread.h>

// TODO
int dladdr(const void *__address, Dl_info *__info)
{
    return 0;
}

// TODO
void *dlopen(const char *__file, int __mode)
{
    return NULL;
}

char *dlerror()
{
	struct pthread* self = __pthread_self();
	if (!self->dlerror_flag) return 0;
	self->dlerror_flag = 0;
	char *s = self->dlerror_buf;
	if (s == (void *)-1)
		return "Dynamic linker failed to allocate memory for error message";
	else
		return s;
}

// TODO
void *dlsym(void *__restrict__ __handle, const char *__restrict__ __name)
{
    return NULL;
}

// TODO
int dlclose(void *p)
{
    return 0;
}