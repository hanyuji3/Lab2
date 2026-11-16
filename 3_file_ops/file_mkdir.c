/*
파일 이름: file_mkdir.c
설명: 디렉토리 생성과 삭제 (mkdir, rmdir)
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "사용법: file_mkdir 디렉토리이름\n");
        exit(1);
    }
    if (mkdir(argv[1], 0755) == -1) {
        perror("mkdir");
        exit(1);
    }
    printf("%s 디렉토리 생성\n", argv[1]);
    if (rmdir(argv[1]) == -1) {
        perror("rmdir");
        exit(1);
    }
    printf("%s 디렉토리 삭제\n", argv[1]);
    return 0;
}
