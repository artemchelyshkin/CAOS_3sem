#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    pid_t pid;
    char string[4096];
    int32_t res = 0;
    pid = fork();
    if (pid == 0) {
        int elem = 0;
        int lenght = scanf("%s", string);
        if (lenght <= 0) {
            return 0;
        }
        while ((pid = fork()) == 0) {
            int lenght = scanf("%s", string);
            if (lenght <= 0) {
                return 0;
            }
        }
        int status;
        waitpid(pid, &status, 0);
        int32_t res = WEXITSTATUS(status);
        return res + 1;
    }
    int status;
    waitpid(pid, &status, 0);
    res = WEXITSTATUS(status);
    printf("%d\n", res);
    return 0;
}
