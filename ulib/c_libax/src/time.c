#include <stddef.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include "time.h"

long timezone = 0;
const char __utc[] = "UTC";

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
    unimplemented();
    return 0;
}

// TODO:
time_t time(time_t *t)
{
    unimplemented();
    return 0;
}

int gettimeofday(struct timeval *tv, struct timezone *tz)
{
    struct timespec ts;
    if (!tv)
        return 0;
    clock_gettime(CLOCK_REALTIME, &ts);
    tv->tv_sec = ts.tv_sec;
    tv->tv_usec = (int)ts.tv_nsec / 1000;
    return 0;
}

// TODO:
int utimes(const char *filename, const struct timeval times[2])
{
    unimplemented();
    return 0;
}

// TODO
struct tm *localtime_r(const time_t *__restrict__ __timer, struct tm *__restrict__ __tp)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return NULL;
}

// TODO
int nanosleep(const struct timespec *__requested_time, struct timespec *__remaining)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO
void tzset()
{
	unimplemented();
    return ;
}

// TODO
int setitimer(int __which, const struct itimerval *__restrict__ __new,
              struct itimerval *__restrict__ __old)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO
int clock_gettime(clockid_t __clock_id, struct timespec *__tp)
{
    return 0;
}

// TODO
char *ctime_r(const time_t *__restrict__ __timer, char *__restrict__ __buf)
{
    return NULL;
}

// TODO
clock_t clock(void)
{
    unimplemented();
    return 0;
}

double difftime(time_t t1, time_t t0)
{
    return t1 - t0;
}

// TODO
time_t mktime(struct tm *)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}