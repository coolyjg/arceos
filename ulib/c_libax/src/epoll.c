#include <stdio.h>
#include <sys/epoll.h>

//TODO
int epoll_create(int __size){
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

//TODO
int epoll_ctl(int, int, int, struct epoll_event *){
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}

//TODO
int epoll_wait(int, struct epoll_event *, int, int){
    printf("%s%s\n", "Error: no ax_call implementation for ", __func__);
    return 0;
}
