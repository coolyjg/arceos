#include <arpa/inet.h>
#include <stdio.h>

//TODO
const char *inet_ntop(int __af, const void *__restrict__ __cp, char *__restrict__ __buf, socklen_t __len)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return NULL;
}

//TODO
int inet_pton(int __af, const char *__restrict__ __cp, void *__restrict__ __buf)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}