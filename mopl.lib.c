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
    for (int i = 0; i < MOPL_ALLOC_INT; i++)
    {
        a.mantissaInt[0] = '0';
    }
    for (int i = 0; i < MOPL_ALLOC_DEC; i++)
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
    int sum = 0, ci, tis, ia, ib;
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
            ia = c2i(a.mantissaInt[ci]);
            ib = c2i(b.mantissaInt[ci]);
            if(!ia.positive) ia*=-1;
            if(!ib.positive) ib*=-1;
            sum = ia + ib + icarry;
            c.integerFigures[ci] = i2c(sum % 10);
            if (sum > 10)
            {
                icarry = sum - 10;
            }
            else if(sum < 0){
                icarry = sum + 10;
            }
        }
    }
    if (icarry) c.error = true;
    return c;
}
MNumber MSubtract(MNumber a, MNumber b){
    b.positive = !positive;
    return MNAdd(a,b);
}
MNumber MAbsolute(MNumber a)
{
    a.positive = true;
    return a;
}
int MCompare(MNumber a, MNumber b) {
     if(a.positive != b.positive)
          if(a.positive) return 1;
          return -1;
     }
     for(int i = 0; i < MOPL_ALLOC_INT; i++){
         if(a.integerFigures < MOPL_ALLOC_INT - i && b.integerFigures >=  MOPL_ALLOC_INT - i && c2i(b.mantissaInt[i]) != 0){
             if(b.positive) return -1;
             return 1;
         }
         if(b.integerFigues < MOPL_ALLOC_INT && a.integerFigures >= MOPL_ALLOC_INT - i && c2i(a.mantissaInt[i]) != 0){
            if(a.positive) return 1;
            return -1;
         }
         if(c2i(a.mantissaInt[i]) < c2i(b.mantissaInt[i])){
             if(a.positive) return -1;
             return 1;
         }
         if(c2i(a.mantissaInt[i]) > c2i(b.mantissaInt[i])){
             if(a.positive) return 1;
            return -1;
         }
    }
    for(int i = 0; i < MOPL_ALLOC_DEC; i++){
        if(c2i(a.mantissaDec[i]) < c2i(b.mantissaDec[i])){
            if(a.positive)  return -1;
            return 1;
        }
        if(c2i(a.mantissaDec[i]) > c2i(b.mantissaDec[i])){
            if(a.positive) return 1;
            return -1;
        }
    }
    return 0;
}
