/*
파일 이름: sig_kill.c
설명: 프로세스에 시그널 보내기 (kill, SIGUSR1)
*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

volatile sig_atomic_t got = 0;

void handler(int sig)
{
    got = 1;
}

int main(void)
{
    pid_t pid;
    struct sigaction act;

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        act.sa_handler = handler;
        sigemptyset(&act.sa_mask);
        act.sa_flags = 0;
        sigaction(SIGUSR1, &act, NULL);

        printf("[자식] 시그널을 기다립니다. (PID = %d)\n", getpid());
        while (got == 0)
            sleep(1);
        printf("[자식] SIGUSR1 을 받았습니다.\n");
        exit(0);
    }
    sleep(1);
    printf("[부모] 자식에게 SIGUSR1 을 보냅니다.\n");
    kill(pid, SIGUSR1);
    wait(NULL);
    printf("[부모] 자식이 끝났습니다.\n");
    return 0;
}
