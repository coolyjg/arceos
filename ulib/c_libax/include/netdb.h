#ifndef _NETDB_H
#define _NETDB_H

#include "errno.h"
#include "netinet/in.h"
#include "sys/socket.h"

struct addrinfo {
    int ai_flags;             /* Input flags.  */
    int ai_family;            /* Protocol family for socket.  */
    int ai_socktype;          /* Socket type.  */
    int ai_protocol;          /* Protocol for socket.  */
    socklen_t ai_addrlen;     /* Length of socket address.  */
    struct sockaddr *ai_addr; /* Socket address for socket.  */
    char *ai_canonname;       /* Canonical name for service location.  */
    struct addrinfo *ai_next; /* Pointer to next in list.  */
};

struct aibuf {
    struct addrinfo ai;
    union sa {
        struct sockaddr_in sin;
        struct sockaddr_in6 sin6;
    } sa;
    volatile int lock[1];
    short slot, ref;
};

struct service {
    uint16_t port;
    unsigned char proto, socktype;
};

struct address {
    int family;
    unsigned scopeid;
    uint8_t addr[16];
    int sortkey;
};

#define MAXADDRS 48
#define MAXSERVS 2

#define EAI_BADFLAGS -1
#define EAI_NONAME   -2
#define EAI_AGAIN    -3
#define EAI_FAIL     -4
#define EAI_FAMILY   -6
#define EAI_SOCKTYPE -7
#define EAI_SERVICE  -8
#define EAI_MEMORY   -10
#define EAI_SYSTEM   -11
#define EAI_OVERFLOW -12

int getaddrinfo(const char *__restrict__ __name, const char *__restrict__ __service,
                const struct addrinfo *__restrict__ __req, struct addrinfo **__restrict__ __pai);
void freeaddrinfo(struct addrinfo *__ai);

const char *gai_strerror(int __ecode);

#define AI_PASSIVE     0x01
#define AI_CANONNAME   0x02
#define AI_NUMERICHOST 0x04
#define AI_V4MAPPED    0x08
#define AI_ALL         0x10
#define AI_ADDRCONFIG  0x20
#define AI_NUMERICSERV 0x400

#endif