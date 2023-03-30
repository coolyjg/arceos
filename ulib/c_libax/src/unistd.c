#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

// TODO:
long int sysconf(int name)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO:
off_t lseek(int fd, off_t offset, int whence)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO:
unsigned int sleep(unsigned int seconds)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO:
pid_t getpid(void)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    printf("getpid\n");
    return -1;
}

// TODO:
int fsync(int fd)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO:
int close(int fd)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return -1;
}

// TODO:
int access(const char *pathname, int mode)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO:
char *getcwd(char *buf, size_t size)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO:
int lstat(const char *path, struct stat *buf)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO:
int stat(const char *path, struct stat *buf)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO:
int fstat(int fd, struct stat *buf)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO:
int ftruncate(int fd, off_t length)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO:
ssize_t read(int fd, void *buf, size_t count)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO:
ssize_t write(int fd, const void *buf, size_t count)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO:
int unlink(const char *pathname)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO:
int rmdir(const char *pathname)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO:
int fchown(int fd, uid_t owner, gid_t group)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO:
uid_t geteuid(void)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO:
ssize_t readlink(const char *path, char *buf, size_t bufsiz)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO
int pipe(int *__pipedes)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO
int pipe2(int *__pipedes, int __flags)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO
int fdatasync(int __fildes)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO
_Noreturn void _exit(int __status)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
}

// TODO
int usleep(unsigned int __useconds)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO
int execve(const char *__path, char *const *__argv, char *const *__envp)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO
pid_t setsid(void)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO
int dup2(int __fd, int __fd2)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO
int isatty(int __fd)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO
pid_t fork(void)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO
int chdir(const char *__path)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO
int truncate(const char *__file, loff_t __length)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}