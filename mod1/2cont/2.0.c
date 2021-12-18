#include <stdint.h>

void sum(ITYPE first, ITYPE second, ITYPE* res, int* CF)
{
    ITYPE doz = 0;
    *res = 0;
    *CF = 0;
    for (ITYPE i = 0; i < sizeof(ITYPE); ++i) {
        ITYPE a = (first & (1 << i));
        ITYPE b = (second & (1 << i));
        ITYPE tmp = a ^ b ^ doz;
        if ((doz && a) || (doz && b) || (a && b)) {
            doz = 1 << (i + 1);
            *CF = 1;
        } else {
            *CF = 0;
            doz = 0;
        }
        *res = *res | tmp;
        if ((i == sizeof(ITYPE) - 1) && (doz != 0)) {
            *CF = 1;
        }
    }
}
