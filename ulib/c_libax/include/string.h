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
void *memmove(void *__dest, const void *__src, size_t __n);

size_t strlen(const char *s);
size_t strnlen(const char *s, size_t n);
char *strchr(const char *str, int c);
char *strrchr(const char *str, int c);
char *strstr(const char *haystack, const char *needle);
int strcmp(const char *l, const char *r);
char *strncpy(char *restrict d, const char *restrict s, size_t n);
int strncmp(const char *_l, const char *_r, size_t n);

int strcoll(const char *__s1, const char *__s2);
size_t strcspn(const char *s1, const char *s2);
int strcasecmp(const char *__s1, const char *__s2);

char *strrchr(const char *str, int c);
char *strchr(const char *str, int c);

char *strerror(int n);

char *strpbrk(const char *__s, const char *__accept);
char *strdup(const char *__s);

#endif // __STRING_H__
