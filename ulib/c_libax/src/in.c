#include <netinet/in.h>
#include <stdio.h>

static __inline uint16_t __bswap_16(uint16_t __x)
{
	return __x<<8 | __x>>8;
}

static __inline uint32_t __bswap_32(uint32_t __x)
{
	return __x>>24 | (__x>>8&0xff00) | (__x<<8&0xff0000) | __x<<24;
}

static __inline uint64_t __bswap_64(uint64_t __x)
{
	return ((__bswap_32(__x)+0ULL)<<32) | __bswap_32(__x>>32);
}

#define bswap_16(x) __bswap_16(x)
#define bswap_32(x) __bswap_32(x)
#define bswap_64(x) __bswap_64(x)

uint16_t ntohs(uint16_t n)
{
	union { int i; char c; } u = { 1 };
	return u.c ? bswap_16(n) : n;
}

uint32_t htonl(uint32_t n)
{
	union { int i; char c; } u = { 1 };
	return u.c ? bswap_32(n) : n;
}

uint32_t ntohl(uint32_t n)
{
	union { int i; char c; } u = { 1 };
	return u.c ? bswap_32(n) : n;
}

uint16_t htons(uint16_t n)
{
	union { int i; char c; } u = { 1 };
	return u.c ? bswap_16(n) : n;
}
