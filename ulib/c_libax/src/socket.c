#include <stdio.h>
#include <sys/socket.h>

// TODO
int getsockopt(int __fd, int __level, int __optname, void *__restrict__ __optval,
               socklen_t *__restrict__ __optlen)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO
int setsockopt(int __fd, int __level, int __optname, const void *__optval, socklen_t __optlen)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO
int socket(int __domain, int __type, int __protocol)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO
int bind(int __fd, const struct sockaddr *__addr, socklen_t __len)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO
int connect(int __fd, const struct sockaddr *__addr, socklen_t __len)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO
int listen(int __fd, int __n)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

//TODO
int accept (int, struct sockaddr *__restrict, socklen_t *__restrict)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO
int accept4(int __fd, struct sockaddr *__restrict __addr, socklen_t *__restrict__ __addr_len,
            int __flags)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO
int getpeername(int __fd, struct sockaddr *__restrict __addr, socklen_t *__restrict__ __len)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO
int getsockname(int __fd, struct sockaddr *__restrict __addr, socklen_t *__restrict__ __len)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO
int shutdown(int __fd, int __how)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

//TODO
ssize_t send (int, const void *, size_t, int)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

//TODO
ssize_t recv (int, void *, size_t, int)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}