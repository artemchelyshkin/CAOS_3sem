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

void mul(ITYPE first, ITYPE second, ITYPE* res, int* CF)
{
    *res = 0;
    *CF = 0;
    ITYPE max_deg = 0;
    for (ITYPE i = 0; i < sizeof(ITYPE); ++i) {
        if (first & (1 << i)) {
            max_deg = i;
        }
    }
    for (ITYPE i = 0; i < sizeof(ITYPE); ++i) {
        ITYPE a = 0;
        if (second & (1 << i)) {
            a = first << i;
            ITYPE degree = 0;
            int tmp = 0;
            sum(i, max_deg, &degree, &tmp);
            if (degree >= sizeof(ITYPE)) {
                *CF = 1;
            }
        }
        int tmp_CF = 0;
        sum(*res, a, res, &tmp_CF);
        if (tmp_CF) {
            *CF = 1;
        }
    }
}
