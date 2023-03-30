#include <poll.h>
#include <stdio.h>

// TODO
int poll(struct pollfd *__fds, nfds_t __nfds, int __timeout)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}