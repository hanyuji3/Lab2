/*
파일 이름: fifo_write.c
설명: FIFO에 메시지 쓰기 (open, write)
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    int fd;
    char *msg = "FIFO 예제중!";

    fd = open("myfifo", O_WRONLY);        
    if (fd == -1) {
        perror("open");
        exit(1);
    }
    write(fd, msg, strlen(msg));
    printf("[쓰기] 메시지를 보냈습니다.\n");
    close(fd);
    return 0;
}
