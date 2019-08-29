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

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <string.h>
# include <stdbool.h>
# include "aes.h"
# include "hash.h"
# include "ll.h"
# include "statistics.h"

hashTable *newHT(uint32_t l, uint32_t b[]) // Create the hast table
{
    uint8_t successFlag = false;
    hashTable *hashT = NIL;
    hashT = malloc(sizeof(hashTable));
    if (hashT != NIL)
    {
        hashT->h = (listNode **)calloc(l + 1, sizeof(listNode *));
        if (hashT->h != NIL)
        {
            hashT->l = l;
            for (uint8_t i = 0; i < 4; i++)
            {
                hashT->s[i] = b[i]; // Get the salt.
            }
            successFlag = true;
        }
        else
        {
            free(hashT);
        }
    }
    if (successFlag == true) 
    {
        return hashT;
    }
    else 
    {   // successFlag != true
        return NIL;
    }		
}

void delHT(hashTable *hashT)
{
    // Delete each and every linked list. You have the function for that in ll.h.
    // loop for the length of the hash table.
    for (uint32_t i = 0; i < hashT->l; i++)
    {
        delLL(hashT->h[i]);
    }
    free(hashT->h); // Delete the array of pointers to linked lists.
    hashT->h = NIL;
    free(hashT); // Delete the hash table.
    hashT = NIL;
    return;
}

// Finds the node inside the hash table that has the oldspeak.
listNode *findHT(hashTable *hashT, const char *oldWord)
{
    listNode *foundNode = NIL;
    uint32_t hashTableArrayLocation = (hash(hashT, oldWord) % hashT->l);
    if (moveToFront == true) // If this flag is set, we need to move the head.
    {
        foundNode = findLL(&(hashT->h[hashTableArrayLocation]), oldWord);
        if (foundNode != NIL)
        {
            hashT->h[hashTableArrayLocation] = foundNode;
            return foundNode;
        }
        else
        {
            return NIL;
        }
    }
    else
    {
        foundNode = findLL(&(hashT->h[hashTableArrayLocation]), oldWord);
        if (foundNode != NIL) // Don't move the head, just return.
        {
            return foundNode;
        }
        else
        {
            return NIL;
        }
    }
    return NIL;
}

// Inserts elements to the hash table(linked list).
void insertHT(hashTable *hashT, const char *oldWord, const char *newWord)
{
    // We move the head each time we insert. The new head is the thing we inserted.
    uint32_t hashTableArrayLocation = (hash(hashT, oldWord) % hashT->l);
    hashT->h[hashTableArrayLocation] = insertLL(&(hashT->h[hashTableArrayLocation]), oldWord,
    newWord);
    return;
}

// Prints the elements inside the hash table.
void printHT(const hashTable *hashT)
{
    for (uint32_t i = 0; i < hashT->l; i++)
    {
        if ((hashT->h[i]) != NIL)
        {
            printLL((hashT->h[i]));
        }
    }
    return;
}

static inline int realLength(int l)
{
	return 16 * (l / 16 + (l % 16 ? 1 : 0));
}

uint32_t hash(hashTable *h, const char *key)
{
	uint32_t output[4] = { 0x0 };
	uint32_t sum       = 0x0;
	int keyL           = strlen(key);
	uint8_t *realKey   = (uint8_t *) calloc(realLength(keyL), sizeof(uint8_t
    ));

	memcpy(realKey, key, keyL);

	for (int i = 0; i < realLength(keyL); i += 16)
	{
		AES128_ECB_encrypt((uint8_t *) h->s, // Salt
        (uint8_t *) realKey + i,             // Input
        (uint8_t *) output);                 // Output
		sum ^= output[0] ^ output[1] ^ output[2] ^ output[3];
	}
	free(realKey);
	return sum;
}