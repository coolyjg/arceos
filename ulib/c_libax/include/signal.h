#ifndef _SIGNAL_H
#define _SIGNAL_H

#include <stdint.h>

#include <stddef.h>
#include <bits/types.h>


int kill(pid_t __pid, int __sig);

typedef int sig_atomic_t;
#ifndef __siginfo_t_defined
#define __siginfo_t_defined 1
#ifndef ____sigval_t_defined
#define ____sigval_t_defined

/* Type for data associated with a signal.  */
#ifdef __USE_POSIX199309
union sigval {
    int sival_int;
    void *sival_ptr;
};

typedef union sigval __sigval_t;
#else
union __sigval {
    int __sival_int;
    void *__sival_ptr;
};

typedef union __sigval __sigval_t;
#endif

#endif

typedef int __pid_t;
typedef unsigned int __uid_t;
#ifndef _BITS_TYPES_H
typedef long __clock_t;
#endif
#define __SI_CLOCK_T __clock_t

#define __SI_MAX_SIZE 128
#define __SI_PAD_SIZE ((__SI_MAX_SIZE / sizeof(int)) - 4)

#ifndef __SI_ALIGNMENT
#define __SI_ALIGNMENT /* nothing */
#endif
#ifndef __SI_BAND_TYPE
#define __SI_BAND_TYPE long int
#endif
#ifndef __SI_ERRNO_THEN_CODE
#define __SI_ERRNO_THEN_CODE 1
#endif
#ifndef __SI_HAVE_SIGSYS
#define __SI_HAVE_SIGSYS 1
#endif
#ifndef __SI_SIGFAULT_ADDL
#define __SI_SIGFAULT_ADDL /* nothing */
#endif

#define SA_NOCLDSTOP 1
#define SA_NOCLDWAIT 2
#define SA_SIGINFO   4
#define SA_ONSTACK   0x08000000
#define SA_RESTART   0x10000000
#define SA_NODEFER   0x40000000
#define SA_RESETHAND 0x80000000
#define SA_RESTORER  0x04000000

enum {
    SI_ASYNCNL = -60, /* Sent by asynch name lookup completion.  */
    SI_DETHREAD = -7, /* Sent by execve killing subsidiary
                         threads.  */
    SI_TKILL,         /* Sent by tkill.  */
    SI_SIGIO,         /* Sent by queued SIGIO. */
#if __SI_ASYNCIO_AFTER_SIGIO
    SI_ASYNCIO, /* Sent by AIO completion.  */
    SI_MESGQ,   /* Sent by real time mesq state change.  */
    SI_TIMER,   /* Sent by timer expiration.  */
#else
    SI_MESGQ,
    SI_TIMER,
    SI_ASYNCIO,
#endif
    SI_QUEUE,        /* Sent by sigqueue.  */
    SI_USER,         /* Sent by kill, sigsend.  */
    SI_KERNEL = 0x80 /* Send by kernel.  */

#define SI_ASYNCNL  SI_ASYNCNL
#define SI_DETHREAD SI_DETHREAD
#define SI_TKILL    SI_TKILL
#define SI_SIGIO    SI_SIGIO
#define SI_ASYNCIO  SI_ASYNCIO
#define SI_MESGQ    SI_MESGQ
#define SI_TIMER    SI_TIMER
#define SI_ASYNCIO  SI_ASYNCIO
#define SI_QUEUE    SI_QUEUE
#define SI_USER     SI_USER
#define SI_KERNEL   SI_KERNEL
};

union sigval {
    int sival_int;
    void *sival_ptr;
};

typedef struct {
#ifdef __SI_SWAP_ERRNO_CODE
    int si_signo, si_code, si_errno;
#else
    int si_signo, si_errno, si_code;
#endif
    union {
        char __pad[128 - 2 * sizeof(int) - sizeof(long)];
        struct {
            union {
                struct {
                    int si_pid;
                    unsigned int si_uid;
                } __piduid;
                struct {
                    int si_timerid;
                    int si_overrun;
                } __timer;
            } __first;
            union {
                union sigval si_value;
                struct {
                    int si_status;
                    long si_utime, si_stime;
                } __sigchld;
            } __second;
        } __si_common;
        struct {
            void *si_addr;
            short si_addr_lsb;
            union {
                struct {
                    void *si_lower;
                    void *si_upper;
                } __addr_bnd;
                unsigned si_pkey;
            } __first;
        } __sigfault;
        struct {
            long si_band;
            int si_fd;
        } __sigpoll;
        struct {
            void *si_call_addr;
            int si_syscall;
            unsigned si_arch;
        } __sigsys;
    } __si_fields;
} siginfo_t;

