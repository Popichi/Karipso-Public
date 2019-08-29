/*###############################################
# Anil Celik Maral - amaral
# amaral@ucsc.edu
# 1454995
# Assignment - 3
# Lab: Friday, 9:00am - 10:00am
# Lab Partner: None
# Date: 05/14/17
###############################################*/

# include <stdio.h>
# include <ctype.h>
# include <unistd.h> 
# include <string.h>
# include <stdbool.h>
# include "ll.h"
# include "bv.h"
# include "bf.h"
# include "hash.h"
# include "statistics.h"

# ifndef BADSPEAK
# define BADSPEAK "/afs/cats.ucsc.edu/users/g/darrell/badspeak.txt"
# endif

# ifndef NEWSPEAK
# define NEWSPEAK "/afs/cats.ucsc.edu/users/g/darrell/newspeak.txt"
# endif

# ifndef ESPERANTO
# define ESPERANTO "/afs/cats.ucsc.edu/users/g/darrell/Esperanto.txt"
# endif

/* --Function prototypes and Global Variables-- */

/* 
 * yylex() runs scanner until it gets a token, and returns the
 * value returned by the action associated with that token.
 */
int yylex(void); //Comment and code are taken from Boris' flex tutorial.	

/*This function frees the memory that is allocated in yy.lex.c*/
int yylex_destroy(void);

/*
 * When yylex() returns, the text matched by the scanner is
 * stored in a string accessible through the pointer yytext.
 */
extern char* yytext; //Comment and code are taken from Boris' flex tutorial.

/*
 * yyin is the file from which the scanner will get its input.
 * By default, it is stdin.
 */
extern FILE* yyin; //Comment and code are taken from Boris' flex tutorial.

uint8_t getStatistics = false; // Used for -s flag.
bool moveToFront = false; // Used for -m and -b flags. By default, we don't use the rule.
double average = 0; // Average moves in findLL.
uint64_t seeks = 0; // Total moves made in findLL.
uint64_t dictionary = 0; // Number of words in badspeak.txt.
uint64_t translations = 0; // Number of words in newspeak.txt.
uint64_t text = 0; // Number of words read by yylex().
double densityOne = 0; // Density of set bits(1) in the first bloom filter.
double densityTwo = 0; // Density of set bits(1) in the first bloom filter.

