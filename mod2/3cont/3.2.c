#include <stdint.h>

void process_double_slash(char* begin, char* end)
{
    for (char* tmp = begin; tmp != end; ++tmp) {
        *tmp = *(tmp + 1);
    }
}

int64_t process_double_dot_slash(char* begin, char* end)
{
    int64_t size_of_word = 4;
    char* tmp = begin - 4;
    while (*tmp != '/') {
        tmp--;
        size_of_word++;
    }
    for (; tmp != end; ++tmp) {
        *tmp = *(tmp + size_of_word);
    }
    return size_of_word;
}

void process_dot_slash(char* begin, char* end)
{
    for (char* tmp = begin - 2; tmp != end; ++tmp) {
        *tmp = *(tmp + 2);
    }
}

extern void normalize_path(char* path)
{
    char* tmp = path;
    while (*tmp != '\0') {
        ++tmp;
    }
    char* end = tmp;
    tmp = path;
    tmp++;
    for (; *tmp != '\0'; tmp++) {
        if (*tmp == '/') {
            if (*(tmp - 1) == '/') {
                process_double_slash(tmp, end);
                tmp -= 1, end -= 1;
            } else if (
                *(tmp - 1) == '.' && *(tmp - 2) == '.' && *(tmp - 3) == '/') {
                int64_t size = process_double_dot_slash(tmp, end);
                tmp -= size, end -= size;
            } else if (*(tmp - 1) == '.' && *(tmp - 2) == '/') {
                process_dot_slash(tmp, end);
                tmp -= 2, end -= 2;
            }
        }
    }
}
