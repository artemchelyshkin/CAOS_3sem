#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

const int BUF_MAX = 4096;

void get_name(char* init_name, char* res)
{
    char* finish = init_name + strlen(init_name);
    while (*finish != '/' && finish != (init_name - 1)) {
        finish--;
    }
    finish++;
    snprintf(res, BUF_MAX, "link_to_");
    uint64_t i = 8;
    while (*finish != '\0') {
        res[i] = *finish;
        ++i, ++finish;
    }
    res[i] = '\0';
    return;
}

int main()
{
    char file_name[BUF_MAX];
    struct stat s;
    while (fgets(file_name, BUF_MAX, stdin)) {
        uint64_t i = 0;
        for (; file_name[i] != '\n'; ++i) {}
        file_name[i] = '\0';
        lstat(file_name, &s);
        if (S_ISREG(s.st_mode)) {
            char res[BUF_MAX];
            get_name(file_name, res);
            symlink(file_name, res);
            continue;
        }
        if (S_ISLNK(s.st_mode)) {
            char buf[BUF_MAX];
            memset(buf, '\0', BUF_MAX);
            realpath(file_name, buf);
            printf("%s\n", buf);
        }
    }
}
