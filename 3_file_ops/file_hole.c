/*
파일 이름: file_hole.c
설명: 파일 크기 늘리기 (lseek 후 write)
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd;
    off_t before, after;

    if (argc < 3) {
        fprintf(stderr, "사용법: file_hole 파일이름 늘릴크기\n");
        exit(1);
    }
    fd = open(argv[1], O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(1);
    }
    before = lseek(fd, 0, SEEK_END);
    printf("Before: %ld바이트\n", (long)before);

    lseek(fd, atoi(argv[2]), SEEK_END);   // 파일 끝을 넘어 이동
    write(fd, ".", 1);                    // write를 해야 크기가 늘어남

    after = lseek(fd, 0, SEEK_END);
    printf("After : %ld바이트\n", (long)after);
    close(fd);
    return 0;
}
