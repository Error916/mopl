#ifndef _MOPL_H
#define _MOPL_H

#ifndef MOPL_ALLOC_INT
#define MOPL_ALLOC_INT 100
#endif

#ifndef MOPL_ALLOC_DEC
#define MOPL_ALLOC_DEC 100
#endif

#include <stdint.h>
#include <string.h>
typedef struct MNumber
{
    // The numbers are stored as big endian
    unsigned char mantissaInt[MOPL_ALLOC_INT];
    unsigned char mantissaDec[MOPL_ALLOC_DEC];
    uint64_t integerFigures;
    uint64_t decimalFigures;
    uint8_t positive;
    uint8_t error;
} MNumber;

MNumber MInit(uint64_t integerFigures, uint64_t decimalFigures, uint8_t positive);
MNumber MAdd(MNumber a, MNumber b);
MNumber MNAdd(MNumber a, MNumber b);
MNumber MSubtract(MNumber a, MNumber b);
MNumber MExponent(MNumber a, MNumber b);
MNumber MMultiplicate(MNumber a, MNumber b);
MNumber MDivide(MNumber a, MNumber b);
MNumber MModulo(MNumber a, MNumber b);
MNumber MIntegerDivision(MNumber a, MNumber b);
MNumber MAbsolute(MNumber a);
int MCompare(MNumber a, MNumber b);
int c2i(char c);
char i2c(int i);

#endif
