#include <stdint.h>

typedef enum {
    PlusZero = 0x00,
    MinusZero = 0x01,
    PlusInf = 0xF0,
    MinusInf = 0xF1,
    PlusRegular = 0x10,
    MinusRegular = 0x11,
    PlusDenormal = 0x20,
    MinusDenormal = 0x21,
    SignalingNaN = 0x30,
    QuietNaN = 0x31
} float_class_t;

float_class_t classify(double* value_ptr)
{
    uint64_t* val = (uint64_t*)((void*)value_ptr);
    uint64_t copy = *val;
    uint64_t M = 0x000FFFFFFFFFFFFF;
    uint64_t E = 0x7FF0000000000000;
    uint64_t S = 0x8000000000000000;
    if ((M & copy) != 0) {
        if ((E & copy) == E) {
            if (S & copy) {
                return QuietNaN;
            } else {
                return SignalingNaN;
            }
        }
        if ((E & copy) == 0) {
            if (S & copy) {
                return MinusDenormal;
            } else {
                return PlusDenormal;
            }
        } else {
            if (S & copy) {
                return MinusRegular;
            } else {
                return PlusRegular;
            }
        }
    } else {
        if ((E & copy) == 0) {
            if (S & copy) {
                return MinusZero;
            } else {
                return PlusZero;
            }
        }
        if ((E & copy) == E) {
            if (S & copy) {
                return MinusInf;
            } else {
                return PlusInf;
            }
        } else {
            if (S & copy) {
                return MinusRegular;
            } else {
                return PlusRegular;
            }
        }
    }
}
