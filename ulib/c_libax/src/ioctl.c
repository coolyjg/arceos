#include <sys/ioctl.h>
#include <stdio.h>

//TODO
int ioctl(int __fd, unsigned long __request, ...)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}