// /* Copyright (C) 1991-2022 Free Software Foundation, Inc.
//    This file is part of the GNU C Library.

//    The GNU C Library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU Lesser General Public
//    License as published by the Free Software Foundation; either
//    version 2.1 of the License, or (at your option) any later version.

//    The GNU C Library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Lesser General Public License for more details.

//    You should have received a copy of the GNU Lesser General Public
//    License along with the GNU C Library; if not, see
//    <https://www.gnu.org/licenses/>.  */

// /*
//  *	POSIX Standard: 6.5 File Control Operations	<fcntl.h>
//  */

#ifndef _FCNTL_H
#define _FCNTL_H

typedef long off_t;
#define O_APPEND 02000
#define O_CREAT 0100
#define O_RDONLY 00
#define O_WRONLY 01
#define O_RDWR 02
#ifndef O_NONBLOCK
# define O_NONBLOCK	  04000
#endif
#ifndef __O_CLOEXEC
# define __O_CLOEXEC   02000000
# define O_CLOEXEC	__O_CLOEXEC
#endif
#ifndef O_TRUNC
# define O_TRUNC	  01000	/* Not fcntl.  */
#endif

#define F_DUPFD		0	/* Duplicate file descriptor.  */
#define F_GETFD		1	/* Get file descriptor flags.  */
#define F_SETFD		2	/* Set file descriptor flags.  */
#define F_GETFL		3	/* Get file status flags.  */
#define F_SETFL		4	/* Set file status flags.  */

#define FD_CLOEXEC	1

#define __USE_XOPEN2K8

#include <bits/types/struct_timespec.h>
#include <bits/types.h>

struct stat
  {
#ifdef __USE_TIME_BITS64
# include <bits/struct_stat_time64_helper.h>
#else
    __dev_t st_dev;		/* Device.  */
# ifndef __x86_64__
    unsigned short int __pad1;
# endif
# if defined __x86_64__ || !defined __USE_FILE_OFFSET64
    __ino_t st_ino;		/* File serial number.	*/
# else
    __ino_t __st_ino;			/* 32bit file serial number.	*/
# endif
# ifndef __x86_64__
    __mode_t st_mode;			/* File mode.  */
    __nlink_t st_nlink;			/* Link count.  */
# else
    __nlink_t st_nlink;		/* Link count.  */
    __mode_t st_mode;		/* File mode.  */
# endif
    __uid_t st_uid;		/* User ID of the file's owner.	*/
    __gid_t st_gid;		/* Group ID of the file's group.*/
# ifdef __x86_64__
    int __pad0;
# endif
    __dev_t st_rdev;		/* Device number, if device.  */
# ifndef __x86_64__
    unsigned short int __pad2;
# endif
# if defined __x86_64__ || !defined __USE_FILE_OFFSET64
    __off_t st_size;			/* Size of file, in bytes.  */
# else
    __off64_t st_size;			/* Size of file, in bytes.  */
# endif
    __blksize_t st_blksize;	/* Optimal block size for I/O.  */
# if defined __x86_64__  || !defined __USE_FILE_OFFSET64
    __blkcnt_t st_blocks;		/* Number 512-byte blocks allocated. */
# else
    __blkcnt64_t st_blocks;		/* Number 512-byte blocks allocated. */
# endif
# ifdef __USE_XOPEN2K8
    /* Nanosecond resolution timestamps are stored in a format
       equivalent to 'struct timespec'.  This is the type used
       whenever possible but the Unix namespace rules do not allow the
       identifier 'timespec' to appear in the <sys/stat.h> header.
       Therefore we have to handle the use of this header in strictly
       standard-compliant sources special.  */
    struct timespec st_atim;		/* Time of last access.  */
    struct timespec st_mtim;		/* Time of last modification.  */
    struct timespec st_ctim;		/* Time of last status change.  */
#  define st_atime st_atim.tv_sec	/* Backward compatibility.  */
#  define st_mtime st_mtim.tv_sec
#  define st_ctime st_ctim.tv_sec
# else
    __time_t st_atime;			/* Time of last access.  */
    __syscall_ulong_t st_atimensec;	/* Nscecs of last access.  */
    __time_t st_mtime;			/* Time of last modification.  */
    __syscall_ulong_t st_mtimensec;	/* Nsecs of last modification.  */
    __time_t st_ctime;			/* Time of last status change.  */
    __syscall_ulong_t st_ctimensec;	/* Nsecs of last status change.  */
# endif
# ifdef __x86_64__
    __syscall_slong_t __glibc_reserved[3];
# else
#  ifndef __USE_FILE_OFFSET64
    unsigned long int __glibc_reserved4;
    unsigned long int __glibc_reserved5;
#  else
    __ino64_t st_ino;			/* File serial number.	*/
#  endif
# endif
#endif /* __USE_TIME_BITS64  */
  };

#endif