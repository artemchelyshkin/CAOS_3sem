#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int N = atoi(argv[1]);
    pid_t pid;
    pid = fork();
    if (pid == 0) {
        N--;
        while ((pid = fork()) >= 0 && (N >= 1)) {
            if (pid > 0) {
                int status;
                waitpid(pid, &status, 0);
                int32_t res = WEXITSTATUS(status);
                printf("%d ", res + 1);
                return res + 1;
            }
            N--;
        }
        return 0;
    }
    int status;
    waitpid(pid, &status, 0);
    int32_t res = WEXITSTATUS(status);
    printf("%d\n", res + 1);
    return 0;
}
