#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <libax.h>

char **environ = NULL;

// #ifdef AX_CONFIG_FS
int close(int fd)
{
    return ax_close(fd);
}

off_t lseek(int fd, off_t offset, int whence)
{
    return ax_lseek(fd, offset, whence);
}

// TODO
int fsync(int fd)
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

// TODO:
int access(const char *pathname, int mode)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

char *getcwd(char *buf, size_t size)
{
    return ax_getcwd(buf, size);
}

int lstat(const char *path, struct stat *buf)
{
    return ax_lstat(path, buf);
}

int stat(const char *path, struct stat *buf)
{
    return ax_stat(path, buf);
}

int fstat(int fd, struct stat *buf)
{
    return ax_fstat(fd, buf);
}

// TODO:
int ftruncate(int fd, off_t length)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

ssize_t read(int fd, void *buf, size_t count)
{
    return ax_read(fd, buf, count);
}

ssize_t write(int fd, const void *buf, size_t count)
{
    return ax_write(fd, buf, count);
}

// TODO:
int fchown(int fd, uid_t owner, gid_t group)
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

// #endif
// TODO:
long int sysconf(int name)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

unsigned sleep(unsigned seconds)
{
	struct timespec tv = { .tv_sec = seconds, .tv_nsec = 0 };
	if (nanosleep(&tv, &tv))
		return tv.tv_sec;
	return 0;
}

// TODO:
pid_t getpid(void)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    printf("getpid\n");
    return -1;
}

uid_t geteuid(void)
{
    // return __syscall(SYS_geteuid);
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
_Noreturn void _exit(int __status)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    abort();
}

int usleep(unsigned int useconds)
{
    struct timespec tv = {
		.tv_sec = useconds/1000000,
		.tv_nsec = (useconds%1000000)*1000
	};
	return nanosleep(&tv, &tv);
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
int truncate(const char *path, off_t length)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

//TODO
uid_t getuid(void)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}