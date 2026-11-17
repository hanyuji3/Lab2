/*
파일 이름: ipc_msg.c
설명: System V 메시지 큐 (msgget, msgsnd, msgrcv, msgctl)
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>

struct my_msg {
    long mtype;          
    char mtext[100];     
};

int main(void)
{
    int id;
    pid_t pid;
    struct my_msg msg;

    id = msgget(IPC_PRIVATE, IPC_CREAT | 0666);    
    if (id == -1) {
        perror("msgget");
        exit(1);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        if (msgrcv(id, &msg, sizeof(msg.mtext), 1, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }
        printf("[자식] 받은 메시지: %s\n", msg.mtext);
        exit(0);
    }

    // 부모: 메시지를 보냄
    msg.mtype = 1;
    strcpy(msg.mtext, "메시지 큐 예제중!");
    if (msgsnd(id, &msg, strlen(msg.mtext) + 1, 0) == -1) {
        perror("msgsnd");
        exit(1);
    }
    printf("[부모] 메시지를 보냈습니다.\n");
    wait(NULL);
    msgctl(id, IPC_RMID, NULL);                  
    printf("[부모] 메시지 큐를 삭제했습니다.\n");
    return 0;
}
