/*
파일 이름: file_link.c
설명: 링크 생성 (link, symlink)
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "사용법: file_link 파일이름\n");
        exit(1);
    }
    if (link(argv[1], "hard_link") == -1) {
        perror("link");
        exit(1);
    }
    printf("하드 링크 hard_link 생성\n");
    if (symlink(argv[1], "sym_link") == -1) {
        perror("symlink");
        exit(1);
    }
    printf("심볼릭 링크 sym_link 생성\n");
    return 0;
}
