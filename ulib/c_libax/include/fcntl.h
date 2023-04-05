#ifndef _FCNTL_H
#define _FCNTL_H

typedef long long int off_t;

#define __USE_XOPEN2K8

#include <bits/types.h>
#include <bits/types/struct_timespec.h>

#define O_ACCMODE 00000003
#ifndef O_RDONLY
#define O_RDONLY 00000000
#endif
#define O_WRONLY 00000001
#define O_RDWR   00000002
#ifndef O_CREAT
#define O_CREAT 00000100 /* not fcntl */
#endif
#ifndef O_EXCL
#define O_EXCL 00000200 /* not fcntl */
#endif
#ifndef O_NOCTTY
#define O_NOCTTY 00000400 /* not fcntl */
#endif
#ifndef O_TRUNC
#define O_TRUNC 00001000 /* not fcntl */
#endif
#ifndef O_APPEND
#define O_APPEND 00002000
#endif
#ifndef O_NONBLOCK
#define O_NONBLOCK 00004000
#endif
#ifndef O_DSYNC
#define O_DSYNC 00010000 /* used to be O_SYNC, see below */
#endif
#ifndef FASYNC
#define FASYNC 00020000 /* fcntl, for BSD compatibility */
#endif
#ifndef O_DIRECT
#define O_DIRECT 00040000 /* direct disk access hint */
#endif
#ifndef O_LARGEFILE
#define O_LARGEFILE 00100000
#endif
#ifndef O_DIRECTORY
#define O_DIRECTORY 00200000 /* must be a directory */
#endif
#ifndef O_NOFOLLOW
#define O_NOFOLLOW 00400000 /* don't follow links */
#endif
#ifndef O_NOATIME
#define O_NOATIME 01000000
#endif
#ifndef O_CLOEXEC
#define O_CLOEXEC 02000000 /* set close_on_exec */
#endif

#ifndef O_SYNC
#define __O_SYNC 04000000
#define O_SYNC   (__O_SYNC | O_DSYNC)
#endif

#ifndef O_PATH
#define O_PATH 010000000
#endif

#ifndef __O_TMPFILE
#define __O_TMPFILE 020000000
#endif

/* a horrid kludge trying to make sure that this will fail on old kernels */
#define O_TMPFILE      (__O_TMPFILE | O_DIRECTORY)
#define O_TMPFILE_MASK (__O_TMPFILE | O_DIRECTORY | O_CREAT)

#ifndef O_NDELAY
#define O_NDELAY O_NONBLOCK
#endif

#define F_DUPFD 0 /* dup */
#define F_GETFD 1 /* get close_on_exec */
#define F_SETFD 2 /* set/clear close_on_exec */
#define F_GETFL 3 /* get file->f_flags */
#define F_SETFL 4 /* set file->f_flags */
#ifndef F_GETLK
#define F_GETLK  5
#define F_SETLK  6
#define F_SETLKW 7
#endif
#ifndef F_SETOWN
#define F_SETOWN 8 /* for sockets. */
#define F_GETOWN 9 /* for sockets. */
#endif
#ifndef F_SETSIG
#define F_SETSIG 10 /* for sockets. */
#define F_GETSIG 11 /* for sockets. */
#endif

#if __BITS_PER_LONG == 32 || defined(__KERNEL__)
#ifndef F_GETLK64
#define F_GETLK64  12 /*  using 'struct flock64' */
#define F_SETLK64  13
#define F_SETLKW64 14
#endif
#endif /* __BITS_PER_LONG == 32 || defined(__KERNEL__) */

#ifndef F_SETOWN_EX
#define F_SETOWN_EX 15
#define F_GETOWN_EX 16
#endif

#ifndef F_GETOWNER_UIDS
#define F_GETOWNER_UIDS 17
#endif

/*
 * Open File Description Locks
 *
 * Usually record locks held by a process are released on *any* close and are
 * not inherited across a fork().
 *
 * These cmd values will set locks that conflict with process-associated
 * record  locks, but are "owned" by the open file description, not the
 * process. This means that they are inherited across fork() like BSD (flock)
 * locks, and they are only released automatically when the last reference to
 * the the open file against which they were acquired is put.
 */
#define F_OFD_GETLK  36
#define F_OFD_SETLK  37
#define F_OFD_SETLKW 38

#define F_OWNER_TID  0
#define F_OWNER_PID  1
#define F_OWNER_PGRP 2

