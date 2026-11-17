/*
파일 이름: pipe_chat.c
설명: FIFO(이름 있는 파이프) 2개를 이용한 텍스트 채팅
      (mkfifo, open, read, write, fork)
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    char *wname, *rname;       
    int wfd, rfd, n;
    pid_t pid;
    char buf[100];

    if (argc != 2 || (strcmp(argv[1], "1") != 0 && strcmp(argv[1], "2") != 0)) {
        printf("사용법: %s [1 또는 2]\n", argv[0]);
        return 1;
    }
    if (strcmp(argv[1], "1") == 0) {
        wname = "fifo1";
        rname = "fifo2";
    } else {
        wname = "fifo2";
        rname = "fifo1";
    }

    if (mkfifo("fifo1", 0666) == -1 && errno != EEXIST) {
        perror("mkfifo fifo1");
        exit(1);
    }
    if (mkfifo("fifo2", 0666) == -1 && errno != EEXIST) {
        perror("mkfifo fifo2");
        exit(1);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        rfd = open(rname, O_RDONLY);
        if (rfd == -1) {
            perror("open read");
            exit(1);
        }
        while ((n = read(rfd, buf, sizeof(buf) - 1)) > 0) {
            buf[n] = '\0';
            if (strcmp(buf, "exit") == 0)
                break;
            printf("\r상대방> %s\n나> ", buf);
            fflush(stdout);
        }
        printf("\n상대방이 나갔습니다.\n");
        kill(getppid(), SIGTERM);              
        exit(0);
    }

    printf("상대방을 기다리는 중입니다...\n");
    wfd = open(wname, O_WRONLY);
    if (wfd == -1) {
        perror("open write");
        exit(1);
    }
    printf("채팅을 시작합니다. 종료하려면 'exit'을 입력하세요.\n");

    while (1) {
        printf("나> ");
        fflush(stdout);
        if (fgets(buf, sizeof(buf), stdin) == NULL)
            break;
        buf[strcspn(buf, "\n")] = '\0';      
        if (strlen(buf) == 0)
            continue;
        write(wfd, buf, strlen(buf));
        if (strcmp(buf, "exit") == 0)
            break;
    }

    kill(pid, SIGTERM);                       
    wait(NULL);
    close(wfd);
    printf("채팅을 종료합니다.\n");
    return 0;
}
