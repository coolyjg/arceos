#ifndef _FCNTL_H
#define _FCNTL_H

typedef long long int off_t;

#define __USE_XOPEN2K8

#include <bits/types/struct_timespec.h>
#include <bits/types.h>

// struct stat
//   {
// #ifdef __USE_TIME_BITS64
// # include <bits/struct_stat_time64_helper.h>
// #else
//     __dev_t st_dev;		/* Device.  */
// # ifndef __x86_64__
//     unsigned short int __pad1;
// # endif
// # if defined __x86_64__ || !defined __USE_FILE_OFFSET64
//     __ino_t st_ino;		/* File serial number.	*/
// # else
//     __ino_t __st_ino;			/* 32bit file serial number.	*/
// # endif
// # ifndef __x86_64__
//     __mode_t st_mode;			/* File mode.  */
//     __nlink_t st_nlink;			/* Link count.  */
// # else
//     __nlink_t st_nlink;		/* Link count.  */
//     __mode_t st_mode;		/* File mode.  */
// # endif
//     __uid_t st_uid;		/* User ID of the file's owner.	*/
//     __gid_t st_gid;		/* Group ID of the file's group.*/
// # ifdef __x86_64__
//     int __pad0;
// # endif
//     __dev_t st_rdev;		/* Device number, if device.  */
// # ifndef __x86_64__
//     unsigned short int __pad2;
// # endif
// # if defined __x86_64__ || !defined __USE_FILE_OFFSET64
//     __off_t st_size;			/* Size of file, in bytes.  */
// # else
//     __off64_t st_size;			/* Size of file, in bytes.  */
// # endif
//     __blksize_t st_blksize;	/* Optimal block size for I/O.  */
// # if defined __x86_64__  || !defined __USE_FILE_OFFSET64
//     __blkcnt_t st_blocks;		/* Number 512-byte blocks allocated. */
// # else
//     __blkcnt64_t st_blocks;		/* Number 512-byte blocks allocated. */
// # endif
// # ifdef __USE_XOPEN2K8
//     /* Nanosecond resolution timestamps are stored in a format
//        equivalent to 'struct timespec'.  This is the type used
//        whenever possible but the Unix namespace rules do not allow the
//        identifier 'timespec' to appear in the <sys/stat.h> header.
//        Therefore we have to handle the use of this header in strictly
//        standard-compliant sources special.  */
//     struct timespec st_atim;		/* Time of last access.  */
//     struct timespec st_mtim;		/* Time of last modification.  */
//     struct timespec st_ctim;		/* Time of last status change.  */
// #  define st_atime st_atim.tv_sec	/* Backward compatibility.  */
// #  define st_mtime st_mtim.tv_sec
// #  define st_ctime st_ctim.tv_sec
// # else
//     __time_t st_atime;			/* Time of last access.  */
//     __syscall_ulong_t st_atimensec;	/* Nscecs of last access.  */
//     __time_t st_mtime;			/* Time of last modification.  */
//     __syscall_ulong_t st_mtimensec;	/* Nsecs of last modification.  */
//     __time_t st_ctime;			/* Time of last status change.  */
//     __syscall_ulong_t st_ctimensec;	/* Nsecs of last status change.  */
// # endif
// # ifdef __x86_64__
//     __syscall_slong_t __glibc_reserved[3];
// # else
// #  ifndef __USE_FILE_OFFSET64
//     unsigned long int __glibc_reserved4;
//     unsigned long int __glibc_reserved5;
// #  else
//     __ino64_t st_ino;			/* File serial number.	*/
// #  endif
// # endif
// #endif /* __USE_TIME_BITS64  */
//   };
/*
 * FMODE_EXEC is 0x20
 * FMODE_NONOTIFY is 0x4000000
 * These cannot be used by userspace O_* until internal and external open
 * flags are split.
 * -Eric Paris
 */

/*
 * When introducing new O_* bits, please check its uniqueness in fcntl_init().
 */

#define O_ACCMODE 00000003
#ifndef O_RDONLY
#define O_RDONLY  00000000
#endif
#define O_WRONLY  00000001
#define O_RDWR    00000002
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

#endif