/* for F_[GET|SET]FL */
#define FD_CLOEXEC 1 /* actually anything with low bit set goes */

/* for posix fcntl() and lockf() */
#ifndef F_RDLCK
#define F_RDLCK 0
#define F_WRLCK 1
#define F_UNLCK 2
#endif

/* for old implementation of bsd flock () */
#ifndef F_EXLCK
#define F_EXLCK 4 /* or 3 */
#define F_SHLCK 8 /* or 4 */
#endif

/* operations for bsd flock(), also used by the kernel implementation */
#define LOCK_SH 1 /* shared lock */
#define LOCK_EX 2 /* exclusive lock */
#define LOCK_NB                                            \
    4             /* or'd with one of the above to prevent \
                     blocking */
#define LOCK_UN 8 /* remove lock */

/*
 * LOCK_MAND support has been removed from the kernel. We leave the symbols
 * here to not break legacy builds, but these should not be used in new code.
 */
#define LOCK_MAND  32  /* This is a mandatory flock ... */
#define LOCK_READ  64  /* which allows concurrent read operations */
#define LOCK_WRITE 128 /* which allows concurrent write operations */
#define LOCK_RW    192 /* which allows concurrent read & write ops */

#define F_LINUX_SPECIFIC_BASE 1024

typedef unsigned int __kernel_off_t;

typedef unsigned int __kernel_pid_t;

#ifndef HAVE_ARCH_STRUCT_FLOCK
struct flock {
    short l_type;
    short l_whence;
    __kernel_off_t l_start;
    __kernel_off_t l_len;
    __kernel_pid_t l_pid;
#ifdef __ARCH_FLOCK_EXTRA_SYSID
    __ARCH_FLOCK_EXTRA_SYSID
#endif
#ifdef __ARCH_FLOCK_PAD
    __ARCH_FLOCK_PAD
#endif
};

#define R_OK 4 /* Test for read permission.  */
#define W_OK 2 /* Test for write permission.  */
#define X_OK 1 /* Test for execute permission.  */
#define F_OK 0 /* Test for existence.  */

#endif /* HAVE_ARCH_STRUCT_FLOCK */

#define FILENAME_MAX 4096

int fcntl(int fd, int cmd, ... /* arg */);
int open(const char *filename, int flags, ...);
int posix_fadvise(int __fd, unsigned long __offset, unsigned long __len, int __advise);

#ifndef __POSIX_FADV_DONTNEED
#define __POSIX_FADV_DONTNEED 4
#define __POSIX_FADV_NOREUSE  5
#endif

#define POSIX_FADV_DONTNEED __POSIX_FADV_DONTNEED /* Don't need these pages.  */

