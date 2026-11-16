/*
파일 이름: file_size.c
설명: 파일 크기 알아내기 (lseek)
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd;
    off_t size;

    if (argc < 2) {
        fprintf(stderr, "사용법: file_size 파일이름\n");
        exit(1);
    }
    fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }
    size = lseek(fd, 0, SEEK_END);      // 파일 끝 위치 = 파일 크기
    printf("%s의 크기 = %ld바이트\n", argv[1], (long)size);
    close(fd);
    return 0;
}
