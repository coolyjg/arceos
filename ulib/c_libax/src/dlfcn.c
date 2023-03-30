#include <dlfcn.h>
#include <stdio.h>

// TODO
int dladdr(const void *__address, Dl_info *__info)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO
void *dlopen(const char *__file, int __mode)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return NULL;
}

// TODO
char *dlerror(void)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return NULL;
}

// TODO
void *dlsym(void *__restrict__ __handle, const char *__restrict__ __name)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return NULL;
}

// TODO
int dlclose(void *__handle)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}