enum {
    _SC_ARG_MAX,
#define _SC_ARG_MAX _SC_ARG_MAX
    _SC_CHILD_MAX,
#define _SC_CHILD_MAX _SC_CHILD_MAX
    _SC_CLK_TCK,
#define _SC_CLK_TCK _SC_CLK_TCK
    _SC_NGROUPS_MAX,
#define _SC_NGROUPS_MAX _SC_NGROUPS_MAX
    _SC_OPEN_MAX,
#define _SC_OPEN_MAX _SC_OPEN_MAX
    _SC_STREAM_MAX,
#define _SC_STREAM_MAX _SC_STREAM_MAX
    _SC_TZNAME_MAX,
#define _SC_TZNAME_MAX _SC_TZNAME_MAX
    _SC_JOB_CONTROL,
#define _SC_JOB_CONTROL _SC_JOB_CONTROL
    _SC_SAVED_IDS,
#define _SC_SAVED_IDS _SC_SAVED_IDS
    _SC_REALTIME_SIGNALS,
#define _SC_REALTIME_SIGNALS _SC_REALTIME_SIGNALS
    _SC_PRIORITY_SCHEDULING,
#define _SC_PRIORITY_SCHEDULING _SC_PRIORITY_SCHEDULING
    _SC_TIMERS,
#define _SC_TIMERS _SC_TIMERS
    _SC_ASYNCHRONOUS_IO,
#define _SC_ASYNCHRONOUS_IO _SC_ASYNCHRONOUS_IO
    _SC_PRIORITIZED_IO,
#define _SC_PRIORITIZED_IO _SC_PRIORITIZED_IO
    _SC_SYNCHRONIZED_IO,
#define _SC_SYNCHRONIZED_IO _SC_SYNCHRONIZED_IO
    _SC_FSYNC,
#define _SC_FSYNC _SC_FSYNC
    _SC_MAPPED_FILES,
#define _SC_MAPPED_FILES _SC_MAPPED_FILES
    _SC_MEMLOCK,
#define _SC_MEMLOCK _SC_MEMLOCK
    _SC_MEMLOCK_RANGE,
#define _SC_MEMLOCK_RANGE _SC_MEMLOCK_RANGE
    _SC_MEMORY_PROTECTION,
#define _SC_MEMORY_PROTECTION _SC_MEMORY_PROTECTION
    _SC_MESSAGE_PASSING,
#define _SC_MESSAGE_PASSING _SC_MESSAGE_PASSING
    _SC_SEMAPHORES,
#define _SC_SEMAPHORES _SC_SEMAPHORES
    _SC_SHARED_MEMORY_OBJECTS,
#define _SC_SHARED_MEMORY_OBJECTS _SC_SHARED_MEMORY_OBJECTS
    _SC_AIO_LISTIO_MAX,
#define _SC_AIO_LISTIO_MAX _SC_AIO_LISTIO_MAX
    _SC_AIO_MAX,
#define _SC_AIO_MAX _SC_AIO_MAX
    _SC_AIO_PRIO_DELTA_MAX,
#define _SC_AIO_PRIO_DELTA_MAX _SC_AIO_PRIO_DELTA_MAX
    _SC_DELAYTIMER_MAX,
#define _SC_DELAYTIMER_MAX _SC_DELAYTIMER_MAX
    _SC_MQ_OPEN_MAX,
#define _SC_MQ_OPEN_MAX _SC_MQ_OPEN_MAX
    _SC_MQ_PRIO_MAX,
#define _SC_MQ_PRIO_MAX _SC_MQ_PRIO_MAX
    _SC_VERSION,
#define _SC_VERSION _SC_VERSION
    _SC_PAGESIZE,
#define _SC_PAGESIZE  _SC_PAGESIZE
#define _SC_PAGE_SIZE _SC_PAGESIZE
    _SC_RTSIG_MAX,
#define _SC_RTSIG_MAX _SC_RTSIG_MAX
    _SC_SEM_NSEMS_MAX,
#define _SC_SEM_NSEMS_MAX _SC_SEM_NSEMS_MAX
    _SC_SEM_VALUE_MAX,
#define _SC_SEM_VALUE_MAX _SC_SEM_VALUE_MAX
    _SC_SIGQUEUE_MAX,
#define _SC_SIGQUEUE_MAX _SC_SIGQUEUE_MAX
    _SC_TIMER_MAX,
#define _SC_TIMER_MAX _SC_TIMER_MAX

    /* Values for the argument to `sysconf'
       corresponding to _POSIX2_* symbols.  */
    _SC_BC_BASE_MAX,
#define _SC_BC_BASE_MAX _SC_BC_BASE_MAX
    _SC_BC_DIM_MAX,
#define _SC_BC_DIM_MAX _SC_BC_DIM_MAX
    _SC_BC_SCALE_MAX,
#define _SC_BC_SCALE_MAX _SC_BC_SCALE_MAX
    _SC_BC_STRING_MAX,
#define _SC_BC_STRING_MAX _SC_BC_STRING_MAX
    _SC_COLL_WEIGHTS_MAX,
#define _SC_COLL_WEIGHTS_MAX _SC_COLL_WEIGHTS_MAX
    _SC_EQUIV_CLASS_MAX,
#define _SC_EQUIV_CLASS_MAX _SC_EQUIV_CLASS_MAX
    _SC_EXPR_NEST_MAX,
#define _SC_EXPR_NEST_MAX _SC_EXPR_NEST_MAX
    _SC_LINE_MAX,
#define _SC_LINE_MAX _SC_LINE_MAX
    _SC_RE_DUP_MAX,
#define _SC_RE_DUP_MAX _SC_RE_DUP_MAX
    _SC_CHARCLASS_NAME_MAX,
#define _SC_CHARCLASS_NAME_MAX _SC_CHARCLASS_NAME_MAX

