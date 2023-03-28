#ifndef _SYS_UIO_H
#define _SYS_UIO_H	1


#include <stddef.h>
struct iovec
  {
    void *iov_base;	/* Pointer to data.  */
    size_t iov_len;	/* Length of data.  */
  };

#define IOV_MAX 1024


#endif /* sys/uio.h */
