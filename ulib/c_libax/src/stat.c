#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

// TODO:
int fchmod(int fd, mode_t mode)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO:
int mkdir(const char *pathname, mode_t mode)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO
int chmod(const char *__file, mode_t __mode)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO
mode_t umask(mode_t __mask)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

//TODO
int fstatat(int, const char *__restrict, struct stat *__restrict, int)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}