#ifndef __SYS_STAT__
#define __SYS_STAT__

#include <sys/types.h>
#include <time.h>

#ifndef O_EXCL
#define O_EXCL 1 // TODO;
#endif
#ifndef O_CREAT
#define O_CREAT 2 // TODO;
#endif
#ifndef O_RDONLY
#define O_RDONLY 3 // TODO;
#endif

#ifndef S_IRUSR
#define S_IRUSR 0400
#define S_IWUSR 0200
#define S_IXUSR 0100
#define S_IRWXU 0700
#define S_IRGRP 0040
#define S_IWGRP 0020
#define S_IXGRP 0010
#define S_IRWXG 0070
#define S_IROTH 0004
#define S_IWOTH 0002
#define S_IXOTH 0001
#define S_IRWXO 0007
#endif

struct stat {
    dev_t st_dev;         /* ID of device containing file*/
    ino_t st_ino;         /* inode number*/
    mode_t st_mode;       /* protection*/
    nlink_t st_nlink;     /* number of hard links*/
    uid_t st_uid;         /* user ID of owner*/
    gid_t st_gid;         /* group ID of owner*/
    dev_t st_rdev;        /* device ID (if special file)*/
    off_t st_size;        /* total size, in bytes*/
    blksize_t st_blksize; /* blocksize for filesystem I/O*/
    blkcnt_t st_blocks;   /* number of blocks allocated*/
    time_t st_atime;      /* time of last access*/
    time_t st_mtime;      /* time of last modification*/
    time_t st_ctime;      /* time of last status change*/
};

int fchmod(int fd, mode_t mode);
int mkdir(const char *pathname, mode_t mode);
int chmod(const char *__file, mode_t __mode);
mode_t umask(mode_t __mask);

#endif
