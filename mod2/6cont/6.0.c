#include <stdio.h>
#include <unistd.h>

const int expression_lenght = 4096;

int main()
{
    char expr[expression_lenght + 7];
    snprintf(expr, expression_lenght + 7, "print(");
    fgets(expr + 6, expression_lenght, stdin);
    size_t lenght = 6;
    for (; expr[lenght] != '\0'; lenght++) {}
    expr[lenght] = ')';
    expr[lenght + 1] = '\0';
    execlp("python", "python", "-c", expr, NULL);
    return 0;
}
