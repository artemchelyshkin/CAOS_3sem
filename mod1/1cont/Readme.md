Problem inf-I-01-0: shell_automation/sh/find_c_includes (1.0)
---
Реализуйте скрипт для командного интерпретатора bash, который выполняет поиск имен #include-файлов для заданных имен Си-функций, используя в качестве источника данных третий раздел man-страниц Linux.

Исходные данные располагаются в одном из каталогов, перечисленных в переменной окружения MANPATH, внутри которых располагается каталог man3.

Файлы могут быть как сжатыми утилитой gz, так и распакованными.

Список функций задается на стандартном потоке ввода:
```
fopen
malloc
unknown_function
strcmp
```
Если описание функции не найдено, то записывается прочерк из трех дефисов: ---.

Результат необходимо записать в стандартный поток вывода:
```
stdio.h
stdlib.h
---
string.h
```
В скрипте допускается использовать только команды ввода-вывода и утилиты sed и gunzip.

Использовать вызов интерпретаторов высокоуровневых языков (Perl, Python и пр.) запрещено.

Problem inf-I-01-1: shell_automation/sh/gauss (1.1)
---
Реализуйте программу для командного интерпретатора bash, которая вычисляет вещественные корни системы линейных алгебраических уравнений методом Гаусса.

Единственным аргументом скрипта является csv-файл c матрицей (N,N+1) вида:
```
2,1,-1,8
-3,-1,2,-11
-2,1,2,-3
```
Скрипт должен вычислить значения и вывести их в тектовом виде на экран в виде строк со значениями:
```
2.00000000000000000000
3.00000000000000000000
-1.00000000000000000000
```
В скрипте допускается использовать только команды ввода-вывода и утилиту bc (для вещественнозначных вычислений).

Использовать вызов интерпретаторов высокоуровневых языков (Perl, Python и пр.) запрещено.
