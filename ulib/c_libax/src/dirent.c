#include <stdio.h>
#include <dirent.h>

//TODO
int closedir(DIR * __dirp)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

//TODO
DIR *fdopendir(int __fd)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return NULL;
}

//TODO
DIR *opendir(const char * __name)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return NULL;
}

//TODO
struct dirent *readdir(DIR *__dirp)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return NULL;
}

//TODO
int readdir_r(DIR *__restrict __dirp, struct dirent *__restrict, struct dirent **__restrict)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

//TODO
void rewinddir(DIR *__dirp)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return ;
}

//TODO
int dirfd(DIR *__dirp)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}