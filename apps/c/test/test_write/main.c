#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
    int f = open("text.txt", O_WRONLY | O_CREAT);
    char buf[5000];
    for (int i = 0; i < 5000; i++) buf[i] = 'a';
    int len = write(f, buf, 5000);
    printf("len = %d\n", len);
    int len2 = write(f, buf + len, 5000 - len);
    printf("len2 = %d\n", len2);
    close(f);
    return 0;
}
