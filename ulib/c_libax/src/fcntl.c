#include <stdio.h>
#include <fcntl.h>

// TODO:
int fcntl(int fd, int cmd, ... /* arg */)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO:
int open(const char *filename, int flags, ...)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    printf("open file: %s\n", filename);
    return -1;
}

//TODO
int posix_fadvise(int __fd, unsigned long __offset, unsigned long __len, int __advise)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}