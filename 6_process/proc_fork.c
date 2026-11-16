/*
파일 이름: proc_fork.c
설명: 프로세스 생성 (fork)
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        printf("[자식] PID = %d, 부모 PID = %d\n", getpid(), getppid());
    } else {
        printf("[부모] PID = %d, 자식 PID = %d\n", getpid(), pid);
        sleep(1);      
    }
    return 0;
}
