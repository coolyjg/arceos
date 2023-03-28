#include <stdio.h>
#include <dlfcn.h>

//TODO
int dladdr(const void *__address, Dl_info *__info)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}
