#include <stdio.h>
#include <glob.h>

//TODO
int glob(const char *__restrict__ __pattern, int __flags, int (*__errfunc)(const char *, int), glob_t *__restrict__ __pglob)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

//TODO
void globfree(glob_t *__pglob)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return ;
}