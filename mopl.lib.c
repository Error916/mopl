#include "mopl.lib.h"

MNumber MInit(uint64_t integerFigures, uint64_t decimalFigures, uint8_t positive)
{
    MNumber a;

    if (MOPL_ALLOC_INT < integerFigures || MOPL_ALLOC_DEC < decimalFigures)
    {
        a.error = 1;
        return a;
    }

    memset(a.mantissaInt, 0, MOPL_ALLOC_INT);
    memset(a.mantissaDec, 0, MOPL_ALLOC_DEC);

    a.integerFigures = integerFigures;
    a.decimalFigures = decimalFigures;
    a.positive = positive;
    a.error = 0;
    return a;
}

int c2i(char c)
{
    if(c >= '0' && c <= '9')
        return (int) c - 48;

    return 0;
}

char i2c(int i)
{
    if(i >= 0 && i <= 9)
        return (char) i + 48;

    return '0';
}

MNumber MAdd(MNumber a, MNumber b)
{
    int icarry = 0, da, db, dcarry;
    MNumber c, imax, imin, dmax, dmin;
    c.mantissaInt[MOPL_ALLOC_INT];
    c.mantissaDec[MOPL_ALLOC_DEC];
    if (a.integerFigures < b.integerFigures)
    {
        imax = b;
        imin = a;
    }
    else
    {
        imax = a;
        imin = b;
    }
    if (a.decimalFigures < b.decimalFigures)
    {
        dmin = a;
        dmax = b;
    }
    else
    {
        dmin = b;
        dmax = a;
    }
    c.integerFigures = imax.integerFigures;
    c.decimalFigures = dmax.decimalFigures;
    int sum = 0, ci, tis;
    for (int i = 0; i < MOPL_ALLOC_INT; i++)
    {
        ci = MOPL_ALLOC_INT - i;
        if (i > imin.integerFigures)
        {
            tis = c2i(imax.mantissaInt[ci]) + icarry;
            c.mantissaInt[ci] = i2c(tis % 10);
            icarry = tis - 10;
        }
        else
        {
            sum = c2i(imax.mantissaInt[ci]) + c2i(imin.mantissaInt[ci]) + icarry;
            c.mantissaInt[ci] = i2c(sum % 10);
            if (sum > 10)
            {
                icarry = sum - 10;
            }
        }
    }
    if (icarry) c.error = 1;
    return c;
}

MNumber MSubtract(MNumber a, MNumber b){
    b.positive = b.positive ? 0 : 1;
    return MNAdd(a,b);
}

MNumber MAbsolute(MNumber a)
{
    a.positive = 1;
    return a;
}

int MCompare(MNumber a, MNumber b) {
	if(a.positive != b.positive){
		return a.positive ? 1 : -1;
	}

	if(memcmp(a.mantissaInt, b.mantissaInt, MOPL_ALLOC_INT) != 0){
		return a.positive ? 1 : -1;
	}

	if(memcmp(a.mantissaDec, b.mantissaDec, MOPL_ALLOC_DEC) != 0){
		return a.positive ? 1 : -1;
	}

	return 0;
}
