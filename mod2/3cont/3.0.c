#include <stdint.h>
#include <stdio.h>
#include <sys/stat.h>

int main()
{
    char file_name[4096];
    long int sze = 0;
    struct stat s;
    while (fgets(file_name, 4096, stdin)) {
        uint64_t i = 0;
        for (; file_name[i] != '\n'; ++i) {}
        file_name[i] = '\0';
        if (-1 != lstat(file_name, &s)) {
            if (S_ISREG(s.st_mode)) {
                sze += s.st_size;
            }
        }
    }
    printf("%li", sze);
}
