#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

const int expression_lenght = 4096;

int main()
{
    char expr[expression_lenght + 4];
    int fd = open("expression.c", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    write(fd, "#include<stdio.h>\nint main(){printf(\"%d\",(int)(", 47);
    fgets(expr, expression_lenght, stdin);
    size_t lenght = 0;
    for (; expr[lenght] != '\0'; lenght++) {}
    expr[lenght] = ')';
    expr[lenght + 1] = ')';
    expr[lenght + 2] = ';';
    expr[lenght + 3] = '}';
    write(fd, expr, lenght + 4);
    close(fd);
    pid_t pid = fork();
    if (pid == 0) {
        execlp("gcc", "gcc", "expression.c", "-o", "expression", NULL);
    } else {
        int status;
        waitpid(pid, &status, 0);
        execlp("./expression", "./expression", NULL);
    }
    return 0;
}
