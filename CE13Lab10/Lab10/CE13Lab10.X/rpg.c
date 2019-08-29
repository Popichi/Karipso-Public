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
#include "Game.h"

// User libraries

// **** Set any macros or preprocessor directives here ****

// **** Declare any data types here ****

typedef struct gameData {
    char titleArray[GAME_MAX_ROOM_TITLE_LENGTH + 1];
    char descriptionArray[GAME_MAX_ROOM_DESC_LENGTH + 1];
    uint8_t northExit;
    uint8_t southExit;
    uint8_t eastExit;
    uint8_t westExit;
} gameData;

// **** Define any global or external variables here ****
#define NO_ITEMS_TO_CHECK 7

// **** Declare any function prototypes here ****

int main()
{
    static gameData gameDataStruct;
    static uint8_t titleCheckFlag = FALSE;
    static uint8_t descriptionCheckFlag = FALSE;
    static uint8_t initalizationCheckFlag = FALSE;

    /******************************** Your custom code goes below here ********************************/
    initalizationCheckFlag = GameInit();
    if (initalizationCheckFlag == SUCCESS) {
        titleCheckFlag = GameGetCurrentRoomTitle(gameDataStruct.titleArray);
        if (titleCheckFlag != 0) {
            printf("%s", gameDataStruct.titleArray);
        } else {
            printf("\nERROR PRINTING THE TITLE");
        }
        descriptionCheckFlag = GameGetCurrentRoomDescription(gameDataStruct.descriptionArray);
        if (descriptionCheckFlag != 0) {
            printf("\n%s", gameDataStruct.descriptionArray);
        } else {
            printf("\nERROR PRINTING THE DESCRIPTION");
        }
    } else {
        printf("\nERROR INITIALIZING THE FILE");
    }
    return (0);
    /**************************************************************************************************/
}