    _SC_2_VERSION,
#define _SC_2_VERSION _SC_2_VERSION
    _SC_2_C_BIND,
#define _SC_2_C_BIND _SC_2_C_BIND
    _SC_2_C_DEV,
#define _SC_2_C_DEV _SC_2_C_DEV
    _SC_2_FORT_DEV,
#define _SC_2_FORT_DEV _SC_2_FORT_DEV
    _SC_2_FORT_RUN,
#define _SC_2_FORT_RUN _SC_2_FORT_RUN
    _SC_2_SW_DEV,
#define _SC_2_SW_DEV _SC_2_SW_DEV
    _SC_2_LOCALEDEF,
#define _SC_2_LOCALEDEF _SC_2_LOCALEDEF

    _SC_PII,
#define _SC_PII _SC_PII
    _SC_PII_XTI,
#define _SC_PII_XTI _SC_PII_XTI
    _SC_PII_SOCKET,
#define _SC_PII_SOCKET _SC_PII_SOCKET
    _SC_PII_INTERNET,
#define _SC_PII_INTERNET _SC_PII_INTERNET
    _SC_PII_OSI,
#define _SC_PII_OSI _SC_PII_OSI
    _SC_POLL,
#define _SC_POLL _SC_POLL
    _SC_SELECT,
#define _SC_SELECT _SC_SELECT
    _SC_UIO_MAXIOV,
#define _SC_UIO_MAXIOV _SC_UIO_MAXIOV
    _SC_IOV_MAX = _SC_UIO_MAXIOV,
#define _SC_IOV_MAX _SC_IOV_MAX
    _SC_PII_INTERNET_STREAM,
#define _SC_PII_INTERNET_STREAM _SC_PII_INTERNET_STREAM
    _SC_PII_INTERNET_DGRAM,
#define _SC_PII_INTERNET_DGRAM _SC_PII_INTERNET_DGRAM
    _SC_PII_OSI_COTS,
#define _SC_PII_OSI_COTS _SC_PII_OSI_COTS
    _SC_PII_OSI_CLTS,
#define _SC_PII_OSI_CLTS _SC_PII_OSI_CLTS
    _SC_PII_OSI_M,
#define _SC_PII_OSI_M _SC_PII_OSI_M
    _SC_T_IOV_MAX,
#define _SC_T_IOV_MAX _SC_T_IOV_MAX

    /* Values according to POSIX 1003.1c (POSIX threads).  */
    _SC_THREADS,
#define _SC_THREADS _SC_THREADS
    _SC_THREAD_SAFE_FUNCTIONS,
#define _SC_THREAD_SAFE_FUNCTIONS _SC_THREAD_SAFE_FUNCTIONS
    _SC_GETGR_R_SIZE_MAX,
#define _SC_GETGR_R_SIZE_MAX _SC_GETGR_R_SIZE_MAX
    _SC_GETPW_R_SIZE_MAX,
#define _SC_GETPW_R_SIZE_MAX _SC_GETPW_R_SIZE_MAX
    _SC_LOGIN_NAME_MAX,
#define _SC_LOGIN_NAME_MAX _SC_LOGIN_NAME_MAX
    _SC_TTY_NAME_MAX,
#define _SC_TTY_NAME_MAX _SC_TTY_NAME_MAX
    _SC_THREAD_DESTRUCTOR_ITERATIONS,
#define _SC_THREAD_DESTRUCTOR_ITERATIONS _SC_THREAD_DESTRUCTOR_ITERATIONS
    _SC_THREAD_KEYS_MAX,
#define _SC_THREAD_KEYS_MAX _SC_THREAD_KEYS_MAX
    _SC_THREAD_STACK_MIN,
#define _SC_THREAD_STACK_MIN _SC_THREAD_STACK_MIN
    _SC_THREAD_THREADS_MAX,
#define _SC_THREAD_THREADS_MAX _SC_THREAD_THREADS_MAX
    _SC_THREAD_ATTR_STACKADDR,
#define _SC_THREAD_ATTR_STACKADDR _SC_THREAD_ATTR_STACKADDR
    _SC_THREAD_ATTR_STACKSIZE,
#define _SC_THREAD_ATTR_STACKSIZE _SC_THREAD_ATTR_STACKSIZE
    _SC_THREAD_PRIORITY_SCHEDULING,
#define _SC_THREAD_PRIORITY_SCHEDULING _SC_THREAD_PRIORITY_SCHEDULING
    _SC_THREAD_PRIO_INHERIT,
#define _SC_THREAD_PRIO_INHERIT _SC_THREAD_PRIO_INHERIT
    _SC_THREAD_PRIO_PROTECT,
#define _SC_THREAD_PRIO_PROTECT _SC_THREAD_PRIO_PROTECT
    _SC_THREAD_PROCESS_SHARED,
#define _SC_THREAD_PROCESS_SHARED _SC_THREAD_PROCESS_SHARED

