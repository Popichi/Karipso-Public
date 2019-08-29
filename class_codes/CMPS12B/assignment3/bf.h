# ifndef NIL
# define NIL (void *) 0
# endif
# ifndef _BF_H
# define _BF_H
# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include "aes.h"
# include "statistics.h"

typedef struct bloomF {
    uint8_t *v; // Vector
    uint32_t l; // Length
    uint32_t s[4]; // Salt
} bloomF;

// NOTE: This is the only header file that is modified as static inline functions required us to
// write the code here.

/*#############################################
# Anil Celik Maral - amaral
# amaral@ucsc.edu
# 1454995
# Assignment - 3
# Lab: Friday, 9:00am - 10:00am
# Lab Partner: None
# Date: 05/14/17
###############################################
*/

// Each function has its own has function, determined by the salt.

uint32_t hashBF(bloomF *, char *);

// Create a new Bloom Filter of a given length and hash function.

static inline bloomF *newBF(uint32_t l, uint32_t b[])
{
    uint8_t successFlag = false;
    bloomF *bloomFilter = NIL;
    bloomFilter = malloc(sizeof(bloomF));
    if (bloomFilter != NIL)
    {
        bloomFilter->v = (uint8_t*)calloc((l / 8) + 1, sizeof(uint8_t));
        if (bloomFilter->v != NIL)
        {
            bloomFilter->l = l;
            for (uint8_t i = 0; i < 4; i++)
            {
                bloomFilter->s[i] = b[i]; // Get the salt.
            }
            successFlag = true;
        }
        else
        {
            free(bloomFilter);
        }
    }
    if (successFlag == true) 
    {
        return bloomFilter;
    }
    else 
    {   // successFlag != true
        return NIL;
    }		
}

// Delete a Bloom Filter.

static inline void delBF(bloomF *v)
{
    free(v->v);
    v->v = NIL;
    free(v);
    v = NIL;
    return;
}

// Return the value of position k in the Bloom Filter.

static inline uint32_t valBF(bloomF *x, uint32_t k)
{
    return (((x->v[(k / 8)]) & (0x01 << (k % 8))) >> (k % 8));
}

static inline uint32_t lenBF(bloomF *x) { return x->l; }

// Count bits in the Bloom Filter

static inline uint32_t countBF(bloomF *b)
{
    // It counts the 1 bits.
    uint8_t desiredBit = 10; // It is set to 10 to differentiate from boolean 1 and 0.
    uint32_t numberOfOneBits = 0;
    uint32_t lengthOfTheVector = lenBF(b);
    for (uint32_t i = 0; i < lengthOfTheVector; i++)
    {
        if ((desiredBit = valBF(b, i)) == 1)
        {
            ++numberOfOneBits;
        }
    }
    return numberOfOneBits;
}

// Set an entry in the Bloom Filter.
// Since setBF takes a string (char*) as input, it must call the hash function to find which bit to 
// set.
// Find a bit in the filter the same way you would do it in a bitvector.
static inline void setBF(bloomF *x, char *key)
{
    // Calls the hash function to get the correct bit place. We then use modulo to the return value
    // to get the correct location in our bloom filter. So, the modulo value is the size of our
    // bloom filter.
    uint32_t bloomFilterBitLocation = (hashBF(x, key) % x->l);
    x->v[(bloomFilterBitLocation / 8)] |= (0x01 << (bloomFilterBitLocation % 8));
    return;
}

// Clear an entry in the Bloom Filter

static inline void clrBF(bloomF *x, char *key)
{
    // Calls the hash function to get the correct bit place. We then use modulo to the return value
    // to get the correct location in our bloom filter. So, the modulo value is the size of our
    // bloom filter.
    uint32_t bloomFilterBitLocation = (hashBF(x, key) % x->l);
    x->v[(bloomFilterBitLocation / 8)] &= ~(0x01 << (bloomFilterBitLocation % 8));
    return;
}

// Check membership in the Bloom filter

static inline uint32_t memBF(bloomF *x, char *key)
{
    // Calls the hash function to get the correct bit place. We then use modulo to the return value
    // to get the correct location in our bloom filter. So, the modulo value is the size of our
    // bloom filter.
    uint32_t bloomFilterBitLocation = (hashBF(x, key) % x->l);
    return valBF(x, bloomFilterBitLocation);
}


static inline void printBF(bloomF *x)
{
    // Print the entire bloom filter(A bit vector). It prints the values at each location up to the
    // length of the bloom filter.
    uint32_t lengthOfTheVector = lenBF(x);
    for (uint32_t i = 0; i < lengthOfTheVector; i++)
    {
        printf("%u", valBF(x, i));
    }
    return;
}

# endif