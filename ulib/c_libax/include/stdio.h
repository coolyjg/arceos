#ifndef __STDIO_H__
#define __STDIO_H__

typedef long __off_t;

#include <stddef.h>

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

#define _IOFBF 0
#define _IOLBF 1
#define _IONBF 2

#define SEEK_SET	0	/* Seek from beginning of file.  */
#define SEEK_CUR	1	/* Seek from current position.  */
#define SEEK_END	2	/* Seek from end of file.  */

// #ifndef __FILE_defined
// #define __FILE_defined 1

// struct _IO_FILE;

// /* The opaque type of streams.  This is the definition used elsewhere.  */
// typedef struct _IO_FILE FILE;

// #endif

struct _IO_FILE {
    int _flags; /* High-order word is _IO_MAGIC; rest is flags. */

    /* The following pointers correspond to the C++ streambuf protocol. */
    char *_IO_read_ptr;   /* Current read pointer */
    char *_IO_read_end;   /* End of get area. */
    char *_IO_read_base;  /* Start of putback+get area. */
    char *_IO_write_base; /* Start of put area. */
    char *_IO_write_ptr;  /* Current put pointer. */
    char *_IO_write_end;  /* End of put area. */
    char *_IO_buf_base;   /* Start of reserve area. */
    char *_IO_buf_end;    /* End of reserve area. */

    /* The following fields are used to support backing up and undo. */
    char *_IO_save_base;   /* Pointer to start of non-current get area. */
    char *_IO_backup_base; /* Pointer to first valid character of backup area */
    char *_IO_save_end;    /* Pointer to end of non-current get area. */

    struct _IO_marker *_markers;

    struct _IO_FILE *_chain;

    int _fileno;
    int _flags2;
    __off_t _old_offset; /* This used to be _offset but it's too small.  */

    /* 1+column number of pbase(); 0 is unknown. */
    unsigned short _cur_column;
    signed char _vtable_offset;
    char _shortbuf[1];

    //   _IO_lock_t *_lock;
};

typedef struct _IO_FILE FILE;

// extern FILE *const stdin;
// extern FILE *const stdout;
// extern FILE *const stderr;

// #define stdin  (stdin)
// #define stdout (stdout)
// #define stderr (stderr)

#define stdin 0
#define stdout 1
#define stderr 2

#define EOF (-1)

#define BUFSIZ 1024

int fprintf(int f, const char *fmt, ...);

#define printf(...) fprintf(1, __VA_ARGS__)

#define S_IFMT   00170000
#define S_IFSOCK 0140000
#define S_IFLNK  0120000
#define S_IFREG  0100000
#define S_IFBLK  0060000
#define S_IFDIR  0040000
#define S_IFCHR  0020000
#define S_IFIFO  0010000
#define S_ISUID  0004000
#define S_ISGID  0002000
#define S_ISVTX  0001000

#define S_ISLNK(m)  (((m)&S_IFMT) == S_IFLNK)
#define S_ISREG(m)  (((m)&S_IFMT) == S_IFREG)
#define S_ISDIR(m)  (((m)&S_IFMT) == S_IFDIR)
#define S_ISCHR(m)  (((m)&S_IFMT) == S_IFCHR)
#define S_ISBLK(m)  (((m)&S_IFMT) == S_IFBLK)
#define S_ISFIFO(m) (((m)&S_IFMT) == S_IFIFO)
#define S_ISSOCK(m) (((m)&S_IFMT) == S_IFSOCK)

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

int getchar();
int putchar(int);
int puts(const char *s);

int snprintf ( char * str, int size, const char * format, ... );
#include<stdarg.h>
int vsnprintf(char *__restrict__ __s, unsigned long __maxlen, const char *__restrict__ __format, va_list __arg);
int fflush(int);
//TODO: should be FILE*
int fopen(const char *filename, const char *mode);

int sscanf(const char *__restrict__ __s, const char *__restrict__ __format, ...);

unsigned long fread(void *__restrict__ __ptr, unsigned long __size, unsigned long __n, FILE *__restrict__ __stream);
unsigned long fwrite(const void *__restrict__ __ptr, unsigned long, unsigned long, FILE *__restrict);

int fclose(FILE *__stream);
char *fgets(char *__restrict__ __s, int __n, FILE *__restrict__ __stream);

void perror(const char *__s);

int rename(const char *__old, const char *__new);

int fileno(FILE *__stream);
int feof(FILE *__stream);
int fseek(FILE *__stream, long __off, int __whence);
long ftello(FILE *__stream);


#endif // __STDIO_H__
