#ifndef _ARPA_INET_H
#define _ARPA_INET_H 1

#include <sys/socket.h>

const char *inet_ntop(int __af, const void *__restrict__ __cp, char *__restrict__ __buf,
                      socklen_t __len);
int inet_pton(int __af, const char *__restrict__ __cp, void *__restrict__ __buf);

#endif /* arpa/inet.h */
