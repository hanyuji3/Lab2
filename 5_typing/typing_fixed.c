/*
파일 이름: typing_fixed.c
*/
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

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

int split(char *s, char *ch[])
{
    int n = 0;

    while (*s != '\0') {
        ch[n++] = s;
        s += char_len(s);
    }
    return n;
}

int same(char *x, char *y)
{
    int lx = char_len(x);
    int ly = char_len(y);

    return lx == ly && strncmp(x, y, lx) == 0;
}

int edit_distance(char *s1, char *s2)
{
    static char *c1[300];
    static char *c2[300];
    static int d[301][301];
    int n1 = split(s1, c1);
    int n2 = split(s2, c2);
    int i, j, cost, min;

    for (i = 0; i <= n1; i++)
        d[i][0] = i;
    for (j = 0; j <= n2; j++)
        d[0][j] = j;
    for (i = 1; i <= n1; i++) {
        for (j = 1; j <= n2; j++) {
            cost = same(c1[i - 1], c2[j - 1]) ? 0 : 1;
            min = d[i - 1][j - 1] + cost;          
            if (d[i - 1][j] + 1 < min)
                min = d[i - 1][j] + 1;               
            if (d[i][j - 1] + 1 < min)
                min = d[i][j - 1] + 1;              
            d[i][j] = min;
        }
    }
    return d[n1][n2];
}

int main(void)
{
    char *text[COUNT] = {
        "리눅스는 무료로 사용할 수 있는 운영체제이다.",
        "프로세스는 실행 중인 프로그램이다.",
        "꾸준히 노력하는 사람은 결국 원하는 결과를 얻는다.",
        "파일을 열 때는 반환값을 확인하여 오류를 검사해야 한다.",
        "작은 실수도 반복해서 확인하면 더 나은 코드를 만들 수 있다."
    };
    char input[300];
    struct timeval start, end;
    double sec;
    double total_sec = 0;
    int total_chars = 0;
    int total_wrong = 0;
    int i, wrong;

    printf("=== 한글 타자 연습 ===\n");
    printf("문장을 그대로 입력하고 엔터를 누르세요.\n\n");

    for (i = 0; i < COUNT; i++) {
        printf("[%d/%d] %s\n", i + 1, COUNT, text[i]);
        printf("      ");

        gettimeofday(&start, NULL);          
        if (fgets(input, sizeof(input), stdin) == NULL)
            break;
        gettimeofday(&end, NULL);            
        input[strcspn(input, "\n")] = '\0';    

        sec = (end.tv_sec - start.tv_sec)
            + (end.tv_usec - start.tv_usec) / 1000000.0;
        total_sec += sec;

        wrong = edit_distance(text[i], input);  
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

