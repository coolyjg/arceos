#ifndef __UNISTD_H__
#define __UNISTD_H__

#include <stddef.h>
#include <sys/stat.h>
#include <sys/types.h>

// #define _SC_PAGESIZE 30
#define X_OK 1
#define F_OK 0
// char **environ;

// char **environ = 0;
extern char **environ;

// #ifdef AX_CONFIG_FS
int close(int fd);
off_t lseek(int fd, off_t offset, int whence);
int fsync(int fd);
int fdatasync(int __fildes);

int access(const char *pathname, int mode);
char *getcwd(char *buf, size_t size);
int lstat(const char *path, struct stat *buf);
int stat(const char *path, struct stat *buf);
int fstat(int fd, struct stat *buf);
int ftruncate(int fd, off_t length);
ssize_t read(int fd, void *buf, size_t count);
ssize_t write(int fd, const void *buf, size_t count);

int fchown(int fd, uid_t owner, gid_t group);

ssize_t readlink(const char *path, char *buf, size_t bufsiz);
int unlink(const char *pathname);
int rmdir(const char *pathname);

// #endif

unsigned sleep(unsigned seconds);

uid_t geteuid(void);

int pipe(int *__pipedes);
int pipe2(int *__pipedes, int __flags);

_Noreturn void _exit(int __status);

int usleep(unsigned int __useconds);
int execve(const char *__path, char *const *__argv, char *const *__envp);

pid_t setsid(void);

int dup2(int __fd, int __fd2);
int isatty(int __fd);
pid_t fork(void);

int chdir(const char *__path);
int truncate(const char *path, off_t length);
uid_t getuid(void);

#endif
