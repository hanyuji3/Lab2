/*
파일 이름: sig_handler.c
설명: 시그널 처리 (sigaction, SIGINT)
*/
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t count = 0;

void handler(int sig)
{
    char *msg = "\nCtrl-C 를 눌렀습니다.\n";

    count++;
    write(1, msg, strlen(msg));
}

int main(void)
{
    struct sigaction act;

    act.sa_handler = handler;    
    sigemptyset(&act.sa_mask);    
    act.sa_flags = 0;
    sigaction(SIGINT, &act, NULL);

    printf("Ctrl-C 를 3번 누르면 종료합니다. (PID = %d)\n", getpid());
    while (count < 3)
        sleep(1);
    printf("3번 눌렀으므로 종료합니다.\n");
    return 0;
}
