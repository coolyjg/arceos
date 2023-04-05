#ifndef __TIME_H__
#define __TIME_H__

#include <stddef.h>

typedef long time_t;
#define CLOCK_REALTIME           0

#define CLOCKS_PER_SEC 1000000L

#if defined(_XOPEN_SOURCE) || defined(_BSD_SOURCE) || defined(_GNU_SOURCE)
extern int daylight;
extern long timezone;
extern int getdate_err;
#endif

struct tm {
    int tm_sec;          /* seconds of minute */
    int tm_min;          /* minutes of hour */
    int tm_hour;         /* hours of day */
    int tm_mday;         /* day of month */
    int tm_mon;          /* month of year, 0 is first month(January) */
    int tm_year;         /* years, whose value equals the actual year minus 1900 */
    int tm_wday;         /* day of week, 0 is sunday, 1 is monday, and so on*/
    int tm_yday;         /* day of year */
    int tm_isdst;        /*  */
    long int tm_gmtoff;  /* */
    const char *tm_zone; /* timezone */
};

size_t strftime(char *__restrict__ _Buf, size_t _SizeInBytes, const char *__restrict__ _Format,
                const struct tm *__restrict__ _Tm);

struct tm *gmtime(const time_t *timer);

struct tm *localtime(const time_t *timep);
struct tm *localtime_r(const time_t *__restrict__ __timer, struct tm *__restrict__ __tp);

time_t time(time_t *t);

#include <bits/types/struct_timespec.h>
int nanosleep(const struct timespec *__requested_time, struct timespec *__remaining);
void tzset(void);

#include <sys/time.h>
int setitimer(int __which, const struct itimerval *__restrict__ __new,
              struct itimerval *__restrict__ __old);

#define CLOCK_MONOTONIC 1

int clock_gettime(clockid_t __clock_id, struct timespec *__tp);

char *ctime_r(const time_t *__restrict__ __timer, char *__restrict__ __buf);

#endif
