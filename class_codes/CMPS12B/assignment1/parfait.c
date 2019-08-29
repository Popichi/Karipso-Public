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

#include <stdio.h>
#include <stdbool.h>
#include "bv.h"
#include "sieve.h"

int main(void)
{
    uint8_t desiredBit = 11;    //This variable is used to check the value of the bit at a certain
                                //position in the bit vector. Eleven is used to differentiate the
                                //value from '0' and '1' in case of an error.
    uint8_t desiredBitTwo = 12;    //Variable is used to check the value of the bit at a certain
                                   //position in the bit vector. Twelve is used to differentiate the
                                   //value from '0' and '1' in case of an error.
    uint32_t desiredLength = 100000;              //This represent the length, the number of bits,
                                                  //for the bit vector. Therefore, it represents
                                                  //the biggest number in the list.
    uint64_t theDivisorListForComposites[200];    //This array contains the prime divisors that
                                                  //will be printed for composite numbers.
    uint64_t theDivisorListForPerfects[200];      //This array contains the divisors that will be
                                                  //printed for perfect numbers.
    bitV *bitVector = NULL;
    bitVector = newVec(desiredLength);    //The bit vector is created.
    if (bitVector != NULL) {              //If the vector is successfully created!
        sieve(bitVector);                 //This algorithm finds the prime numbers.
        //All the values are checked to determine which are composite, rarely perfect, and which
        //are prime given the lenght(the range of the numbers) of the bit vector by the code below.
        for (uint32_t i = 2; i <= lenVec(bitVector); i++) {
            desiredBit = valBit(bitVector, i);
            if (desiredBit == 0x01) {    //If the number is prime then no further action is needed
                                         //other than printing the number and stating it is prime.
                printf("\n%u P", i);
            } else { //if(desiredBit != 0x01) or if the number is composite, we check if it is also
                     //perfect or not. If it is perfect, both the prime divisors and all other
                     //divisors are printed.
                uint8_t numberIsPerfect = false;    //Assume that the number is not perfect.
                uint16_t numberOfDivisors = 0;      //This variable is used to determine how many
                                                    //elements will be printed from the divisors
                                                    //array.
                uint16_t numberOfPrimeDivisors = 0;
                uint32_t arrayCounter = 1;
                uint32_t j = 2;    //Start checking for divisors from 2.
                theDivisorListForPerfects[0] = 1;    //1 divides everything so no need to check.
                while (j <= (i / 2)) {    //No numbers expect the number itself can divide after
                                          //the half value of the checked number.
                    if (i % j == 0) {    //Remainder = 0;
                        if (theDivisorListForPerfects[arrayCounter - 1] != j) {    //Save only the
                                                                                   //distinct
                                                                                   //divisors.
                            theDivisorListForPerfects[arrayCounter] = j;
                            ++numberOfDivisors;
                        }
                        ++arrayCounter;
                    }
                    ++j;    //Go to next number to check to see if it is a divisor.
                }
                uint64_t sumOfDivisors = theDivisorListForPerfects[0]; //1 is always included as a
                                                                       //divisor.
                for (uint32_t j = 1; j <= numberOfDivisors; j++) {    //Add up all the divisors.
                    sumOfDivisors += theDivisorListForPerfects[j];
                }
                if (sumOfDivisors == i) {    //If the sum of divisors is equal to the number then
                                             //the number is a perfect number.
                    numberIsPerfect = true;
				}
                if (1) {    //This step is always executed.
                    uint32_t arrayCounter = 0;
                    uint32_t j = 2;
                    uint32_t theFactorizedNumber = i;    //For prime factorization, we need the
                                                         //Quotient.
                    printf("\n%u C: ", i);
                    while (j <= (i / 2)) {
                        //We don't care when the quotient is smaller than 2 so we skip.
                        if (theFactorizedNumber % j == 0 && theFactorizedNumber > 1) {
                            desiredBitTwo = valBit(bitVector, j);
                            if (desiredBitTwo == 0x01) {    //We only need the prime divisors.
                                theDivisorListForComposites[arrayCounter] = j;
                                theFactorizedNumber = (theFactorizedNumber / j);    //Get the
                                                                                    //quotient.
                                printf("%u ", j);    //Print the prime divisor.
                                ++numberOfPrimeDivisors;
                                ++arrayCounter;
                            }
                        } else {
                            ++j;
                        }
                    }
                }
                if (numberIsPerfect == true) {    //If the number was perfect, then print all of
                                                  //its divisors.
                    printf("\n%u E: ", i);    //E stands for perfect numbers.
                    for (uint32_t j = 0; j <= numberOfDivisors; j++) {
                    printf("%lu ", theDivisorListForPerfects[j]);
                    }
                }
            }
        }
    } else {
        printf("Bit vector couldn't be created!");
    }
    delVec(bitVector);
    ++theDivisorListForComposites[0];    //Just to get rid of the not used warning.
    return 0;
}
