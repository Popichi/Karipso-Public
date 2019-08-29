/*#############################################
# Anil Celik Maral - amaral
# amaral@ucsc.edu
# 1454995
# Assignment-0
# Lab: Friday, 9:00am - 10:00am
# Lab Partner: None
#############################################
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
    //Declarations for the faces of the die as type enum and
    //the array that represents the die.
    typedef enum faciem {LEFT, RIGHT, CENTER, PASS} faces;
    faces die[] = {LEFT, RIGHT, CENTER, PASS, PASS, PASS};

    //Declaration for the struct of variables that should be checked during the game.
    typedef struct gameData {
        char playerInTheGame[10];		//This array is used to track if a player is in the game or not.
        unsigned int theIndexLimit;		//This is used to some manipulations depending on how many
				                //players there are.
        unsigned int potMoney;
        unsigned int playerMoney[10];		//playerMoney[0] represents Whoopi's money .... 
					        //playerMoney[9] represents Clint's money.
    } gameData;

    //Declarations for the player names in the game.
    const char *names[] = {"Whoopi",
			   "Dale",
		           "Rosie",
			   "Jimmie",
			   "Barbara",
		           "Kyle",
			   "Raven",
			   "Tony",
			   "Jenny",
			   "Clint"};

    //This is the constant declaration that is used to label a player who is in the game.
    enum activePlayer {
        playerIsActive = 15,
    };

    //Here, we create the struct on stack and initialize what we can at this point.
    gameData lrcData;
    lrcData.potMoney = 0;

    //This is the declaration of a couple of important constants that are used during
    //initialization of some variables.
    enum playerInitializationFlags {
        thereAreTenPlayers = 10,
        thereAreNinePlayers = 9,
        thereAreEightPlayers = 8,
        thereAreSevenPlayers = 7,
        thereAreSixPlayers = 6,
        thereAreFivePlayers = 5,
        thereAreFourPlayers = 4,
        thereAreThreePlayers = 3,
        thereAreTwoPlayers = 2,
        thereIsOnePlayer = 1,
        thereAreNoPlayers = 0
    };

    //Declaration of variable that will be used later.
    uint8_t playerInitializationFlag = thereAreNoPlayers;		//Used to select between 
								        //initialization options.
    uint8_t onlyOnePlayerHasMoney = false;				//Used to end the game.
    unsigned int randomSeed = 0;					//Used in scanf.
    unsigned int numberOfPlayers = 0;					//Used in scanf.
    unsigned int indexForInitialization = 0;				//Used during initialization of 
									//players.
    unsigned int playersWithNoMoneyCount = 0;				//Used to keep track of how many 
									//players have money.
    uint8_t theDiceRoll = 0;						//Used to save how save the dice 
									//roll.
    uint8_t indexLrc = 0;						//This is the index for choosing
	        							//values in the lrcData struct.

    printf("Random seed:");					        //The prompt for asking for the 
									//seed.
    scanf("%u", &randomSeed);

    printf("How many players?");				        //The prompt for asking for the 
									//number of players.
    scanf("%u", &numberOfPlayers);

    //This is the big check that sets a flag for further initialization and it
    //also sets the the index limit that is used for resetting index back to
    //the first player, checking which player won and for edge cases such as
    //when the first player gives money to the last player.
    if (numberOfPlayers == 10) {
        playerInitializationFlag = thereAreTenPlayers;
        lrcData.theIndexLimit = 9;
    } else if (numberOfPlayers == 9) {
        playerInitializationFlag = thereAreNinePlayers;
        lrcData.theIndexLimit = 8;
    } else if (numberOfPlayers == 8) {
        playerInitializationFlag = thereAreEightPlayers;
        lrcData.theIndexLimit = 7;
    } else if (numberOfPlayers == 7) {
        playerInitializationFlag = thereAreSevenPlayers;
        lrcData.theIndexLimit = 6;
    } else if (numberOfPlayers == 6) {
        playerInitializationFlag = thereAreSixPlayers;
        lrcData.theIndexLimit = 5;
    } else if (numberOfPlayers == 5) {
        playerInitializationFlag = thereAreFivePlayers;
        lrcData.theIndexLimit = 4;
    } else if (numberOfPlayers == 4) {
        playerInitializationFlag = thereAreFourPlayers;
        lrcData.theIndexLimit = 3;
    } else if (numberOfPlayers == 3) {
        playerInitializationFlag = thereAreThreePlayers;
        lrcData.theIndexLimit = 2;
    } else if (numberOfPlayers == 2) {
        playerInitializationFlag = thereAreTwoPlayers;
        lrcData.theIndexLimit = 1;
    } else if (numberOfPlayers == 1) {
        printf("\nThe number of players can only be between 1 and 10, including 10."
	"\nRestart the program to enter again!");
	return (1);
    } else {
	printf("\nThe number of players can only be between 1 and 10, including 10."
	"\nRestart the program to enter again!");
	return (1);
	}

    //This is the actual initialization. It sets the starting money for each
    //player that is playing and also sets the flag for whether they are
    //active or not.
    for (indexForInitialization = playerInitializationFlag; indexForInitialization != 0;
	indexForInitialization--) {
        if (indexForInitialization == 10) {
            lrcData.playerMoney[9] = 3;
            lrcData.playerInTheGame[9] = playerIsActive;
        }
        if (indexForInitialization == 9) {
            lrcData.playerMoney[8] = 3;
            lrcData.playerInTheGame[8] = playerIsActive;
        }
        if (indexForInitialization == 8) {
            lrcData.playerMoney[7] = 3;
            lrcData.playerInTheGame[7] = playerIsActive;
        }
        if (indexForInitialization == 7) {
            lrcData.playerMoney[6] = 3;
            lrcData.playerInTheGame[6] = playerIsActive;
        }
        if (indexForInitialization == 6) {
            lrcData.playerMoney[5] = 3;
            lrcData.playerInTheGame[5] = playerIsActive;
        }
        if (indexForInitialization == 5) {
            lrcData.playerMoney[4] = 3;
            lrcData.playerInTheGame[4] = playerIsActive;
        }
        if (indexForInitialization == 4) {
            lrcData.playerMoney[3] = 3;
            lrcData.playerInTheGame[3] = playerIsActive;
        }
        if (indexForInitialization == 3) {
            lrcData.playerMoney[2] = 3;
            lrcData.playerInTheGame[2] = playerIsActive;
        }
        if (indexForInitialization == 2) {
            lrcData.playerMoney[1] = 3;
            lrcData.playerInTheGame[1] = playerIsActive;
        }
        if (indexForInitialization == 1) {
            lrcData.playerMoney[0] = 3;
            lrcData.playerInTheGame[0] = playerIsActive;
        }
    }

    //Here, we give the entered seed to srand so that we can later call rand().
    srand(randomSeed);

    while (onlyOnePlayerHasMoney != true) {
        //If the player has three or more dollars.
        if (lrcData.playerMoney[indexLrc] >= 3) {
	    //The index below is used to represent how many times to player will roll the dice.
            unsigned int rollIndex = 3;
            printf("\n%s rolls...", names[indexLrc]);
            //If the roll is ".", then the player passes.
            //Else if the roll is "Left", then the player gives one dollar to the person on the											    //left.
            //Else if the roll is "Right", then the player gives one dollar to the person on the
	    //right.
            //Else the player puts one dollar to the center.
	    //The check 'if (rollIndex != 1) is used so that we can put ',' or '.' depending 
	    //on whether it is the last roll or not to make the output more readable.
            while (rollIndex != 0) {
                theDiceRoll = die[(rand() % 6)];
                if (theDiceRoll == PASS) {
                    if (rollIndex != 1) {
                        printf("gets a pass,");
                    } else {
                        printf("gets a pass.");
                    }
                } else if (theDiceRoll == LEFT) {
	  	    //Below, we check for the special case of the first player.
		    //It is special because the player on the left is the last
		    //one and therefore, we need to do special operations.
		    //The special case is when indexLrc == 0.
                    if (indexLrc == 0) {
                        --lrcData.playerMoney[indexLrc];
                        ++lrcData.playerMoney[lrcData.theIndexLimit];
                        if (rollIndex != 1) {
                            printf("gives $1 to %s,", names[lrcData.theIndexLimit]);
                        } else {
                            printf("gives $1 to %s.", names[lrcData.theIndexLimit]);
                        }
		    //Below, we check for the regular case.
                    } else {
                        --lrcData.playerMoney[indexLrc];
                        ++lrcData.playerMoney[indexLrc - 1];
                        if (rollIndex != 1) {
                            printf("gives $1 to %s,", names[indexLrc - 1]);
                        } else {
                            printf("gives $1 to %s.", names[indexLrc - 1]);
                        }
                    }
                } else if (theDiceRoll == RIGHT) {
		    //Below, we check for the special case of the last player.
		    //It is special because the player on the right is the first
		    //one and therefore, we need to do special operations.
		    //The special case is when indexLrc == lrcData.theIndexLimit.
		    //lrcData.theIndexLimit represents the last player.
                    if (indexLrc == lrcData.theIndexLimit) {
                        --lrcData.playerMoney[indexLrc];
                        ++lrcData.playerMoney[0];
                        if (rollIndex != 1) {
                            printf("gives $1 to %s,", names[0]);
                        } else {
                            printf("gives $1 to %s.", names[0]);
                        }
		    //Below, we check for the regular case.
                    } else {
                        --lrcData.playerMoney[indexLrc];
                        ++lrcData.playerMoney[indexLrc + 1];
                        if (rollIndex != 1) {
                            printf("gives $1 to %s,", names[indexLrc + 1]);
                        } else {
                            printf("gives $1 to %s.", names[indexLrc + 1]);
                        }
                    }
                } else if (theDiceRoll == CENTER) {
                    --lrcData.playerMoney[indexLrc];
                    ++lrcData.potMoney;
                    if (rollIndex != 1) {
                        printf("puts $1 in the pot,");
                    } else {
                        printf("puts $1 in the pot.");
                    }
                }
                --rollIndex;
            }
	//The if statement below is taken if the player has 2 dollars.	
        } else if (lrcData.playerMoney[indexLrc] == 2) {
	    //The index below is used to represent how many times to player will roll the dice.
            unsigned int rollIndex = 2;
            printf("\n%s rolls...", names[indexLrc]);
            //If the roll is ".", then the player passes.
            //Else if the roll is "Left", then the player gives one dollar to the person on the 										    //left.
            //Else if the roll is "Right", then the player gives one dollar to the person on the 
	    //right.
            //Else the player puts one dollar to the center.
	    //The check 'if (rollIndex != 1) is used so that we can put ',' or '.' depending on
	    //whether it is the last roll or not to make the output more readable.
            while (rollIndex != 0) {
                theDiceRoll = die[(rand() % 6)];
                if (theDiceRoll == PASS) {
                    if (rollIndex != 1) {
                        printf("gets a pass,");
                    } else {
                        printf("gets a pass.");
                    }
                } else if (theDiceRoll == LEFT) {
		    //Below, we check for the special case of the first player.
		    //It is special because the player on the left is the last
		    //one and therefore, we need to do special operations.
		    //The special case is when indexLrc == 0.
                    if (indexLrc == 0) {
                        --lrcData.playerMoney[indexLrc];
                        ++lrcData.playerMoney[lrcData.theIndexLimit];
                        if (rollIndex != 1) {
                            printf("gives $1 to %s,", names[lrcData.theIndexLimit]);
                        } else {
                            printf("gives $1 to %s.", names[lrcData.theIndexLimit]);
                        }
		    //Below, we check for the regular case.
                    } else {
                        --lrcData.playerMoney[indexLrc];
                        ++lrcData.playerMoney[indexLrc - 1];
                        if (rollIndex != 1) {
                            printf("gives $1 to %s,", names[indexLrc - 1]);
                        } else {
                            printf("gives $1 to %s.", names[indexLrc - 1]);
                        }
                    }
                } else if (theDiceRoll == RIGHT) {
		    //Below, we check for the special case of the last player.
		    //It is special because the player on the right is the first
		    //one and therefore, we need to do special operations.
		    //The special case is when indexLrc == lrcData.theIndexLimit.
		    //lrcData.theIndexLimit represents the last player.
                    if (indexLrc == lrcData.theIndexLimit) {
                        --lrcData.playerMoney[indexLrc];
                        ++lrcData.playerMoney[0];
                        if (rollIndex != 1) {
                            printf("gives $1 to %s,", names[0]);
                        } else {
                            printf("gives $1 to %s.", names[0]);
                        }
		    //Below, we check for the regular case.
                    } else {
                        --lrcData.playerMoney[indexLrc];
                        ++lrcData.playerMoney[indexLrc + 1];
                        if (rollIndex != 1) {
                            printf("gives $1 to %s,", names[indexLrc + 1]);
                        } else {
                            printf("gives $1 to %s.", names[indexLrc + 1]);
                        }
                    }
                } else if (theDiceRoll == CENTER) {
                    --lrcData.playerMoney[indexLrc];
                    ++lrcData.potMoney;
                    if (rollIndex != 1) {
                        printf("puts $1 in the pot,");
                    } else {
                        printf("puts $1 in the pot.");
                    }
                }
                --rollIndex;
            }
	//The if statement below is taken if the player has 1 dollar.
        } else if (lrcData.playerMoney[indexLrc] == 1) {
            //The index below is used to represent how many times to player will roll the dice.
            unsigned int rollIndex = 1;
            printf("\n%s rolls...", names[indexLrc]);
            //If the roll is ".", then the player passes.
            //Else if the roll is "Left", then the player gives one dollar to the person on the 										    //left.
            //Else if the roll is "Right", then the player gives one dollar to the person on the 
	    //right.
            //Else the player puts one dollar to the center.
	    //Unlike previous if statements, we don't check for (rollIndex != 1) because we only 
	    //printf() one case each time such as BLAH BLAH gets a pass.
            while (rollIndex != 0) {
                theDiceRoll = die[(rand() % 6)];
                if (theDiceRoll == PASS) {
                    printf("gets a pass.");
                } else if (theDiceRoll == LEFT) {
		    //Below, we check for the special case of the first player.
		    //It is special because the player on the left is the last
		    //one and therefore, we need to do special operations.
	            //The special case is when indexLrc == 0.
                    if (indexLrc == 0) {
                        --lrcData.playerMoney[indexLrc];
                        ++lrcData.playerMoney[lrcData.theIndexLimit];
                        printf("gives $1 to %s.", names[lrcData.theIndexLimit]);
		    //Below, we check for the regular case.
                    } else {
                        --lrcData.playerMoney[indexLrc];
                        ++lrcData.playerMoney[indexLrc - 1];
                        printf("gives $1 to %s.", names[indexLrc - 1]);
                    }
                } else if (theDiceRoll == RIGHT) {
		    //Below, we check for the special case of the last player.
		    //It is special because the player on the right is the first
		    //one and therefore, we need to do special operations.
		    //The special case is when indexLrc == lrcData.theIndexLimit.
		    //lrcData.theIndexLimit represents the last player.
                    if (indexLrc == lrcData.theIndexLimit) {
                        --lrcData.playerMoney[indexLrc];
                        ++lrcData.playerMoney[0];
                        printf("gives $1 to %s.", names[0]);
		    //Below, we check for the regular case.
                    } else {
                        --lrcData.playerMoney[indexLrc];
                        ++lrcData.playerMoney[indexLrc + 1];
                        printf("gives $1 to %s.", names[indexLrc + 1]);
                    }
                } else if (theDiceRoll == CENTER) {
                    --lrcData.playerMoney[indexLrc];
                    ++lrcData.potMoney;
                    printf("puts $1 in the pot.");
                }
                --rollIndex;
            }
        }
	//Below, we have a bunch of if statements to check which players don't have money.
	//These statements are taken only if the player joined the game at the beginning
	//of the initialization. We use this to determine if someone has won the game or
	//not. If there are (numberOfPlayers - 1) players that don't have money, then it
	//means that someone has just won the game. If not, the game continues.
        if (lrcData.playerMoney[0] == 0 && lrcData.playerInTheGame[0] == playerIsActive) {
            ++playersWithNoMoneyCount;
        }
        if (lrcData.playerMoney[1] == 0 && lrcData.playerInTheGame[1] == playerIsActive) {
            ++playersWithNoMoneyCount;
        }
        if (lrcData.playerMoney[2] == 0 && lrcData.playerInTheGame[2] == playerIsActive) {
            ++playersWithNoMoneyCount;
        }
        if (lrcData.playerMoney[3] == 0 && lrcData.playerInTheGame[3] == playerIsActive) {
            ++playersWithNoMoneyCount;
        }
        if (lrcData.playerMoney[4] == 0 && lrcData.playerInTheGame[4] == playerIsActive) {
            ++playersWithNoMoneyCount;
        }
        if (lrcData.playerMoney[5] == 0 && lrcData.playerInTheGame[5] == playerIsActive) {
            ++playersWithNoMoneyCount;
        }
        if (lrcData.playerMoney[6] == 0 && lrcData.playerInTheGame[6] == playerIsActive) {
            ++playersWithNoMoneyCount;
        }
        if (lrcData.playerMoney[7] == 0 && lrcData.playerInTheGame[7] == playerIsActive) {
            ++playersWithNoMoneyCount;
        }
        if (lrcData.playerMoney[8] == 0 && lrcData.playerInTheGame[8] == playerIsActive) {
            ++playersWithNoMoneyCount;
        }
        if (lrcData.playerMoney[9] == 0 && lrcData.playerInTheGame[9] == playerIsActive) {
            ++playersWithNoMoneyCount;
        }
	//Below, we check who still had money(who was the winner) when the game ended.
	//We run through the player array to save the index for the winner so that we
	//can print the correct name and that players money. We also set the game over
	//flag to be true so that we can end the while loop and finish the game.
	//lrcData.theIndexLimit represents (number of players in the game - 1).
	//We also use it for limiting the for loop because it happens to represent the
	//last player in the game too as in C arrays start from 0.
        if (playersWithNoMoneyCount == lrcData.theIndexLimit) {
            onlyOnePlayerHasMoney = true;
			unsigned int checkIndex = 0;
			unsigned int correctIndex = 0;
			for (checkIndex = 0; checkIndex <= lrcData.theIndexLimit; checkIndex++) {
				if (lrcData.playerMoney[checkIndex] != 0){
					correctIndex = checkIndex;
				}
			}
            printf("\n%s wins the $%u pot with $%u left in the bank!", names[correctIndex],
	    lrcData.potMoney, lrcData.playerMoney[correctIndex]);
        } else {
			playersWithNoMoneyCount = 0;	//We reset the count so that we can check it next time 															//correctly.
	}
	//If the index has reached to the last player, then reset it back to the first player.
	//Otherwise, keep incrementing.
        if (indexLrc == lrcData.theIndexLimit) {
            indexLrc = 0;
        } else {
            ++indexLrc;
        }
    }
    return 0;
}
