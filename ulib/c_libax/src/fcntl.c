#include <fcntl.h>
#include <libax.h>
#include <stdio.h>

// TODO:
int fcntl(int fd, int cmd, ... /* arg */)
{
    unimplemented("fd: %d cmd: %d", fd, cmd);
    return 0;
}

int open(const char *filename, int flags, ...)
{
    mode_t mode = 0;

    if ((flags & O_CREAT) || (flags & O_TMPFILE) == O_TMPFILE) {
        va_list ap;
        va_start(ap, flags);
        mode = va_arg(ap, mode_t);
        va_end(ap);
    }

    return ax_open(filename, flags, mode);
}

// TODO
int posix_fadvise(int __fd, unsigned long __offset, unsigned long __len, int __advise)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

//TODO
int sync_file_range(int, off_t, off_t, unsigned)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}