/*
파일 이름: shm_recv.c
설명: 공유 메모리의 내용을 파일로 저장 (shm_open, mmap, shm_unlink)
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define NAME "/copy_shm"

int main(int argc, char *argv[])
{
    int fd_shm, fd_out;
    struct stat st;
    long size, done;
    int n;
    char *p;

    if (argc != 2) {
        printf("사용법: %s 복사본파일\n", argv[0]);
        return 1;
    }

    fd_shm = shm_open(NAME, O_RDWR, 0666);
    if (fd_shm == -1) {
        perror("shm_open");
        exit(1);
    }
    if (fstat(fd_shm, &st) == -1) {
        perror("fstat");
        exit(1);
    }
    p = mmap(NULL, st.st_size, PROT_READ, MAP_SHARED, fd_shm, 0);
    if (p == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    memcpy(&size, p, sizeof(long));           

    fd_out = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd_out == -1) {
        perror("open");
        exit(1);
    }
    done = 0;
    while (done < size) {                    
        n = write(fd_out, p + sizeof(long) + done, size - done);
        if (n <= 0)
            break;
        done += n;
    }

    printf("[수신] 공유 메모리의 %ld바이트를 %s에 저장했습니다.\n", size, argv[1]);

    munmap(p, st.st_size);
    close(fd_shm);
    close(fd_out);
    shm_unlink(NAME);                         
    return 0;
}
