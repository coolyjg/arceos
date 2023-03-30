#ifndef _SYS_UIO_H
#define _SYS_UIO_H 1

#include <stddef.h>

struct iovec {
    void *iov_base; /* Pointer to data.  */
    size_t iov_len; /* Length of data.  */
};

#define IOV_MAX 1024

ssize_t writev(int __fd, const struct iovec *__iovec, int __count);

#endif /* sys/uio.h */
