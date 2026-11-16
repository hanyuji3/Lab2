/*
파일 이름: sig_alarm.c
설명: 타이머 시그널 (alarm, SIGALRM)
*/
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t ring = 0;

void handler(int sig)
{
    ring = 1;
}

int main(void)
{
    struct sigaction act;
    int i = 0;

    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGALRM, &act, NULL);

    printf("3초 후 알람이 울립니다.\n");
    alarm(3);                        
    while (ring == 0) {
        printf("%d번째 대기 중...\n", ++i);
        sleep(1);
    }
    printf("알람(SIGALRM)을 받았습니다!\n");
    return 0;
}
