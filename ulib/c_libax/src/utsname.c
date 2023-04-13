#include <stdio.h>
#include <sys/utsname.h>

// TODO
int uname(struct utsname *)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}