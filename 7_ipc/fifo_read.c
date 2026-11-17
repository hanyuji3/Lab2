/*
파일 이름: fifo_read.c
설명: FIFO에서 메시지 읽기 (mkfifo, open, read)
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>

int main(void)
{
    int fd, n;
    char buf[100];

    if (mkfifo("myfifo", 0666) == -1 && errno != EEXIST) {
        perror("mkfifo");
        exit(1);
    }
    printf("[읽기] 메시지를 기다립니다...\n");
    fd = open("myfifo", O_RDONLY);       
    if (fd == -1) {
        perror("open");
        exit(1);
    }
    n = read(fd, buf, sizeof(buf) - 1);
    if (n == -1) {
        perror("read");
        exit(1);
    }
    buf[n] = '\0';
    printf("[읽기] 받은 메시지: %s\n", buf);
    close(fd);
    return 0;
}
