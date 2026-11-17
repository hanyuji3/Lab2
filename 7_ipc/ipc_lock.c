/*
파일 이름: ipc_lock.c
설명: 레코드 잠금 (fcntl, F_SETLKW)
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    int fd;
    pid_t pid;
    struct flock testlock;

    testlock.l_type = F_WRLCK;         
    testlock.l_whence = SEEK_SET;
    testlock.l_start = 0;
    testlock.l_len = 10;               

    fd = open("testlock", O_RDWR | O_CREAT, 0666);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    if (fcntl(fd, F_SETLKW, &testlock) == -1) {
        perror("parent: locking");
        exit(1);
    }
    printf("parent: locked record\n");

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        testlock.l_len = 5;            
        if (fcntl(fd, F_SETLKW, &testlock) == -1) {
            perror("child: locking");
            exit(1);
        }
        printf("child: locked\n");
        sleep(5);
        printf("child: exiting\n");
    } else {
        sleep(5);
        printf("parent: exiting\n");
    }
    return 0;
}