#define si_pid       __si_fields.__si_common.__first.__piduid.si_pid
#define si_uid       __si_fields.__si_common.__first.__piduid.si_uid
#define si_status    __si_fields.__si_common.__second.__sigchld.si_status
#define si_utime     __si_fields.__si_common.__second.__sigchld.si_utime
#define si_stime     __si_fields.__si_common.__second.__sigchld.si_stime
#define si_value     __si_fields.__si_common.__second.si_value
#define si_addr      __si_fields.__sigfault.si_addr
#define si_addr_lsb  __si_fields.__sigfault.si_addr_lsb
#define si_lower     __si_fields.__sigfault.__first.__addr_bnd.si_lower
#define si_upper     __si_fields.__sigfault.__first.__addr_bnd.si_upper
#define si_pkey      __si_fields.__sigfault.__first.si_pkey
#define si_band      __si_fields.__sigpoll.si_band
#define si_fd        __si_fields.__sigpoll.si_fd
#define si_timerid   __si_fields.__si_common.__first.__timer.si_timerid
#define si_overrun   __si_fields.__si_common.__first.__timer.si_overrun
#define si_ptr       si_value.sival_ptr
#define si_int       si_value.sival_int
#define si_call_addr __si_fields.__sigsys.si_call_addr
#define si_syscall   __si_fields.__sigsys.si_syscall
#define si_arch      __si_fields.__sigsys.si_arch

#define SIGHUP    1
#define SIGINT    2
#define SIGQUIT   3
#define SIGILL    4
#define SIGTRAP   5
#define SIGABRT   6
#define SIGIOT    SIGABRT
#define SIGBUS    7
#define SIGFPE    8
#define SIGKILL   9
#define SIGUSR1   10
#define SIGSEGV   11
#define SIGUSR2   12
#define SIGPIPE   13
#define SIGALRM   14
#define SIGTERM   15
#define SIGSTKFLT 16
#define SIGCHLD   17
#define SIGCONT   18
#define SIGSTOP   19
#define SIGTSTP   20
#define SIGTTIN   21
#define SIGTTOU   22
#define SIGURG    23
#define SIGXCPU   24
#define SIGXFSZ   25
#define SIGVTALRM 26
#define SIGPROF   27
#define SIGWINCH  28
#define SIGIO     29
#define SIGPOLL   29
#define SIGPWR    30
#define SIGSYS    31
#define SIGUNUSED SIGSYS

#define _NSIG 65

/* Values for the HOW argument to `sigprocmask'.  */
#define SIG_BLOCK   0 /* Block signals.  */
#define SIG_UNBLOCK 1 /* Unblock signals.  */
#define SIG_SETMASK 2 /* Set the set of blocked signals.  */

typedef void (*__sighandler_t)(int);
#define SIG_IGN ((__sighandler_t)1)
#define SIG_DFL ((__sighandler_t)0) /* Default action.  */

#define _SIGSET_NWORDS (1024 / (8 * sizeof(unsigned long int)))

#define __USE_POSIX199309 1

#include <bits/types.h>

struct sigaction {
	union {
		void (*sa_handler)(int);
		void (*sa_sigaction)(int, siginfo_t *, void *);
	} __sa_handler;
	sigset_t sa_mask;
	int sa_flags;
	void (*sa_restorer)(void);
};

#define sa_handler   __sa_handler.sa_handler
#define sa_sigaction __sa_handler.sa_sigaction

#define SA_SIGINFO   4
#define SA_NODEFER   0x40000000
#define SA_RESETHAND 0x80000000
#endif

typedef void (*sighandler_t)(int);

void (*signal(int, void (*)(int)))(int);
int sigemptyset(sigset_t *__set);
int sigaction(int __sig, const struct sigaction *__restrict__ __act,
              struct sigaction *__restrict__ __oact);
int raise(int __sig);
int sigaddset(sigset_t *__set, int __signo);
int pthread_sigmask(int __how, const sigset_t *__restrict__ __newmask, sigset_t *__restrict__ __oldmask);

// int pthread_kill(pthread_t t, int sig);
#endif