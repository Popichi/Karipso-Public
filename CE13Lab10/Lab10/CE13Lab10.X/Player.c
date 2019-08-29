/*#############################################
# Anil Celik Maral - amaral
# amaral@ucsc.edu
# 1454995
# Lab#10, Rpg
# Section:C , Wed 05:00PM-08:00PM, Kyle Cordes and Megan Boivin 
# Lab Partner: None
#############################################
 */
// **** Include libraries here ****
// Standard libraries
#include <string.h>
#include <math.h>
#include <stdio.h>

//CMPE13 Support Library
#include "UnixBOARD.h"
#include "Player.h"

// Inventory.
static uint8_t numberOfItemsInInventory = 0;
static char playerInventory[4] = {0, 0, 0, 0};
static uint8_t theInventoryCounter = 0;

/**
 * Adds the specified item to the player's inventory if the inventory isn't full.
 * @param item The item number to be stored: valid values are 0-255.
 * @return SUCCESS if the item was added, STANDARD_ERRROR if the item couldn't be added.
 */
int AddToInventory(uint8_t item)
{
    if (numberOfItemsInInventory != INVENTORY_SIZE && (item >= 0 && item <= 255)) {
        playerInventory[theInventoryCounter] = item;
        ++numberOfItemsInInventory;
        ++theInventoryCounter;
        return SUCCESS;
    } else if (numberOfItemsInInventory >= INVENTORY_SIZE) {
        return STANDARD_ERROR;
    }
    return STANDARD_ERROR;
}

/**
 * Check if the given item exists in the player's inventory.
 * @param item The number of the item to be searched for: valid values are 0-255.
 * @return SUCCESS if it was found or STANDARD_ERROR if it wasn't.
 */
int FindInInventory(uint8_t item)
{
    uint8_t searchCounter = 0;
    uint8_t itemBackUp = 0;
    while (searchCounter < INVENTORY_SIZE) {
        itemBackUp = playerInventory[searchCounter];
        if (itemBackUp == item) {
            return SUCCESS;
        }
        ++searchCounter;
    }
    return STANDARD_ERROR;
}
