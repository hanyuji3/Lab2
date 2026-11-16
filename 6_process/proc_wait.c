/*
파일 이름: proc_wait.c
설명: 자식 프로세스 종료 기다리기 (fork, wait, exit)
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        printf("[자식] 2초 후 종료합니다.\n");
        sleep(2);
        exit(3);             
    }

    printf("[부모] 자식(%d)을 기다립니다.\n", pid);
    wait(&status);             
    if (WIFEXITED(status))
        printf("[부모] 자식 종료 상태 = %d\n", WEXITSTATUS(status));
    return 0;
}
