#ifndef __STDINT_H__
#define __STDINT_H__

/* Explicitly-sized versions of integer types */
typedef char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned int uint32_t;
typedef unsigned int __uint32_t;
typedef long long int64_t;
typedef unsigned long long uint64_t;
typedef long intmax_t;

#define UINT64_MAX		(__UINT64_C(18446744073709551615))
#define SIZE_MAX (18446744073709551615UL)

#define __WORDSIZE	64
# if __WORDSIZE == 64
#  define INTPTR_MIN		(-9223372036854775807L-1)
#  define INTPTR_MAX		(9223372036854775807L)
#  define UINTPTR_MAX		(18446744073709551615UL)
# else
#  define INTPTR_MIN		(-2147483647-1)
#  define INTPTR_MAX		(2147483647)
#  define UINTPTR_MAX		(4294967295U)
# endif

/* *
 * Pointers and addresses are 32 bits long.
 * We use pointer types to represent addresses,
 * uintptr_t to represent the numerical values of addresses.
 * */
#if __riscv_xlen == 64 || defined(__x86_64__) || defined(__aarch64__)
typedef int64_t intptr_t;
typedef uint64_t uintptr_t;
#elif __riscv_xlen == 32 || defined(__i386__)
typedef int32_t intptr_t;
typedef uint32_t uintptr_t;
#endif

#endif // __STDINT_H__
