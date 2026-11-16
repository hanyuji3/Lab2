/*
파일 이름: file_creat.c
설명: 파일 생성과 쓰기 (open O_CREAT|O_TRUNC, write)
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd;
    int n;
    char *text = "This is a test.";

    if (argc < 2) {
        fprintf(stderr, "사용법: file_creat 파일이름\n");
        exit(1);
    }
    fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        exit(1);
    }
    n = write(fd, text, strlen(text));
    printf("write count = %d\n", n);
    close(fd);
    return 0;
}
