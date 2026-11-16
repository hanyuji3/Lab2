/*
파일 이름: ls_r.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

void list_dir(char *path)
{
    struct dirent **list;
    struct stat st;
    char full[1024];
    int n, i;

    n = scandir(path, &list, NULL, alphasort);
    if (n < 0) {
        perror(path);
        return;
    }

    printf("%s:\n", path);
    for (i = 0; i < n; i++) {
        if (list[i]->d_name[0] != '.')
            printf("%s\n", list[i]->d_name);
    }

    for (i = 0; i < n; i++) {
        if (list[i]->d_name[0] == '.')
            continue;
        snprintf(full, sizeof(full), "%s/%s", path, list[i]->d_name);
        if (lstat(full, &st) == 0 && S_ISDIR(st.st_mode)) {
            printf("\n");
            list_dir(full);
        }
    }

    for (i = 0; i < n; i++)
        free(list[i]);
    free(list);
}

int main(int argc, char *argv[])
{
    char *start = ".";

    if (argc >= 2)
        start = argv[1];
    list_dir(start);
    return 0;
}
