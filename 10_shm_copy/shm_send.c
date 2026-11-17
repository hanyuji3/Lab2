/*
파일 이름: shm_send.c
설명: 파일 내용을 POSIX 공유 메모리에 올리기 (shm_open, ftruncate, mmap)
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
    int fd_in, fd_shm;
    struct stat st;
    long size, done;
    int n;
    char *p;

    if (argc != 2) {
        printf("사용법: %s 원본파일\n", argv[0]);
        return 1;
    }

    fd_in = open(argv[1], O_RDONLY);
    if (fd_in == -1) {
        perror("open");
        exit(1);
    }
    if (fstat(fd_in, &st) == -1) {
        perror("fstat");
        exit(1);
    }
    size = st.st_size;                         

    shm_unlink(NAME);                          
    fd_shm = shm_open(NAME, O_CREAT | O_RDWR, 0666);
    if (fd_shm == -1) {
        perror("shm_open");
        exit(1);
    }
    if (ftruncate(fd_shm, sizeof(long) + size) == -1) {   
        perror("ftruncate");
        exit(1);
    }
    p = mmap(NULL, sizeof(long) + size, PROT_READ | PROT_WRITE,
             MAP_SHARED, fd_shm, 0);
    if (p == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    memcpy(p, &size, sizeof(long));            
    done = 0;
    while (done < size) {                     
        n = read(fd_in, p + sizeof(long) + done, size - done);
        if (n <= 0)
            break;
        done += n;
    }

    printf("[송신] %s (%ld바이트)를 공유 메모리 %s에 올렸습니다.\n",
           argv[1], size, NAME);

    munmap(p, sizeof(long) + size);
    close(fd_shm);
    close(fd_in);
    return 0;
}
