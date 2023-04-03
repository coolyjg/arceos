#include <ctype.h>
#include <stdio.h>
#include <string.h>

int isupper(int c)
{
	return (unsigned)c-'A' < 26;
}

int tolower(int c)
{
    if (isupper(c)) return c | 32;
	return c;
}

int islower(int c)
{
	return (unsigned)c-'a' < 26;
}

int toupper(int c)
{
    if (islower(c)) return c & 0x5f;
	return c;
}

int isalpha(int c)
{
	return ((unsigned)c|32)-'a' < 26;
}

int isprint(int c)
{
	return (unsigned)c-0x20 < 0x5f;
}

int isalnum(int c)
{
	return isalpha(c) || isdigit(c);
}