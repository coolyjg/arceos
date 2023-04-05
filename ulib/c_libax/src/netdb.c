#include <netdb.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

// TODO
int getaddrinfo(const char *__restrict__ __name, const char *__restrict__ __service,
                const struct addrinfo *__restrict__ __req, struct addrinfo **__restrict__ __pai)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

static const char msgs[] =
	"Invalid flags\0"
	"Name does not resolve\0"
	"Try again\0"
	"Non-recoverable error\0"
	"Unknown error\0"
	"Unrecognized address family or invalid length\0"
	"Unrecognized socket type\0"
	"Unrecognized service\0"
	"Unknown error\0"
	"Out of memory\0"
	"System error\0"
	"Overflow\0"
	"\0Unknown error";

const char *__lctrans_cur(const char *msg)
{
	return msg;
}

#define LCTRANS_CUR(msg) __lctrans_cur(msg)

const char *gai_strerror(int ecode)
{
	const char *s;
	for (s=msgs, ecode++; ecode && *s; ecode++, s++) for (; *s; s++);
	if (!*s) s++;
	return LCTRANS_CUR(s);
}

//TODO
void freeaddrinfo(struct addrinfo *p)
{
	size_t cnt;
	for (cnt=1; p->ai_next; cnt++, p=p->ai_next);
	struct aibuf *b = (void *)((char *)p - offsetof(struct aibuf, ai));
	b -= b->slot;
	// LOCK(b->lock);
	// if (!(b->ref -= cnt)) free(b);
	// else UNLOCK(b->lock);
}