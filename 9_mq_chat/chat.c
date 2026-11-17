/* 파일 이름: chat.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <mqueue.h>

#define SIZE 100

int main(int argc, char *argv[])
{
    mqd_t send_q, recv_q;
    struct mq_attr attr;
    char send_name[50], recv_name[50];
    char line[SIZE], buf[SIZE];

    if (argc != 3) {
        printf("사용법: %s [보낼 번호] [받을 번호]\n", argv[0]);
        exit(1);
    }

    sprintf(send_name, "/chat_%s", argv[1]);
    sprintf(recv_name, "/chat_%s", argv[2]);

    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = SIZE;
    attr.mq_curmsgs = 0;

    send_q = mq_open(send_name, O_CREAT | O_WRONLY, 0666, &attr);
    recv_q = mq_open(recv_name, O_CREAT | O_RDONLY, 0666, &attr);
    if (send_q == (mqd_t)-1 || recv_q == (mqd_t)-1) {
        perror("mq_open");
        exit(1);
    }

    printf("채팅을 시작합니다. 종료하려면 exit를 입력하세요.\n");

    while (1) {
        printf("나> ");
        fflush(stdout);
        if (fgets(line, SIZE, stdin) == NULL)
            break;
        line[strcspn(line, "\r\n")] = '\0';
        if (strlen(line) == 0)
            continue;

        mq_send(send_q, line, strlen(line) + 1, 0);

        if (strcmp(line, "exit") == 0) {
            printf("채팅을 종료합니다.\n");
            break;
        }

        if (mq_receive(recv_q, buf, SIZE, NULL) == -1) {
            perror("mq_receive");
            break;
        }

        if (strcmp(buf, "exit") == 0) {
            printf("상대방이 나갔습니다.\n");
            mq_unlink(send_name);
            mq_unlink(recv_name);
            break;
        }
        printf("상대방> %s\n", buf);
    }

    mq_close(send_q);
    mq_close(recv_q);
    return 0;
}
