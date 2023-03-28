#include <stddef.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>

// TODO:
size_t strftime(char *__restrict__ _Buf, size_t _SizeInBytes, const char *__restrict__ _Format,
                const struct tm *__restrict__ _Tm)
{
    return 0;
}

// TODO:
struct tm *gmtime(const time_t *timer)
{
    return NULL;
}

// TODO:
struct tm *localtime(const time_t *timep)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO:
time_t time(time_t *t)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO:
int gettimeofday(struct timeval *tv, struct timezone *tz)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO:
int utimes(const char *filename, const struct timeval times[2])
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

//TODO
struct tm *localtime_r(const time_t *__restrict__ __timer, struct tm *__restrict__ __tp)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return NULL;
}

//TODO
int nanosleep(const struct timespec *__requested_time, struct timespec *__remaining)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

//TODO
void tzset(void)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return ;
}

//TODO
int setitimer(int __which, const struct itimerval *__restrict__ __new, struct itimerval *__restrict__ __old)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

//TODO
int clock_gettime(clockid_t __clock_id, struct timespec *__tp)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}