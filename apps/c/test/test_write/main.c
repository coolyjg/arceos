#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void test_write(){
    int f = open("text.txt", O_WRONLY | O_CREAT);
    char buf[5000];
    for (int i = 0; i < 5000; i++) buf[i] = 'a';
    int len = write(f, buf, 5000);
    printf("write: len = %d\n", len);
    int len2 = write(f, buf + len, 5000 - len);
    printf("write: len2 = %d\n", len2);
    close(f);
}

void test_fwrite(){
    FILE* f = fopen("text2.txt", "a");
    char buf[5000];
    for (int i = 0; i < 5000; i++) buf[i] = 'a';
    int len = fwrite(buf, 1, 5000, f);
    printf("fwrite: len = %d\n", len);
    fclose(f);
}

int main()
{
    test_write();
    test_fwrite();
    return 0;
}
