#include <stdio.h>
#include <math.h>
#include "sieve.h"
#include "bv.h"

//This is the Sieve of Eratosthenes. It is provided in the assignment - 1 lab manual for CS - 12B.
//The credit for providing the code goes to Professor Darrell Don Earl Long from UCSC.
void sieve(bitV *bitVector)
{
    one(bitVector);    // Assume all are prime.
    clrBit(bitVector, 0);    // 0 is, well, zero.
    clrBit(bitVector, 1);    // 1 is unity.
    setBit(bitVector, 2);    // 2 is prime.
    for (uint32_t i = 2; i <= sqrtl(lenVec(bitVector)); i += 1)
    {
        if (valBit(bitVector, i))    // It's prime.
        {
            for (uint32_t k = 0; (k + i) * i <= lenVec(bitVector); k += 1)
            {
                clrBit(bitVector, (k + i) * i);   // Its multiple are composite.
            }
        }
    }
    return;
}
