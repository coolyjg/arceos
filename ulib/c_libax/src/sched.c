#include <sched.h>
#include <stdio.h>

// TODO
int sched_setaffinity(pid_t __pid, size_t __cpusetsize, const cpu_set_t *__cpuset)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}