    _SC_NPROCESSORS_CONF,
#define _SC_NPROCESSORS_CONF _SC_NPROCESSORS_CONF
    _SC_NPROCESSORS_ONLN,
#define _SC_NPROCESSORS_ONLN _SC_NPROCESSORS_ONLN
    _SC_PHYS_PAGES,
#define _SC_PHYS_PAGES _SC_PHYS_PAGES
    _SC_AVPHYS_PAGES,
#define _SC_AVPHYS_PAGES _SC_AVPHYS_PAGES
    _SC_ATEXIT_MAX,
#define _SC_ATEXIT_MAX _SC_ATEXIT_MAX
    _SC_PASS_MAX,
#define _SC_PASS_MAX _SC_PASS_MAX

    _SC_XOPEN_VERSION,
#define _SC_XOPEN_VERSION _SC_XOPEN_VERSION
    _SC_XOPEN_XCU_VERSION,
#define _SC_XOPEN_XCU_VERSION _SC_XOPEN_XCU_VERSION
    _SC_XOPEN_UNIX,
#define _SC_XOPEN_UNIX _SC_XOPEN_UNIX
    _SC_XOPEN_CRYPT,
#define _SC_XOPEN_CRYPT _SC_XOPEN_CRYPT
    _SC_XOPEN_ENH_I18N,
#define _SC_XOPEN_ENH_I18N _SC_XOPEN_ENH_I18N
    _SC_XOPEN_SHM,
#define _SC_XOPEN_SHM _SC_XOPEN_SHM

    _SC_2_CHAR_TERM,
#define _SC_2_CHAR_TERM _SC_2_CHAR_TERM
    _SC_2_C_VERSION,
#define _SC_2_C_VERSION _SC_2_C_VERSION
    _SC_2_UPE,
#define _SC_2_UPE _SC_2_UPE

    _SC_XOPEN_XPG2,
#define _SC_XOPEN_XPG2 _SC_XOPEN_XPG2
    _SC_XOPEN_XPG3,
#define _SC_XOPEN_XPG3 _SC_XOPEN_XPG3
    _SC_XOPEN_XPG4,
#define _SC_XOPEN_XPG4 _SC_XOPEN_XPG4

    _SC_CHAR_BIT,
#define _SC_CHAR_BIT _SC_CHAR_BIT
    _SC_CHAR_MAX,
#define _SC_CHAR_MAX _SC_CHAR_MAX
    _SC_CHAR_MIN,
#define _SC_CHAR_MIN _SC_CHAR_MIN
    _SC_INT_MAX,
#define _SC_INT_MAX _SC_INT_MAX
    _SC_INT_MIN,
#define _SC_INT_MIN _SC_INT_MIN
    _SC_LONG_BIT,
#define _SC_LONG_BIT _SC_LONG_BIT
    _SC_WORD_BIT,
#define _SC_WORD_BIT _SC_WORD_BIT
    _SC_MB_LEN_MAX,
#define _SC_MB_LEN_MAX _SC_MB_LEN_MAX
    _SC_NZERO,
#define _SC_NZERO _SC_NZERO
    _SC_SSIZE_MAX,
#define _SC_SSIZE_MAX _SC_SSIZE_MAX
    _SC_SCHAR_MAX,
#define _SC_SCHAR_MAX _SC_SCHAR_MAX
    _SC_SCHAR_MIN,
#define _SC_SCHAR_MIN _SC_SCHAR_MIN
    _SC_SHRT_MAX,
#define _SC_SHRT_MAX _SC_SHRT_MAX
    _SC_SHRT_MIN,
#define _SC_SHRT_MIN _SC_SHRT_MIN
    _SC_UCHAR_MAX,
#define _SC_UCHAR_MAX _SC_UCHAR_MAX
    _SC_UINT_MAX,
#define _SC_UINT_MAX _SC_UINT_MAX
    _SC_ULONG_MAX,
#define _SC_ULONG_MAX _SC_ULONG_MAX
    _SC_USHRT_MAX,
#define _SC_USHRT_MAX _SC_USHRT_MAX

