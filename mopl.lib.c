#include "mopl.lib.h"
MNumber MInit(uint64_t integerFigures, uint64_t decimalFigures, bool positive)
{
    MNumber a;

    if (MOPL_ALLOC_INT < integerFigures || MOPL_ALLOC_DEC < decimalFigures)
    {
        a.error = true;
        return a;
    }
    a.integerFigures = integerFigures;
    a.decimalFigures = decimalFigures;
    for (int i = 0; i < a.integerFigures; i++)
    {
        a.mantissaInt[0] = '0';
    }
    for (int i = 0; i < a.decimalFigures; i++)
    {
        a.mantissaDec[0] = '0';
    }
    a.positive = positive;
    a.error = false;
    return a;
}

int c2i(char c)
{
     switch((int) c){  
        case '0':
            return 0;  
        case '1':
            return 1;  
        case '2':
            return 2;  
        case '3':
            return 3;  
        case '4':
            return 4;  
        case '5':
            return 5;  
        case '6':
            return 6;  
        case '7':
            return 7;  
        case '8':
            return 8;  
        case '9':
            return 9;
     }
     return 0;
}

char i2c(int i)
{
     switch(i){  
        case 0:
            return '0';  
        case 1:
            return '1';  
        case 2:
            return '2';  
        case 3:
            return '3';  
        case 4:
            return '4';  
        case 5:
            return '5';  
        case 6:
            return '6';  
        case 7:
            return '7';  
        case 8:
            return '8';  
        case 9:
            return '9';
     }
     return '0';
}

MNumber MAdd(MNumber a, MNumber b)
{
    int ia, ib, icarry, da, db, dcarry;
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
    int iSizeDiff = imax.integerFigures - imin.integerFigures;
    c.integerFigures = imax.integerFigures;
    c.decimalFigures = dmax.decimalFigures;
    int sum = 0;
    for (int i = 0; i < imax.integerFigures; i++)
    {
        if (i < iSizeDiff)
        {
            c.mantissaInt[imax.integerFigures - i] = imax.mantissaInt[imax.integerFigures - i];
        }
        else
        {
            sum = i2c(imax.mantissaInt[imax.integerFigures - i]) + i2c(imin.mantissaInt[imin.integerFigures - i + iSizeDiff]);
            c.integerFigures[imax.integerFigures - i] = sum % 10;
            if (sum > 10)
            {
                icarry = sum - 10;
            }
        }
        ia = c2i(a.mantissaInt[indexA]);
        ib = c2i(b.mantissaInt[indexB]);
    }
}
MNumber MAbsolute(MNumber a)
{
    a.positive = true;
    return a;
}
