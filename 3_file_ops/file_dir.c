/*
파일 이름: file_dir.c
설명: 디렉토리 내용 보기 (opendir, readdir, closedir)
*/
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char *argv[])
{
    DIR *dp;
    struct dirent *ent;

    if (argc < 2) {
        fprintf(stderr, "사용법: file_dir 디렉토리이름\n");
        exit(1);
    }
    dp = opendir(argv[1]);
    if (dp == NULL) {
        perror("opendir");
        exit(1);
    }
    while ((ent = readdir(dp)) != NULL)
        printf("%s\n", ent->d_name);
    closedir(dp);
    return 0;
}
