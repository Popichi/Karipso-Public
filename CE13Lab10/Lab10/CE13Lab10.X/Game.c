#include "UnixBOARD.h"
#include "Player.h"
#include "Game.h"
#include <stdint.h>
#include <stdio.h>

//Variables that are used in multiple functions.
static FILE *roomPointer = NULL;
static char roomDirectory[100];
static uint8_t theCurrentByteBeingRead = 0;
static uint16_t roomNumber = 0;
//static uint8_t titleCheckFlag = FALSE;
//static uint8_t descriptionCheckFlag = FALSE;
//static uint8_t initalizationCheckFlag = FALSE;
static uint8_t itemRequirementsCheckFlag = FALSE;
static uint8_t itemAvailabilityCheckFlag = FALSE;

typedef struct gameData {
    char titleArray[GAME_MAX_ROOM_TITLE_LENGTH + 1];
    char descriptionArray[GAME_MAX_ROOM_DESC_LENGTH + 1];
    uint8_t northExit;
    uint8_t southExit;
    uint8_t eastExit;
    uint8_t westExit;
} gameData;

static gameData gameDataStruct;

//Function prototypes.
//Helper functions.
int GameCheckItemRequirements(void);
int GameCheckAvailableItems(void);

//No items to check.
#define NO_ITEMS_TO_CHECK 7
#define NO_ITEMS_TO_PICK 8

//int GameGoNorth(void);

//int GameGoEast(void);

//int GameGoSouth(void);

//int GameGoWest(void);

int GameInit(void)
{
    gameDataStruct.northExit = 0;
    gameDataStruct.southExit = 0;
    gameDataStruct.eastExit = 0;
    gameDataStruct.westExit = 0;
    sprintf(roomDirectory, "RoomFiles/room%d.txt", STARTING_ROOM);
    roomPointer = fopen(roomDirectory, "rb");
    roomNumber = STARTING_ROOM;
    if (roomPointer != NULL) {
        return SUCCESS;
    } else if (roomPointer == NULL) {
        return STANDARD_ERROR;
    }
    return STANDARD_ERROR;
}

int GameGetCurrentRoomTitle(char *title)
{
    uint8_t titleLength = 0;
    uint8_t titleLengthBackUp = 0;
    uint8_t counterForTheTitle = 0;
    static uint8_t firstTimeFlag = TRUE;
    static uint8_t theDecryptionKey = 0;
    theDecryptionKey = roomNumber + DECRYPTION_BASE_KEY;
    if (firstTimeFlag == TRUE) {
        theCurrentByteBeingRead = fgetc(roomPointer);
        theCurrentByteBeingRead ^= theDecryptionKey;
        titleLength = theCurrentByteBeingRead;
        titleLengthBackUp = titleLength;
        firstTimeFlag = FALSE;
    }
    while (titleLength > 0) {
        theCurrentByteBeingRead = fgetc(roomPointer);
        theCurrentByteBeingRead ^= theDecryptionKey;
        title[counterForTheTitle] = theCurrentByteBeingRead;
        ++counterForTheTitle;
        --titleLength;
    }
    if (titleLength == 0) {
        title[counterForTheTitle] = '\0';
        ++counterForTheTitle;
        if (itemRequirementsCheckFlag == FALSE) {
            itemRequirementsCheckFlag = GameCheckItemRequirements();
            if (itemRequirementsCheckFlag != STANDARD_ERROR) {
                //printf("\nWe have the required items.");
            } else if (itemRequirementsCheckFlag == NO_ITEMS_TO_CHECK) {
                //printf("\nNo requirements.");
            } else {
                //printf("\nWe don't have the required items.");
            }
            //printf("\nSUCCESS ITEM CHECK!");
        }
        itemRequirementsCheckFlag = TRUE;
        firstTimeFlag = TRUE;
        return counterForTheTitle;
    } else if (titleLength != 0) {
        while (titleLengthBackUp > 0) {
            title[titleLengthBackUp] = '\0';
            --titleLengthBackUp;
        }
        if (titleLengthBackUp == 0) {
            return 0;
        }
    }
    return 0;
}

