#include <glob.h>
#include <stdio.h>
#include <stdlib.h>

struct match
{
	struct match *next;
	char name[];
};

// TODO
int glob(const char *__restrict__ __pattern, int __flags, int (*__errfunc)(const char *, int),
         glob_t *__restrict__ __pglob)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

#define offsetof(t, d) __builtin_offsetof(t, d)

void globfree(glob_t *g)
{
	size_t i;
	for (i=0; i<g->gl_pathc; i++)
		free(g->gl_pathv[g->gl_offs + i] - offsetof(struct match, name));
	free(g->gl_pathv);
	g->gl_pathc = 0;
	g->gl_pathv = NULL;
}