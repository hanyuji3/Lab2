/*
파일 이름: file_copy.c
설명: 텍스트 파일 복사 (표준 입출력 fopen, fgetc, fputc)
*/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *src;
    FILE *dst;
    int ch;
    int count = 0;

    if (argc < 3) {
        fprintf(stderr, "사용법: file_copy 원본 사본\n");
        exit(1);
    }
    src = fopen(argv[1], "r");
    if (src == NULL) {
        perror("fopen src");
        exit(1);
    }
    dst = fopen(argv[2], "w");
    if (dst == NULL) {
        perror("fopen dst");
        exit(1);
    }
    while ((ch = fgetc(src)) != EOF) {
        fputc(ch, dst);
        count++;
    }
    printf("%d바이트 복사 완료\n", count);
    fclose(src);
    fclose(dst);
    return 0;
}

