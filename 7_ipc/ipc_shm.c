/*
파일 이름: ipc_shm.c
설명: System V 공유 메모리 (shmget, shmat, shmdt, shmctl)
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

int main(void)
{
    int id;
    char *p;
    pid_t pid;

    id = shmget(IPC_PRIVATE, 1024, IPC_CREAT | 0666);   
    if (id == -1) {
        perror("shmget");
        exit(1);
    }
    p = shmat(id, NULL, 0);                          
    if (p == (char *)-1) {
        perror("shmat");
        exit(1);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        strcpy(p, "공유 메모리 예제중!");
        printf("[자식] 공유 메모리에 썼습니다.\n");
        shmdt(p);
        exit(0);
    }

    wait(NULL);
    printf("[부모] 읽은 내용: %s\n", p);
    shmdt(p);                                        
    shmctl(id, IPC_RMID, NULL);                        
    return 0;
}
