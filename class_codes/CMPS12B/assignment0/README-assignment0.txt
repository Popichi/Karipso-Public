#############################################
# Anil Celik Maral - amaral
# amaral@ucsc.edu
# 1454995
# Assignment-0
# Lab: Friday, 9:00am - 10:00am
# Lab Partner: None
#############################################

How the program works:
We have players sitting around a table in LRC. There can be between 1-10 players including 10.The
game starts by initializing the players that are playing and also recording important values such
as the number of players. We get the number of players and the seed that we will use to generate
random dice roll using scanf. The user inputs these values. There is a struct to keep track of the
pot money, the money that each player has, if a player is in the game and the index limit which we
use in important manipulations such as to check if we reached the last player or if there is a
winner or not. After all the setup and initializations, we enter a while loop that continues until
a player wins the game which happens only one player is left with money. There are three mini while
loops inside the main one. The first one is for when a player has three or more dollars.
In this case, the player rolls the dice three times and either pays to the player on the right or
left side, to the pot or gets a pass, which means nothing happens. After enough rolls, we check
every turn how many players still have money to decide if the game is over or not. If it is over,
we go through a for loop to find the winner(the only player with money) and print his name and
money etc. If it is not, we increment our array counter to go the next player. This is a critical
step as we reset only if we reach to the last player because they are theoretically sitting around
a table. Otherwise, we increment it and go through the main while loop one more time. Inside the
left and right dice roll options we have special checks because occasionally the last and first
player have to interact by giving each other money. This is done differently than usual array
incrementation or decrementation as we have to access the first and last element of the array.
When someone wins the game it is announced and the program returns the control to OS so you have
to re-run it to play it one more time.
