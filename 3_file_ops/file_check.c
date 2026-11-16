/*
파일 이름: file_check.c
설명: 파일 열기/닫기 (open, close)
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd;

    if (argc < 2) {
        fprintf(stderr, "사용법: file_check 파일이름\n");
        exit(1);
    }
    fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }
    printf("\"%s\" 파일을 열었습니다. (fd = %d)\n", argv[1], fd);
    close(fd);
    return 0;
}
