#ifndef	_DLFCN_H
#define	_DLFCN_H

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

#endif