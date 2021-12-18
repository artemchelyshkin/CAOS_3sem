#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    pid_t pid;
    pid = fork();
    if (pid == 0) {
        while ((pid = fork()) >= 0) {
            if (pid > 0) {
                int status;
                waitpid(pid, &status, 0);
                int32_t res = WEXITSTATUS(status);
                return res + 1;
            }
        }
    }
    int status;
    waitpid(pid, &status, 0);
    printf("%d", WEXITSTATUS(status) + 1);
    return 0;
}
