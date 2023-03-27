#ifndef _ARPA_INET_H
#define	_ARPA_INET_H	1

#include <sys/socket.h>

const char *inet_ntop(int __af, const void *__restrict__ __cp, char *__restrict__ __buf, socklen_t __len);

#endif /* arpa/inet.h */
