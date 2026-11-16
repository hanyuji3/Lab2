/*
파일 이름: ipc_pipe.c
설명: 파이프를 이용한 부모 -> 자식 통신 (pipe, fork)
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    int fd[2];
    pid_t pid;
    char buf[100];
    char *msg = "안녕 파이프";
    int n;

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        close(fd[1]);                      
        n = read(fd[0], buf, sizeof(buf) - 1);
        if (n == -1) {
            perror("read");
            exit(1);
        }
        buf[n] = '\0';
        printf("[자식] 받은 메시지: %s\n", buf);
        close(fd[0]);
        exit(0);
    }

    close(fd[0]);                      
    write(fd[1], msg, strlen(msg));
    printf("[부모] 메시지를 보냈습니다.\n");
    close(fd[1]);
    wait(NULL);
    return 0;
}