    _SC_NL_ARGMAX,
#define _SC_NL_ARGMAX _SC_NL_ARGMAX
    _SC_NL_LANGMAX,
#define _SC_NL_LANGMAX _SC_NL_LANGMAX
    _SC_NL_MSGMAX,
#define _SC_NL_MSGMAX _SC_NL_MSGMAX
    _SC_NL_NMAX,
#define _SC_NL_NMAX _SC_NL_NMAX
    _SC_NL_SETMAX,
#define _SC_NL_SETMAX _SC_NL_SETMAX
    _SC_NL_TEXTMAX,
#define _SC_NL_TEXTMAX _SC_NL_TEXTMAX

    _SC_XBS5_ILP32_OFF32,
#define _SC_XBS5_ILP32_OFF32 _SC_XBS5_ILP32_OFF32
    _SC_XBS5_ILP32_OFFBIG,
#define _SC_XBS5_ILP32_OFFBIG _SC_XBS5_ILP32_OFFBIG
    _SC_XBS5_LP64_OFF64,
#define _SC_XBS5_LP64_OFF64 _SC_XBS5_LP64_OFF64
    _SC_XBS5_LPBIG_OFFBIG,
#define _SC_XBS5_LPBIG_OFFBIG _SC_XBS5_LPBIG_OFFBIG

    _SC_XOPEN_LEGACY,
#define _SC_XOPEN_LEGACY _SC_XOPEN_LEGACY
    _SC_XOPEN_REALTIME,
#define _SC_XOPEN_REALTIME _SC_XOPEN_REALTIME
    _SC_XOPEN_REALTIME_THREADS,
#define _SC_XOPEN_REALTIME_THREADS _SC_XOPEN_REALTIME_THREADS

    _SC_ADVISORY_INFO,
#define _SC_ADVISORY_INFO _SC_ADVISORY_INFO
    _SC_BARRIERS,
#define _SC_BARRIERS _SC_BARRIERS
    _SC_BASE,
#define _SC_BASE _SC_BASE
    _SC_C_LANG_SUPPORT,
#define _SC_C_LANG_SUPPORT _SC_C_LANG_SUPPORT
    _SC_C_LANG_SUPPORT_R,
#define _SC_C_LANG_SUPPORT_R _SC_C_LANG_SUPPORT_R
    _SC_CLOCK_SELECTION,
#define _SC_CLOCK_SELECTION _SC_CLOCK_SELECTION
    _SC_CPUTIME,
#define _SC_CPUTIME _SC_CPUTIME
    _SC_THREAD_CPUTIME,
#define _SC_THREAD_CPUTIME _SC_THREAD_CPUTIME
    _SC_DEVICE_IO,
#define _SC_DEVICE_IO _SC_DEVICE_IO
    _SC_DEVICE_SPECIFIC,
#define _SC_DEVICE_SPECIFIC _SC_DEVICE_SPECIFIC
    _SC_DEVICE_SPECIFIC_R,
#define _SC_DEVICE_SPECIFIC_R _SC_DEVICE_SPECIFIC_R
    _SC_FD_MGMT,
#define _SC_FD_MGMT _SC_FD_MGMT
    _SC_FIFO,
#define _SC_FIFO _SC_FIFO
    _SC_PIPE,
#define _SC_PIPE _SC_PIPE
    _SC_FILE_ATTRIBUTES,
#define _SC_FILE_ATTRIBUTES _SC_FILE_ATTRIBUTES
    _SC_FILE_LOCKING,
#define _SC_FILE_LOCKING _SC_FILE_LOCKING
    _SC_FILE_SYSTEM,
#define _SC_FILE_SYSTEM _SC_FILE_SYSTEM
    _SC_MONOTONIC_CLOCK,
#define _SC_MONOTONIC_CLOCK _SC_MONOTONIC_CLOCK
    _SC_MULTI_PROCESS,
#define _SC_MULTI_PROCESS _SC_MULTI_PROCESS
    _SC_SINGLE_PROCESS,
#define _SC_SINGLE_PROCESS _SC_SINGLE_PROCESS
    _SC_NETWORKING,
#define _SC_NETWORKING _SC_NETWORKING
    _SC_READER_WRITER_LOCKS,
#define _SC_READER_WRITER_LOCKS _SC_READER_WRITER_LOCKS
    _SC_SPIN_LOCKS,
#define _SC_SPIN_LOCKS _SC_SPIN_LOCKS
    _SC_REGEXP,
#define _SC_REGEXP _SC_REGEXP
    _SC_REGEX_VERSION,
#define _SC_REGEX_VERSION _SC_REGEX_VERSION
    _SC_SHELL,
#define _SC_SHELL _SC_SHELL
    _SC_SIGNALS,
#define _SC_SIGNALS _SC_SIGNALS
    _SC_SPAWN,
#define _SC_SPAWN _SC_SPAWN
    _SC_SPORADIC_SERVER,
#define _SC_SPORADIC_SERVER _SC_SPORADIC_SERVER
    _SC_THREAD_SPORADIC_SERVER,
#define _SC_THREAD_SPORADIC_SERVER _SC_THREAD_SPORADIC_SERVER
    _SC_SYSTEM_DATABASE,
#define _SC_SYSTEM_DATABASE _SC_SYSTEM_DATABASE
    _SC_SYSTEM_DATABASE_R,
#define _SC_SYSTEM_DATABASE_R _SC_SYSTEM_DATABASE_R
    _SC_TIMEOUTS,
#define _SC_TIMEOUTS _SC_TIMEOUTS
    _SC_TYPED_MEMORY_OBJECTS,
#define _SC_TYPED_MEMORY_OBJECTS _SC_TYPED_MEMORY_OBJECTS
    _SC_USER_GROUPS,
#define _SC_USER_GROUPS _SC_USER_GROUPS
    _SC_USER_GROUPS_R,
#define _SC_USER_GROUPS_R _SC_USER_GROUPS_R
    _SC_2_PBS,
#define _SC_2_PBS _SC_2_PBS
    _SC_2_PBS_ACCOUNTING,
#define _SC_2_PBS_ACCOUNTING _SC_2_PBS_ACCOUNTING
    _SC_2_PBS_LOCATE,
#define _SC_2_PBS_LOCATE _SC_2_PBS_LOCATE
    _SC_2_PBS_MESSAGE,
#define _SC_2_PBS_MESSAGE _SC_2_PBS_MESSAGE
    _SC_2_PBS_TRACK,
#define _SC_2_PBS_TRACK _SC_2_PBS_TRACK
    _SC_SYMLOOP_MAX,
#define _SC_SYMLOOP_MAX _SC_SYMLOOP_MAX
    _SC_STREAMS,
#define _SC_STREAMS _SC_STREAMS
    _SC_2_PBS_CHECKPOINT,
#define _SC_2_PBS_CHECKPOINT _SC_2_PBS_CHECKPOINT

