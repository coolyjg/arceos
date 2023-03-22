#ifndef	_SIGNAL_H
#define _SIGNAL_H

#include <stdint.h>


typedef int sig_atomic_t;
#ifndef __siginfo_t_defined
#define __siginfo_t_defined 1
#ifndef ____sigval_t_defined
#define ____sigval_t_defined

/* Type for data associated with a signal.  */
#ifdef __USE_POSIX199309
union sigval
{
  int sival_int;
  void *sival_ptr;
};

typedef union sigval __sigval_t;
#else
union __sigval
{
  int __sival_int;
  void *__sival_ptr;
};

typedef union __sigval __sigval_t;
#endif

#endif

typedef int __pid_t;
typedef unsigned int __uid_t;
typedef long __clock_t;
#define __SI_CLOCK_T __clock_t

#define __SI_MAX_SIZE	128
#define __SI_PAD_SIZE	((__SI_MAX_SIZE / sizeof (int)) - 4)

#ifndef __SI_ALIGNMENT
# define __SI_ALIGNMENT		/* nothing */
#endif
#ifndef __SI_BAND_TYPE
# define __SI_BAND_TYPE		long int
#endif
#ifndef __SI_ERRNO_THEN_CODE
# define __SI_ERRNO_THEN_CODE	1
#endif
#ifndef __SI_HAVE_SIGSYS
# define __SI_HAVE_SIGSYS	1
#endif
#ifndef __SI_SIGFAULT_ADDL
# define __SI_SIGFAULT_ADDL	/* nothing */
#endif

typedef struct
  {
    int si_signo;		/* Signal number.  */
#if __SI_ERRNO_THEN_CODE
    int si_errno;		/* If non-zero, an errno value associated with
				   this signal, as defined in <errno.h>.  */
    int si_code;		/* Signal code.  */
#else
    int si_code;
    int si_errno;
#endif
#if __WORDSIZE == 64
    int __pad0;			/* Explicit padding.  */
#endif

    union
      {
	int _pad[__SI_PAD_SIZE];

	 /* kill().  */
	struct
	  {
	    __pid_t si_pid;	/* Sending process ID.  */
	    __uid_t si_uid;	/* Real user ID of sending process.  */
	  } _kill;

	/* POSIX.1b timers.  */
	struct
	  {
	    int si_tid;		/* Timer ID.  */
	    int si_overrun;	/* Overrun count.  */
	    __sigval_t si_sigval;	/* Signal value.  */
	  } _timer;

	/* POSIX.1b signals.  */
	struct
	  {
	    __pid_t si_pid;	/* Sending process ID.  */
	    __uid_t si_uid;	/* Real user ID of sending process.  */
	    __sigval_t si_sigval;	/* Signal value.  */
	  } _rt;

	/* SIGCHLD.  */
	struct
	  {
	    __pid_t si_pid;	/* Which child.	 */
	    __uid_t si_uid;	/* Real user ID of sending process.  */
	    int si_status;	/* Exit value or signal.  */
	    __SI_CLOCK_T si_utime;
	    __SI_CLOCK_T si_stime;
	  } _sigchld;

	/* SIGILL, SIGFPE, SIGSEGV, SIGBUS.  */
	struct
	  {
	    void *si_addr;	    /* Faulting insn/memory ref.  */
	    __SI_SIGFAULT_ADDL
	    short int si_addr_lsb;  /* Valid LSB of the reported address.  */
	    union
	      {
		/* used when si_code=SEGV_BNDERR */
		struct
		  {
		    void *_lower;
		    void *_upper;
		  } _addr_bnd;
		/* used when si_code=SEGV_PKUERR */
		__uint32_t _pkey;
	      } _bounds;
	  } _sigfault;

	/* SIGPOLL.  */
	struct
	  {
	    __SI_BAND_TYPE si_band;	/* Band event for SIGPOLL.  */
	    int si_fd;
	  } _sigpoll;

	/* SIGSYS.  */
#if __SI_HAVE_SIGSYS
	struct
	  {
	    void *_call_addr;	/* Calling user insn.  */
	    int _syscall;	/* Triggering system call number.  */
	    unsigned int _arch; /* AUDIT_ARCH_* of syscall.  */
	  } _sigsys;
#endif
      } _sifields;
  } siginfo_t __SI_ALIGNMENT;

#define SIGHUP 1
#define SIGINT 2
#define SIGILL 4
#define SIGABRT 6
#define SIGBUS 7
#define SIGFPE 8
#define SIGUSR1 10
#define SIGSEGV 11
#define SIGPIPE 13
#define	SIGALRM	14	/* Alarm clock.  */
#define SIGTERM 15
#define SIGSTOP 19

/* Values for the HOW argument to `sigprocmask'.  */
#define	SIG_BLOCK     0		 /* Block signals.  */
#define	SIG_UNBLOCK   1		 /* Unblock signals.  */
#define	SIG_SETMASK   2		 /* Set the set of blocked signals.  */

typedef void (*__sighandler_t) (int);
#define	SIG_IGN	 ((__sighandler_t)  1)
#define	SIG_DFL	 ((__sighandler_t)  0)	/* Default action.  */

#define _SIGSET_NWORDS (1024 / (8 * sizeof (unsigned long int)))

#define __USE_POSIX199309 1

#include <bits/types.h>

struct sigaction
  {
    /* Signal handler.  */
#if defined __USE_POSIX199309 || defined __USE_XOPEN_EXTENDED
    union
      {
	/* Used if SA_SIGINFO is not set.  */
	__sighandler_t sa_handler;
	/* Used if SA_SIGINFO is set.  */
	void (*sa_sigaction) (int, siginfo_t *, void *);
      }
    __sigaction_handler;
# define sa_handler	__sigaction_handler.sa_handler
# define sa_sigaction	__sigaction_handler.sa_sigaction
#else
    __sighandler_t sa_handler;
#endif

    /* Additional set of signals to be blocked.  */
    __sigset_t sa_mask;

    /* Special flags.  */
    int sa_flags;

    /* Restore handler.  */
    void (*sa_restorer) (void);
  };

#define SA_SIGINFO 4
#define SA_NODEFER 0x40000000
#define SA_RESETHAND 0x80000000
#endif
#endif