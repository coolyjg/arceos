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
//  *	ISO C99 Standard: 7.5 Errors	<errno.h>
//  */

#define EINTR 4
#define EEXIST 17
#define EINVAL 22

// #define errno 1/*todo*/

int *__errno_location(void);
#define errno (*__errno_location ())

#define ENOPROTOOPT 92
#define EPROTONOSUPPORT 93
#define ESOCKTNOSUPPORT 94
#define EPFNOSUPPORT 96
#define EAFNOSUPPORT 97
#define EADDRNOTAVAIL 99