int main(int argc, char**argv)
{
    FILE *filePath;
    int scanfOutput = 0;
    char badWordNoReplacement[6] = "NoRep";
    char badWord[200]; // Buffer for badspeak.txt.
    char oldWord[200]; // Buffer for oldspeak words in newspeak.txt.
    char newWord[200]; // Buffer for newspeak words in newspeak.txt.
    char inputCharacter = 0; //Used for getopt input.
    uint8_t desiredBit = 11; // Used to check bits in the bit vector.
    uint8_t badSpeakFlag = false; // Set true if a badspeak word is read.
    uint8_t oldSpeakFlag = false; // Set true if an oldspeak word is read.
    uint8_t membershipValue = 10; // Used to check bloom filter membership.
    uint8_t badWordNoReplacementFlag = false; // For checking badspeak.
    uint8_t falsePositiveFlag = false; // Set true whenever a word is a member of both filters.
    uint8_t alreadyInOldSpeakArray = false; // Used to avoid duplicate words for newspeak.
    uint8_t alreadyInBadSpeakArray = false; // Used to avoid duplicate words for badspeak.
    uint32_t hashTableSize = 10000;
    uint32_t bloomFilterSize = 1048576;
    uint32_t desiredLength = 16;    // This represent the length, the number of bits,
                                    // for the bit vector.
    uint32_t initA[] = {0xDeadD00d, 0xFadedBee, 0xBadAb0de, 0xC0c0aB0a}; // First Bloom filter 
    uint32_t initB[] = {0xDeadBeef, 0xFadedB0a, 0xCafeD00d, 0xC0c0aB0a}; // Second Bloom filter 
    uint32_t initH[] = {0xDeadD00d, 0xFadedBee, 0xBadAb0de, 0xC0c0Babe}; // Hash table
    uint64_t arrayLength = 0;    // Length of array of pointers for newspeak.
    uint64_t arrayCapacity = 8;    // Capacity of array of pointers for newspeak.
    uint64_t arrayLengthBad = 0;    // Length of array of pointers for badspeak.
    uint64_t arrayCapacityBad = 8;  // Capacity of array of pointers for badspeak.
    bitV *bitVector = NULL; // Pointer to the bit vector.
    bloomF *bloomFilterOne; // Pointer to the first bloom filter.
    bloomF *bloomFilterTwo; // Pointer to the second bloom filter.
    hashTable *hashT = NIL; // Pointer to the hash table.
    listNode *foundNode = NIL; // Pointer to the searched node in the hash table.
    bitVector = newVec(desiredLength);    //The bit vector is created.
    char **stringArray = NULL;    // Pointer to the array of pointers for newspeak..
    char **stringArrayBad = NULL;    // Pointer to the array of pointers for badspeak.
    char **temporaryPointer = NULL;    //This is the pointer variable used to prevent
                                       // a leak in case realloc() fails.
    stringArray = (char **)calloc(arrayCapacity, sizeof(char *)); // Create array of pointers for
                                                                  // newspeak.txt.
    stringArrayBad = (char **)calloc(arrayCapacityBad, sizeof(char *)); // Create array of pointers 
                                                                        // for badspeak.txt.
    while ((inputCharacter = getopt(argc, argv, "smbh:f:")) != -1)
    {
        if (inputCharacter == 's') // To get only statistics.
        {
            setBit(bitVector, 0);
            getStatistics = true;
        } 
        else if (inputCharacter == 'm') // To use the move to front rule.
        {
            setBit(bitVector, 1);
            if ((desiredBit = valBit(bitVector, 2)) == 0x01)
            {
                printf("\nYou cannot use -m and -b flags at the same time!\n");
                return 1;
            }
        } 
        else if (inputCharacter == 'b') // To not use the move to front rule.
        {
            setBit(bitVector, 2);
            if ((desiredBit = valBit(bitVector, 1)) == 0x01)
            {
                printf("\nYou cannot use -m and -b flags at the same time!\n");
                return 1;
            }
        }
        else if (inputCharacter == 'h') // To change size of the hash table.
        {
            setBit(bitVector, 3);
            hashTableSize = (uint32_t)atoi(optarg);
            if (bloomFilterSize == 0 || hashTableSize == 0)
            {
                printf("\nSize for the bloom filters or the hash table cannot be zero as we cannot"
                       " divide by 0\n");
                return 1;
            }
        } 
        else if (inputCharacter == 'f') // To change the size of the bloom filter.
        {
            setBit(bitVector, 4);
            bloomFilterSize = (uint32_t)atoi(optarg);    //The usage of optarg is from 
                                                        //https://linux.die.net/man/3/getopt.
            if (bloomFilterSize == 0 || hashTableSize == 0)
            {
                printf("\nSize for the bloom filters or the hash table cannot be zero as we cannot"
                       " divide by 0\n");
                return 1;
            }
        } 
    }
    // Create the filters and the hash table.
    bloomFilterOne = newBF(bloomFilterSize, initA);
    bloomFilterTwo = newBF(bloomFilterSize, initB);
    hashT = newHT(hashTableSize, initH);
    // Open the oldspeak and newspeak folders
    filePath = fopen(BADSPEAK, "r");
    scanfOutput = fscanf(filePath, "%s", badWord);
    while (scanfOutput != EOF) // Set bloom filters with bad speak.
    {
        if (getStatistics == true)
        {
            ++dictionary;
        }
        setBF(bloomFilterOne, badWord);
        setBF(bloomFilterTwo, badWord);
        scanfOutput = fscanf(filePath, "%s", badWord);
    }
    fclose(filePath);
    filePath = fopen(NEWSPEAK, "r");
    scanfOutput = fscanf(filePath, "%s %s", oldWord, newWord);
    while (scanfOutput != EOF) // Get newspeak into hash table. Set bloom filters with newspeak.
    {
        if (getStatistics == true)
        {
            ++translations;
        }
        setBF(bloomFilterOne, oldWord);
        setBF(bloomFilterTwo, oldWord);
        insertHT(hashT, oldWord, newWord);
        scanfOutput = fscanf(filePath, "%s %s", oldWord, newWord);
    }
    fclose(filePath);
    filePath = fopen(BADSPEAK, "r");
    scanfOutput = fscanf(filePath, "%s", badWord);
    while (scanfOutput != EOF) // Get the badspeak into hash table.
    {
        foundNode = findHT(hashT, badWord);
        if (foundNode == NIL) // If badspeak word has a match in newspeak, don't add it.
        {
            insertHT(hashT, badWord, badWordNoReplacement);
        }
        scanfOutput = fscanf(filePath, "%s", badWord);
    }
    if ((desiredBit = valBit(bitVector, 1)) == 0x01)
    {
        moveToFront = true;
    }
    fclose(filePath);
    // Start reading the user input.
    int tokenID = 0;
    yyin = stdin;
    while (tokenID != -1)
    {
        tokenID = yylex();
        if (getStatistics == true && tokenID != -1)
        {
            ++text;
        }
        uint32_t j = strlen(yytext);
        for (uint32_t i = 0; i < j; i++)
        {
            yytext[i] = tolower(yytext[i]);
        }
        // check for membership in two bloom filters!
        membershipValue = memBF(bloomFilterOne, yytext);
        if (membershipValue == 1)
        {
            membershipValue = memBF(bloomFilterTwo, yytext);
            if (membershipValue == 1)
            {
                falsePositiveFlag = true;
                if (falsePositiveFlag == true)
                {
                    // Check the hash table for a replacement. If there is any, recommend it. If
                    // there are none, the person goes to the joycamp.
                    foundNode = findHT(hashT, yytext);
                    if (foundNode != NIL)
                    {
                        int stringCompareValue = 0;
                        stringCompareValue = strcasecmp(foundNode->newspeak, badWordNoReplacement);
                        if (stringCompareValue == 0) // Differentiate between bad and old speak.
                        {
                            badWordNoReplacementFlag = true;
                        }
                    }
                    if (foundNode != NIL && badWordNoReplacementFlag != true)
                    {
                        if (arrayLength > 0)
                        {
                            int stringCompareValue = 0;
                            for (uint64_t i = 0; i < arrayLength;) // Prevent duplicates.
                            {
                                stringCompareValue = strcasecmp(yytext, stringArray[i]);
                                if (stringCompareValue == 0)
                                {
                                    alreadyInOldSpeakArray = true;
                                }
                            i = i + 2;
                            }
                        }
                        if (alreadyInOldSpeakArray != true)
                        {
                            // Save the words in an array of pointers to strings.
                            stringArray[arrayLength] = strdup(yytext);    //Save the input.
                            ++arrayLength;
                            if (arrayCapacity == arrayLength)    //If the array is filled... 
                            {
                                temporaryPointer = stringArray;    //Save the pointer so we don't 
                                                                   //lose it.
                                arrayCapacity = (arrayCapacity * 2);  //This is the doubling 
                                                                      //algorithm...
                                //We realloc the array and protect the first pointer by using a 
                                //temporary pointer.
                                temporaryPointer = (char **)realloc(stringArray, sizeof (char *) *
                                                   arrayCapacity);
                                if (temporaryPointer != NIL)    //If realloc didn't fail... 
                                {
                                    stringArray = temporaryPointer;    //Save the new pointer as 
                                                                                 //the original.
                                }
                                else
                                {
                                    printf("\nCouldn't realloc!\n");
                                }
                            }
                            stringArray[arrayLength] = strdup(foundNode->newspeak);    //Save the 
                                                                                       //input.
                            ++arrayLength;
                            if (arrayCapacity == arrayLength)    //If the array is filled... 
                            {
                                temporaryPointer = stringArray;    //Save the pointer so we don't 
                                                                   //lose it.
                                arrayCapacity = (arrayCapacity * 2);  //This is the doubling 
                                                                      //algorithm...
                                //We realloc the array and protect the first pointer by using a 
                                //temporary pointer.
                                temporaryPointer = (char **)realloc(stringArray, sizeof (char *) *
                                                   arrayCapacity);
                                if (temporaryPointer != NIL)    //If realloc didn't fail... 
                                {
                                    stringArray = temporaryPointer;    //Save the new pointer as 
                                                                       //the original.
                                }
                                else
                                {
                                    printf("\nCouldn't realloc!\n");
                                }
                            }
                            oldSpeakFlag = true;
                        }
                        else
                        {
                            alreadyInOldSpeakArray = false; // Reset the flag.
                        }
                    }
                    else if (foundNode != NIL && badWordNoReplacementFlag == true) //Record
                                                                                   //badspeak.
                    {
                        if (arrayLengthBad > 0)
                        {
                            int stringCompareValueTwo = 0;
                            for (uint64_t i = 0; i < arrayLengthBad; i++)
                            {
                                stringCompareValueTwo = strcasecmp(yytext, stringArrayBad[i]);
                                if (stringCompareValueTwo == 0) // No duplicates.
                                {
                                    alreadyInBadSpeakArray = true;
                                }
                            }
                        }
                        if (alreadyInBadSpeakArray != true)
                        {
                            stringArrayBad[arrayLengthBad] = strdup(yytext);    //Save the input.
                            ++arrayLengthBad;
                            if (arrayCapacityBad == arrayLengthBad)    //If the array is filled... 
                            {
                                temporaryPointer = stringArrayBad;    //Save the pointer so we 
                                                                      //don't lose it.
                                arrayCapacityBad = (arrayCapacityBad * 2);  //This is the doubling 
                                                                            //algorithm...
                                //We realloc the array and protect the first pointer by using a 
                                //temporary pointer.
                                temporaryPointer = (char **)realloc(stringArrayBad, sizeof (char *)
                                                   * arrayCapacityBad);
                                if (temporaryPointer != NIL)    //If realloc didn't fail... 
                                {
                                    stringArrayBad = temporaryPointer;    //Save the new pointer as
                                                                          //the original.
                                }
                                else
                                {
                                    printf("\nCouldn't realloc!\n");
                                }
                            }
                            badSpeakFlag = true; // Reset the flag.
                        }
                        else
                        {
                            alreadyInBadSpeakArray = false; // Reset the flag.
                        }
                    }
                badWordNoReplacementFlag = false; // Reset the flag
                }
            }
        }
    }
    if (badSpeakFlag == true && (arrayLength != 0 || arrayLengthBad != 0) && 
       (desiredBit = valBit(bitVector, 0)) != 0x01)
    {
        // Print the general message for sending people to the joycamp.
        printf("Dear Comrade,\n\nYou have chosen to use degenerate words that may cause hurt\n"
        "feelings or cause your comrades to think unpleasant thoughts.\nThis is doubleplus bad."
        " To correct your wrongthink and\nsave community consensus we will be sending you to"
        " joycamp\nadministered by Miniluv.\n\nYour errors:\n\n");
        uint64_t i = arrayLengthBad - 1;
        for (uint64_t j = 0;  j <= arrayLengthBad - 1; j++)
        {
            printf("%s\n", stringArrayBad[i]);
            i--;
        }
        if (oldSpeakFlag == true && arrayLength != 0)
        {
            printf("\nThink on these words during your vacation!\n\n");
            uint64_t j = 0;
            uint64_t i = arrayLength - 1;
            for (uint64_t j = 0; j <= arrayLength - 1;)
            {
                printf("%s -> %s\n", stringArray[i - 1], stringArray[i]);
                i = i - 2;
                j = j + 2;
            }
            i = j / 2; // Suppress the warning.
        }
    }
    if (oldSpeakFlag == true && badSpeakFlag != true && arrayLength != 0 && 
       (desiredBit = valBit(bitVector, 0)) != 0x01)
    {
        // Print the general message for recommending people to use other words.
        printf("Dear Comrade,\n\nSubmitting your text helps to preserve feelings and prevent\n"
        "badthink. Some of the words that you used are not goodspeak.\nThe list shows how to"
        " turn the oldspeak words into newspeak.\n\n");
        // Print the newspeak.
        uint64_t j = 0;
        uint64_t i = arrayLength - 1;
        for (uint64_t j = 0; j <= arrayLength - 1;)
        {
            printf("%s -> %s\n", stringArray[i - 1], stringArray[i]);
            i = i - 2;
            j = j + 2;
        }
        i = j / 2; // Suppress the warning.
    }
    if (getStatistics == true) // If -s is set, print the statistics.
    {
        if (average != 0)
        {
            average = (seeks / average);
        }
        densityOne = (double)countBF(bloomFilterOne);
        densityOne = (double)(densityOne / lenBF(bloomFilterOne));
        densityTwo = (double)countBF(bloomFilterTwo);
        densityTwo = (double)(densityTwo / lenBF(bloomFilterTwo));
        printf("Seeks %lu, Average %f, Dictionary %lu, Translations %lu, Text %lu, " 
        "Densities: %f, %f\n", seeks, average, dictionary, translations, text, densityOne, 
        densityTwo);
    }
    if (arrayLength != 0) // Free the strings.
    {
        for (uint64_t i = 0; i <= arrayLength - 1; i++)
        {
            free(stringArray[i]);
        }
    }
    free(stringArray); // Free the array of pointers.
    if (arrayLengthBad != 0) // Free the strings.
    {
        for (uint64_t i = 0; i <= arrayLengthBad - 1; i++)
        {
            free(stringArrayBad[i]);
        }
    }
    free(stringArrayBad); // Free the array of pointers.
    delBF(bloomFilterOne); // Free the bloom filters.
    delBF(bloomFilterTwo);
    delHT(hashT); // Free the hash table.
    delVec(bitVector); // Free the bit vector.
    yylex_destroy(); // Free the things used by flex.
    return 0;
}
