#include <signal.h>
#include <stddef.h>
#include <stdio.h>

// TODO
int kill(pid_t __pid, int __sig)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO
sighandler_t signal(int __sig, sighandler_t __handler)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return NULL;
}

// TODO
int sigemptyset(sigset_t *__set)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
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

// TODO
int sigaddset(sigset_t *__set, int __signo)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

// TODO
int pthread_sigmask(int __how, const sigset_t *__restrict__ __newmask,
                    sigset_t *__restrict__ __oldmask)
{
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}