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
//  *	ISO C99 Standard: 7.23 Date and time	<time.h>
//  */
#include <bits/types/struct_tm.h>
typedef long time_t;
// typedef long __time_t;
// typedef long __suseconds_t;
// typedef long __time64_t;
// #define __suseconds64_t __suseconds_t

// struct timeval
// {
// #ifdef __USE_TIME_BITS64
//   __time64_t tv_sec;		/* Seconds.  */
//   __suseconds64_t tv_usec;	/* Microseconds.  */
// #else
//   __time_t tv_sec;		/* Seconds.  */
//   __suseconds_t tv_usec;	/* Microseconds.  */
// #endif
// };
