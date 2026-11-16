
/*
파일 이름: typing.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#define MAX_LINES 100
#define COUNT 5

int char_len(char *p)
{
    unsigned char c = *p;
    int len;

    if (c < 0x80)
        len = 1;
    else if ((c & 0xE0) == 0xC0)
        len = 2;
    else if ((c & 0xF0) == 0xE0)
        len = 3;
    else
        len = 4;
    if (len > (int)strlen(p))
        len = strlen(p);
    return len;
}

int count_chars(char *s)
{
    int n = 0;

    while (*s != '\0') {
        s += char_len(s);
        n++;
    }
    return n;
}

int main(int argc, char *argv[])
{
    static char lines[MAX_LINES][300];  
    int order[MAX_LINES];               
    char input[300];
    struct timeval start, end;
    double sec;
    double total_sec = 0;
    int total_chars = 0;
    int total_wrong = 0;
    int n = 0;
    int total, i, j, tmp, la, lb, wrong;
    char *a;
    char *b;
    FILE *fp;

    if (argc < 2) {
        fprintf(stderr, "사용법: typing 문장파일\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("fopen");
        return 1;
    }

    while (n < MAX_LINES && fgets(lines[n], sizeof(lines[n]), fp) != NULL) {
        lines[n][strcspn(lines[n], "\r\n")] = '\0';
        if (lines[n][0] != '\0')
            n++;
    }
    fclose(fp);
    if (n == 0) {
        fprintf(stderr, "문장이 없습니다.\n");
        return 1;
    }

    srand(time(NULL));
    for (i = 0; i < n; i++)
        order[i] = i;
    for (i = n - 1; i > 0; i--) {
        j = rand() % (i + 1);
        tmp = order[i];
        order[i] = order[j];
        order[j] = tmp;
    }
    total = (n < COUNT) ? n : COUNT;

    printf("=== 한글 타자 연습 ===\n");
    printf("문장을 그대로 입력하고 엔터를 누르세요.\n\n");

    for (i = 0; i < total; i++) {
        a = lines[order[i]];
        printf("[%d/%d] %s\n", i + 1, total, a);
        printf("      ");

        gettimeofday(&start, NULL);            
        if (fgets(input, sizeof(input), stdin) == NULL)
            break;
        gettimeofday(&end, NULL);               
        input[strcspn(input, "\n")] = '\0';     

        sec = (end.tv_sec - start.tv_sec)
            + (end.tv_usec - start.tv_usec) / 1000000.0;
        total_sec += sec;

        b = input;
        wrong = 0;
        while (*a != '\0' || *b != '\0') {
            la = (*a != '\0') ? char_len(a) : 0;
            lb = (*b != '\0') ? char_len(b) : 0;
            if (la != lb || strncmp(a, b, la) != 0)
                wrong++;
            a += la;
            b += lb;
        }
        total_wrong += wrong;
        total_chars += count_chars(input);
        printf("      틀린 글자: %d개\n\n", wrong);
    }

    printf("=== 결과 ===\n");
    printf("걸린 시간: %.1f초\n", total_sec);
    printf("입력한 글자 수: %d자\n", total_chars);
    printf("틀린 횟수: %d개\n", total_wrong);
    if (total_sec > 0)
        printf("평균 분당 타자수: %.0f자/분\n", total_chars * 60 / total_sec);
    return 0;
}
