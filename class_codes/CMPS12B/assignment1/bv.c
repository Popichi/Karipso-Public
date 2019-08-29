/*#############################################
# Anil Celik Maral - amaral
# amaral@ucsc.edu
# 1454995
# Assignment - 1
# Lab: Friday, 9:00am - 10:00am
# Lab Partner: None
# Date: 04/22/17
###############################################
*/

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "bv.h"

//Important Note: I used the examples on piazza and classes to tackle the conceptual part of the
//coding. For example, I used the code in example 19, which Professor Darrell Long provided, to
//learn the concepts and algorithms behind manipulating bits in a bit vector. However, all of the
//coding is my own work.

//This function takes the length of the bit vector as uint32_t. This number represent the number
//of bits that we want to have. The function allocates memory space for the bit vector and sets
//the length of the bit vector to the input. If the function is able to allocate enough space
//for the given vector. The pointer to the beginning of the bit vector is saved in the struct
//and the pointer to the struct is returned.
//@param The number of bits for the bit vector.
//@return The pointer to the struct that has to pointer to the bit vector.
bitV *newVec(uint32_t vectorLength)
{
    uint8_t successFlag = false;
    bitV *bitVector = NULL;
    bitVector = malloc(sizeof(bitV));
    if (bitVector != NULL) {
        bitVector -> v = (uint8_t*)calloc((vectorLength / 8) + 1, sizeof(uint8_t));
        bitVector -> l = vectorLength;
        successFlag = true;
    }
    if (successFlag == true) {
        return bitVector;
    } else {    //successFlag != true
        return NULL;
    }		
}

//This function takes the pointer to the struct that holds the length of the bit vector and the
//pointer to the bit vector itself. Firstly, the bit vector is freed and the pointer is changed
//to NULL. Secondly, the struct itself is freed and the pointer is changed to NULL. This function
//is used to prevent memory leaks.
//@param The pointer to the struct that has to pointer to the bit vector.
//@return void.
void delVec(bitV* bitVector)
{
    free(bitVector -> v);
    bitVector -> v = NULL;
    free(bitVector);
    bitVector = NULL;
    return;
}

//This function makes all of the bits 1. In another words, the bit vector is initialized to all
//ones. The entire length is parsed using the bytes.
//@param The pointer to the struct that has to pointer to the bit vector.
//@return void.
void one(bitV* bitVector)
{
    for (uint32_t i = 0; i <= (((bitVector -> l) / 8) + 1); i++) {
        bitVector -> v[i] |= 0xFF;
    }
    return;
}

//This function sets the desired position of the bit vector to one. This is done by choosing the
//correct number(position) of byte given the position of the bit.
//@param The pointer to the struct that has to pointer to the bit vector.
//@param The position of the bit that will be set to 1.
//@return void.
void setBit(bitV* bitVector, uint32_t desiredBit)
{
    bitVector -> v[(desiredBit / 8)] |= (0x01 << (desiredBit % 8));
    return;
}

//This function sets, which is also known as clearing the bit, the desired position of the bit 
//vector to zero. This is done by choosing the correct number(position) of byte given the position
//of the bit.
//@param The pointer to the struct that has to pointer to the bit vector.
//@param The position of the bit that will be set to 0.
//@return void.
void clrBit(bitV* bitVector, uint32_t desiredBit)
{
    bitVector -> v[(desiredBit / 8)] &= ~(0x01 << (desiredBit % 8));
    return;
}

//This function gets the value of the bit at the desired position of the bit vector. This is done
//by choosing the correct number(position) of byte given the position of the bit.
//@param The pointer to the struct that has to pointer to the bit vector.
//@param The position of the bit that the function gets the value of.
//@return The binary value of the bit.
uint8_t valBit(bitV* bitVector, uint32_t desiredBit)
{
    return (((bitVector -> v[(desiredBit / 8)]) & (0x01 << (desiredBit % 8))) >>
    (desiredBit % 8));
}

//This function gets the length of the bit vector, which is represented in terms of bits.
//@param The pointer to the struct that has to pointer to the bit vector.
//@return The length of the bit vector in terms of bits.
uint32_t lenVec(bitV* bitVector)
{
    return bitVector -> l;
}
