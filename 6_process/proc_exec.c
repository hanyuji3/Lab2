/*
파일 이름: proc_exec.c
설명: 다른 프로그램 실행 (fork, execlp, wait)
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid;

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }
    if (pid == 0) {
        printf("[자식] ls -l 을 실행합니다.\n");
        execlp("ls", "ls", "-l", NULL);
        perror("execlp");    
        exit(1);
    }
    wait(NULL);
    printf("[부모] 자식이 끝났습니다.\n");
    return 0;
}
