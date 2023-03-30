#include <stdio.h>
#include <sys/resource.h>

// TODO
int getrlimit(int __resource, struct rlimit *__rlimits)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO
int setrlimit(int __resource, const struct rlimit *__rlimits)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO
int getrusage(int __who, struct rusage *__usage)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}