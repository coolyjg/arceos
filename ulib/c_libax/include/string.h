#ifndef __STRING_H__
#define __STRING_H__

#include <stdint.h>
#include <stddef.h>

int isspace(int c);
int isdigit(int c);
int atoi(const char *s);

void *memset(void *dest, int c, size_t n);
void *memchr(const void *src, int c, size_t n);
int memcmp(const void *str1, const void *str2, size_t n);
void *memcpy(void *dest, const void * src, size_t n);

size_t strlen(const char *s);
size_t strnlen(const char *s, size_t n);
char *strchr(const char *str, int c);
char *strrchr(const char *str, int c);
char *strstr(const char *haystack, const char *needle);
int strcmp(const char *l, const char *r);
char *strncpy(char *restrict d, const char *restrict s, size_t n);
int strncmp(const char *_l, const char *_r, size_t n);

#endif // __STRING_H__
