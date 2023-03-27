#ifndef _SYS_UIO_H
#define _SYS_UIO_H	1


#include <stddef.h>
struct iovec
  {
    void *iov_base;	/* Pointer to data.  */
    size_t iov_len;	/* Length of data.  */
  };

#endif /* sys/uio.h */
