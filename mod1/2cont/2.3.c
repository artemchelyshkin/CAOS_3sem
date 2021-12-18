#include <stdint.h>
#include <stdio.h>

enum constants { digits = 10, digits_and_upper = 36, digits_upper_lower = 62 };

void print(uint64_t arr)
{
    uint64_t one = 1;
    for (int i = 0; i < digits; ++i) {
        if ((arr & (one << i)) != 0) {
            char ch = '0' + i;
            printf("%c", ch);
        }
    }
    for (int i = digits; i < digits_and_upper; ++i) {
        if (arr & (one << i)) {
            char ch = 'A' + i - digits;
            printf("%c", ch);
        }
    }
    for (int i = digits_and_upper; i < digits_upper_lower; ++i) {
        if (arr & (one << i)) {
            char ch = 'a' + i - digits_and_upper;
            printf("%c", ch);
        }
    }
}

int main()
{
    uint64_t arr = 0;
    uint64_t curr_arr = 0;
    char elem;
    uint64_t one = 1;
    while ((elem = getchar()) != EOF) {
        if ((elem >= '0') && (elem <= '9')) {
            curr_arr = (curr_arr | (one << (elem - '0')));
        }
        if ((elem >= 'A') && (elem <= 'Z')) {
            curr_arr = (curr_arr | (one << (elem - 'A' + digits)));
        }
        if ((elem >= 'a') && (elem <= 'z')) {
            curr_arr = (curr_arr | (one << (elem - 'a' + digits_and_upper)));
        }
        if (elem == '&') {
            arr = arr & curr_arr;
            curr_arr = 0;
        }
        if (elem == '|') {
            arr = arr | curr_arr;
            curr_arr = 0;
        }
        if (elem == '^') {
            arr = arr ^ curr_arr;
            curr_arr = 0;
        }
        if (elem == '~') {
            arr = ~arr;
        }
    }
    print(arr);
}
