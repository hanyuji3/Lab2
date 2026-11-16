/*
파일 이름: file_stat.c
설명: 파일 정보 확인 (stat, access)
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    struct stat st;

    if (argc < 2) {
        fprintf(stderr, "사용법: file_stat 파일이름\n");
        exit(1);
    }
    if (stat(argv[1], &st) == -1) {
        perror("stat");
        exit(1);
    }
    printf("크기: %ld바이트\n", (long)st.st_size);
    printf("권한: %o\n", st.st_mode & 0777);
    printf("링크 수: %d\n", (int)st.st_nlink);
    if (S_ISREG(st.st_mode))
        printf("종류: 일반 파일\n");
    else if (S_ISDIR(st.st_mode))
        printf("종류: 디렉토리\n");
    if (access(argv[1], W_OK) == 0)
        printf("쓰기 가능\n");
    else
        printf("쓰기 불가\n");
    return 0;
}
