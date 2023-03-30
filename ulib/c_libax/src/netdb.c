#include <netdb.h>
#include <stdio.h>

// TODO
int getaddrinfo(const char *__restrict__ __name, const char *__restrict__ __service,
                const struct addrinfo *__restrict__ __req, struct addrinfo **__restrict__ __pai)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO
const char *gai_strerror(int __ecode)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return NULL;
}

// TODO
void freeaddrinfo(struct addrinfo *__ai)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return;
}