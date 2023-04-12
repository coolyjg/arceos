#ifndef __SYS_TIME_H__
#define __SYS_TIME_H__

#include <features.h>

#include <bits/types.h>
#include <bits/types/struct_rusage.h>
#include <bits/types/struct_timeval.h>
#include <bits/types/time_t.h>

#ifndef __suseconds_t_defined
typedef __suseconds_t suseconds_t;
#define __suseconds_t_defined
#endif

#define ITIMER_REAL    0
#define ITIMER_VIRTUAL 1
#define ITIMER_PROF    2

#include <sys/select.h>

struct itimerval {
    /* Value to put into `it_value' when the timer expires.  */
    struct timeval it_interval;
    /* Time to the next timer expiration.  */
    struct timeval it_value;
};

// struct timeval {
//     long tv_sec;  /* seconds */
//     long tv_usec; /* microseconds */
// };

struct timezone {
    int tz_minuteswest; /* (minutes west of Greenwich) */
    int tz_dsttime;     /* (type of DST correction) */
};
extern long timezone;
// typedef long timezone;
int gettimeofday(struct timeval *tv, struct timezone *tz);
int utimes(const char *filename, const struct timeval times[2]);

#endif
