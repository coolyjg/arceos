#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
    int f = open("test.txt", O_CREAT | O_RDWR);
    char *buf = "hello";
    int len = write(f, buf, sizeof(buf));
    printf("write size: %d\n", len);
    close(f);
    int res = rename("test.txt", "test2.txt");
    int f2 = open("test.txt", O_RDONLY);
    printf("f2: %d\n", f2);
    f2 = open("test2.txt", O_RDONLY);
    char buf2[64];
    read(f2, buf2, 5);
    buf2[6] = '\0';
    printf("buf2: %s\n", buf2);
    return 0;
}
