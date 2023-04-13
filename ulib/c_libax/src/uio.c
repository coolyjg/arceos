#include <stdio.h>
#include <sys/uio.h>

// TODO
ssize_t writev(int __fd, const struct iovec *__iovec, int __count)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}