int GameGetCurrentRoomDescription(char *desc)
{
    uint8_t descriptionLength = 0;
    uint8_t descriptionLengthBackUp = 0;
    uint8_t counterForTheDescription = 0;
    static uint8_t descriptionFlag = TRUE;
    static uint8_t theDecryptionKey = 0;
    theDecryptionKey = roomNumber + DECRYPTION_BASE_KEY;
    if (descriptionFlag == TRUE) {
        theCurrentByteBeingRead = fgetc(roomPointer);
        theCurrentByteBeingRead ^= theDecryptionKey;
        descriptionLength = theCurrentByteBeingRead;
        descriptionLengthBackUp = descriptionLength;
        descriptionFlag = FALSE;
    }
    while (descriptionLength > 0) {
        theCurrentByteBeingRead = fgetc(roomPointer);
        theCurrentByteBeingRead ^= theDecryptionKey;
        desc[counterForTheDescription] = theCurrentByteBeingRead;
        ++counterForTheDescription;
        --descriptionLength;
    }
    if (descriptionLength == 0) {
        desc[counterForTheDescription] = '\0';
        ++counterForTheDescription;
        if (itemAvailabilityCheckFlag == FALSE) {
            itemAvailabilityCheckFlag = GameCheckAvailableItems();
            if (itemAvailabilityCheckFlag != STANDARD_ERROR) {
                //printf("\nWe got the items.");
            } else if (itemAvailabilityCheckFlag == NO_ITEMS_TO_PICK) {
                //printf("\nNo items to get.");
            } else {
                //printf("\nWe couldn't pick up the items.");
            }
            //printf("\nSUCCESS ITEM PICKUP!");
        }
        itemAvailabilityCheckFlag = TRUE;
        descriptionFlag = TRUE;
        return counterForTheDescription;
    } else if (descriptionLength != 0) {
        while (descriptionLengthBackUp > 0) {
            desc[descriptionLengthBackUp] = '\0';
            --descriptionLengthBackUp;
        }
        if (descriptionLengthBackUp == 0) {
            return 0;
        }
    }
    return 0;
}

//uint8_t GameGetCurrentRoomExits(void);

int GameCheckItemRequirements(void)
{
    uint8_t itemRequirementLength = 0;
    static uint8_t firstTimeFlag = TRUE;
    static uint8_t itemCheckFlag = FALSE;
    static uint8_t theDecryptionKey = 0;
    theDecryptionKey = roomNumber + DECRYPTION_BASE_KEY;
    if (firstTimeFlag == TRUE) {
        theCurrentByteBeingRead = fgetc(roomPointer);
        theCurrentByteBeingRead ^= theDecryptionKey;
        itemRequirementLength = theCurrentByteBeingRead;
        firstTimeFlag = FALSE;
    }
    if (itemRequirementLength == 0) {
        return NO_ITEMS_TO_CHECK;
    }
    while (itemRequirementLength > 0) {
        firstTimeFlag = TRUE;
        theCurrentByteBeingRead = fgetc(roomPointer);
        theCurrentByteBeingRead ^= theDecryptionKey;
        itemCheckFlag = FindInInventory(theCurrentByteBeingRead);
        if (itemCheckFlag != SUCCESS) {
            return STANDARD_ERROR;
        }
        --itemRequirementLength;
    }
    return SUCCESS;
}

int GameCheckAvailableItems(void)
{
    uint8_t availableItemLength = 0;
    static uint8_t firstTimeFlag = TRUE;
    static uint8_t availableItemCheckFlag = FALSE;
    static uint8_t theDecryptionKey = 0;
    theDecryptionKey = roomNumber + DECRYPTION_BASE_KEY;
    if (firstTimeFlag == TRUE) {
        theCurrentByteBeingRead = fgetc(roomPointer);
        theCurrentByteBeingRead ^= theDecryptionKey;
        availableItemLength = theCurrentByteBeingRead;
        firstTimeFlag = FALSE;
    }
    if (availableItemLength == 0) {
        return NO_ITEMS_TO_CHECK;
    }
    while (availableItemLength > 0) {
        firstTimeFlag = TRUE;
        theCurrentByteBeingRead = fgetc(roomPointer);
        theCurrentByteBeingRead ^= theDecryptionKey;
        availableItemCheckFlag = AddToInventory(theCurrentByteBeingRead);
        if (availableItemCheckFlag != SUCCESS) {
            return STANDARD_ERROR;
        }
        --availableItemLength;
    }
    return SUCCESS;
}