    _SC_V6_ILP32_OFF32,
#define _SC_V6_ILP32_OFF32 _SC_V6_ILP32_OFF32
    _SC_V6_ILP32_OFFBIG,
#define _SC_V6_ILP32_OFFBIG _SC_V6_ILP32_OFFBIG
    _SC_V6_LP64_OFF64,
#define _SC_V6_LP64_OFF64 _SC_V6_LP64_OFF64
    _SC_V6_LPBIG_OFFBIG,
#define _SC_V6_LPBIG_OFFBIG _SC_V6_LPBIG_OFFBIG

    _SC_HOST_NAME_MAX,
#define _SC_HOST_NAME_MAX _SC_HOST_NAME_MAX
    _SC_TRACE,
#define _SC_TRACE _SC_TRACE
    _SC_TRACE_EVENT_FILTER,
#define _SC_TRACE_EVENT_FILTER _SC_TRACE_EVENT_FILTER
    _SC_TRACE_INHERIT,
#define _SC_TRACE_INHERIT _SC_TRACE_INHERIT
    _SC_TRACE_LOG,
#define _SC_TRACE_LOG _SC_TRACE_LOG

    _SC_LEVEL1_ICACHE_SIZE,
#define _SC_LEVEL1_ICACHE_SIZE _SC_LEVEL1_ICACHE_SIZE
    _SC_LEVEL1_ICACHE_ASSOC,
#define _SC_LEVEL1_ICACHE_ASSOC _SC_LEVEL1_ICACHE_ASSOC
    _SC_LEVEL1_ICACHE_LINESIZE,
#define _SC_LEVEL1_ICACHE_LINESIZE _SC_LEVEL1_ICACHE_LINESIZE
    _SC_LEVEL1_DCACHE_SIZE,
#define _SC_LEVEL1_DCACHE_SIZE _SC_LEVEL1_DCACHE_SIZE
    _SC_LEVEL1_DCACHE_ASSOC,
#define _SC_LEVEL1_DCACHE_ASSOC _SC_LEVEL1_DCACHE_ASSOC
    _SC_LEVEL1_DCACHE_LINESIZE,
#define _SC_LEVEL1_DCACHE_LINESIZE _SC_LEVEL1_DCACHE_LINESIZE
    _SC_LEVEL2_CACHE_SIZE,
#define _SC_LEVEL2_CACHE_SIZE _SC_LEVEL2_CACHE_SIZE
    _SC_LEVEL2_CACHE_ASSOC,
#define _SC_LEVEL2_CACHE_ASSOC _SC_LEVEL2_CACHE_ASSOC
    _SC_LEVEL2_CACHE_LINESIZE,
#define _SC_LEVEL2_CACHE_LINESIZE _SC_LEVEL2_CACHE_LINESIZE
    _SC_LEVEL3_CACHE_SIZE,
#define _SC_LEVEL3_CACHE_SIZE _SC_LEVEL3_CACHE_SIZE
    _SC_LEVEL3_CACHE_ASSOC,
#define _SC_LEVEL3_CACHE_ASSOC _SC_LEVEL3_CACHE_ASSOC
    _SC_LEVEL3_CACHE_LINESIZE,
#define _SC_LEVEL3_CACHE_LINESIZE _SC_LEVEL3_CACHE_LINESIZE
    _SC_LEVEL4_CACHE_SIZE,
#define _SC_LEVEL4_CACHE_SIZE _SC_LEVEL4_CACHE_SIZE
    _SC_LEVEL4_CACHE_ASSOC,
#define _SC_LEVEL4_CACHE_ASSOC _SC_LEVEL4_CACHE_ASSOC
    _SC_LEVEL4_CACHE_LINESIZE,
#define _SC_LEVEL4_CACHE_LINESIZE _SC_LEVEL4_CACHE_LINESIZE
    /* Leave room here, maybe we need a few more cache levels some day.  */

