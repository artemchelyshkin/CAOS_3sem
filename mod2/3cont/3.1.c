#include <stdint.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
    char file_name[4096];
    struct stat s;
    while (fgets(file_name, 4096, stdin)) {
        uint64_t i = 0;
        for (; file_name[i] != '\n'; ++i) {}
        file_name[i] = '\0';
        if (access(file_name, X_OK) == 0 && access(file_name, F_OK) == 0) {
            FILE* fl = fopen(file_name, "r");
            char interpr[4096];
            char new_fl[4096];
            fgets(interpr, 4096, fl);
            uint64_t i = 0;
            if (interpr[0] == 0x7f && interpr[1] == 'E' && interpr[2] == 'L' &&
                interpr[3] == 'F') {
                fclose(fl);
                continue;
            }
            while (interpr[i] == ' ') {
                ++i;
            }
            if (interpr[i] != '#') {
                printf("%s", file_name);
                fclose(fl);
                continue;
            }
            ++i;
            while (interpr[i] == ' ') {
                ++i;
            }
            if (interpr[i] != '!') {
                printf("%s", file_name);
                fclose(fl);
                continue;
            }
            ++i;
            while (interpr[i] == ' ') {
                ++i;
            }
            int64_t start = i;
            while (interpr[i] != '\n' && interpr[i] != ' ') {
                new_fl[i - start] = interpr[i];
                ++i;
            }
            new_fl[i - start] = '\0';
            if (access(new_fl, F_OK) != 0) {
                printf("%s", file_name);
                fclose(fl);
                continue;
            }
            if (access(new_fl, X_OK) != 0) {
                printf("%s", file_name);
                fclose(fl);
                continue;
            }
        }
    }
}
