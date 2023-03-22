#ifndef __STDIO_H__
#define __STDIO_H__

#define stdin  0
#define stdout 1
#define stderr 2

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

#define SEEK_SET	0	/* Seek from beginning of file.  */
#define SEEK_CUR	1	/* Seek from current position.  */
#define SEEK_END	2	/* Seek from end of file.  */

#ifndef __FILE_defined
#define __FILE_defined 1

struct _IO_FILE;

/* The opaque type of streams.  This is the definition used elsewhere.  */
typedef struct _IO_FILE FILE;

#endif

int getchar();
int putchar(int);
int puts(const char *s);
void fprintf(int f, const char *fmt, ...);
int snprintf ( char * str, int size, const char * format, ... );
int fflush(int);
FILE *fopen(const char *filename, const char *mode);

#define EOF (-1)

#define printf(...) fprintf(stdout, __VA_ARGS__)

#endif // __STDIO_H__
