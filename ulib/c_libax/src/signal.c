#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <errno.h>

// TODO
int kill(pid_t __pid, int __sig)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO
void (*signal(int sig, void (*func)(int)))(int)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

int sigemptyset(sigset_t *set)
{
	set->__bits[0] = 0;
	if (sizeof(long)==4 || _NSIG > 65) set->__bits[1] = 0;
	if (sizeof(long)==4 && _NSIG > 65) {
		set->__bits[2] = 0;
		set->__bits[3] = 0;
	}
	return 0;
}

// TODO
int sigaction(int __sig, const struct sigaction *__restrict__ __act,
              struct sigaction *__restrict__ __oact)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO
int raise(int __sig)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

int sigaddset(sigset_t *set, int sig)
{
	unsigned s = sig-1;
	if (s >= _NSIG-1 || sig-32U < 3) {
		errno = EINVAL;
		return -1;
	}
	set->__bits[s/8/sizeof *set->__bits] |= 1UL<<(s&8*sizeof *set->__bits-1);
	return 0;
}

// TODO
int pthread_sigmask(int __how, const sigset_t *__restrict__ __newmask,
                    sigset_t *__restrict__ __oldmask)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}