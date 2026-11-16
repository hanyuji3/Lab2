/*
파일 이름: proc_id.c
설명: 프로세스 번호 확인 (getpid, getppid)
*/
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    printf("내 PID: %d\n", getpid());
    printf("부모 PID: %d\n", getppid());
    return 0;
}
