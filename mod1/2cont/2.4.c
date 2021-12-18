#include <stdio.h>

int main()
{
    char elem;
    int ascii_readable = 0;
    int ascii_unreadable = 0;
    while ((elem = getchar()) != EOF) {
        if ((elem & (1 << 7)) == 0) {
            ascii_readable++;
        } else {
            ascii_unreadable++;
            int num_of_bytes = 0;
            while (elem & (1 << (7 - num_of_bytes))) {
                num_of_bytes++;
            }
            for (int i = 1; i < num_of_bytes; ++i) {
                elem = getchar();
                if (elem == EOF) {
                    return 1;
                }
                if ((elem & (1 << 7)) == 0 || (elem & (1 << 6)) != 0) {
                    return 1;
                }
            }
        }
    }
    printf("%d %d", ascii_readable, ascii_unreadable);
}
