#ifndef	_SYS_RESOURCE_H
#define	_SYS_RESOURCE_H

#include <bits/resource.h>

// typedef unsigned long long rlim_t;

int setrlimit(int __resource, const struct rlimit *__rlimits);
int getrlimit(int __resource, struct rlimit *__rlimits);

int getrusage(int __who, struct rusage *__usage);

#endif