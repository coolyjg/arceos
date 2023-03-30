#ifndef _DLFCN_H
#define _DLFCN_H

#define RTLD_LAZY     1
#define RTLD_NOW      2
#define RTLD_NOLOAD   4
#define RTLD_NODELETE 4096
#define RTLD_GLOBAL   256
#define RTLD_LOCAL    0

// #if defined(_GNU_SOURCE) || defined(_BSD_SOURCE)
typedef struct {
    const char *dli_fname;
    void *dli_fbase;
    const char *dli_sname;
    void *dli_saddr;
} Dl_info;
int dladdr(const void *__address, Dl_info *__info);
// int dlinfo(void *, int, void *);
// #endif

void *dlopen(const char *__file, int __mode);
char *dlerror(void);
void *dlsym(void *__restrict__ __handle, const char *__restrict__ __name);
int dlclose(void *__handle);

#endif