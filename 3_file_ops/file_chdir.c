/*
파일 이름: file_chdir.c
설명: 작업 디렉토리 확인과 이동 (getcwd, chdir)
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    char buf[256];

    if (argc < 2) {
        fprintf(stderr, "사용법: file_chdir 디렉토리이름\n");
        exit(1);
    }
    getcwd(buf, sizeof(buf));
    printf("이동 전: %s\n", buf);
    if (chdir(argv[1]) == -1) {
        perror("chdir");
        exit(1);
    }
    getcwd(buf, sizeof(buf));
    printf("이동 후: %s\n", buf);
    return 0;
}
