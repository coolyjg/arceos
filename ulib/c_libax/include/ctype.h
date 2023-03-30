#ifndef _CTYPE_H
#define _CTYPE_H

int tolower(int __c);
int toupper(int __c);

int isprint(int);
#define isprint(a) (0 ? isprint(a) : ((unsigned)(a)-0x20) < 0x5f)
// #define isprint(a) ((unsigned)(a)-0x20) < 0x5f

int isalnum(int);

#endif