    _SC_IPV6 = _SC_LEVEL1_ICACHE_SIZE + 50,
#define _SC_IPV6 _SC_IPV6
    _SC_RAW_SOCKETS,
#define _SC_RAW_SOCKETS _SC_RAW_SOCKETS

    _SC_V7_ILP32_OFF32,
#define _SC_V7_ILP32_OFF32 _SC_V7_ILP32_OFF32
    _SC_V7_ILP32_OFFBIG,
#define _SC_V7_ILP32_OFFBIG _SC_V7_ILP32_OFFBIG
    _SC_V7_LP64_OFF64,
#define _SC_V7_LP64_OFF64 _SC_V7_LP64_OFF64
    _SC_V7_LPBIG_OFFBIG,
#define _SC_V7_LPBIG_OFFBIG _SC_V7_LPBIG_OFFBIG

    _SC_SS_REPL_MAX,
#define _SC_SS_REPL_MAX _SC_SS_REPL_MAX

    _SC_TRACE_EVENT_NAME_MAX,
#define _SC_TRACE_EVENT_NAME_MAX _SC_TRACE_EVENT_NAME_MAX
    _SC_TRACE_NAME_MAX,
#define _SC_TRACE_NAME_MAX _SC_TRACE_NAME_MAX
    _SC_TRACE_SYS_MAX,
#define _SC_TRACE_SYS_MAX _SC_TRACE_SYS_MAX
    _SC_TRACE_USER_EVENT_MAX,
#define _SC_TRACE_USER_EVENT_MAX _SC_TRACE_USER_EVENT_MAX

    _SC_XOPEN_STREAMS,
#define _SC_XOPEN_STREAMS _SC_XOPEN_STREAMS

    _SC_THREAD_ROBUST_PRIO_INHERIT,
#define _SC_THREAD_ROBUST_PRIO_INHERIT _SC_THREAD_ROBUST_PRIO_INHERIT
    _SC_THREAD_ROBUST_PRIO_PROTECT,
#define _SC_THREAD_ROBUST_PRIO_PROTECT _SC_THREAD_ROBUST_PRIO_PROTECT

    _SC_MINSIGSTKSZ,
#define _SC_MINSIGSTKSZ _SC_MINSIGSTKSZ

    _SC_SIGSTKSZ
#define _SC_SIGSTKSZ _SC_SIGSTKSZ
};

#define AT_FDCWD (-100)
#define AT_EMPTY_PATH 0x1000

#endif
