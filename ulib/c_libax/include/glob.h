#ifndef _GLOB_H
#define _GLOB_H

#include <stddef.h>

typedef struct {
    size_t gl_pathc;
    char **gl_pathv;
    size_t gl_offs;
    int __dummy1;
    void *__dummy2[5];
} glob_t;

int glob(const char *__restrict__ __pattern, int __flags, int (*__errfunc)(const char *, int),
         glob_t *__restrict__ __pglob);
void globfree(glob_t *__pglob);

#endif