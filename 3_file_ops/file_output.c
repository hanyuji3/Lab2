/*
파일 이름: file_output.c
설명: 표준 출력 재지향 (dup2)
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd;
    char *text = "This is a test output file.\n";

    if (argc < 2) {
        fprintf(stderr, "사용법: file_output 파일이름\n");
        exit(1);
    }
    fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        exit(1);
    }
    dup2(fd, 1);        // 표준 출력(1번)을 fd로 복사
    close(fd);
    write(1, text, strlen(text));   // 화면이 아니라 파일에 써짐
    return 0;
}
