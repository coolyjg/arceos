#include <sys/utsname.h>
#include <stdio.h>

//TODO
int uname (struct utsname *)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}