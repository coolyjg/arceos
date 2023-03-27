#include <sys/socket.h>
#include <stdio.h>

//TODO
int getsockopt(int __fd, int __level, int __optname, void *__restrict__ __optval, socklen_t *__restrict__ __optlen)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

//TODO
int setsockopt(int __fd, int __level, int __optname, const void *__optval, socklen_t __optlen)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

//TODO
int socket(int __domain, int __type, int __protocol)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

//TODO
int bind(int __fd, const struct sockaddr * __addr, socklen_t __len)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

//TODO
int connect(int __fd, const struct sockaddr * __addr, socklen_t __len)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}