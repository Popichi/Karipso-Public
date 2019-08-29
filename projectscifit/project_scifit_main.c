/* 
 * File: project_scifit_main.c
 * Author: Anil Celik Maral
 * Email: anilcelikmaral@gmail.com
 * Brief: Randomized meal planner for daily nutritional needs
 * Created on August 27, 2017
 */

# include <stdio.h>
# include "global_defines.h"

// Local defines
#define NO_MORE_INPUT -1   // Should I use the end of line hash define instead?

int main ()
{
    while ((in_char = getopt(argc, argv, "vi:o:")) != NO_MORE_INPUT)
    {
        if (in_char == 's') // To get only statistics.
        {
            get_stat = true;
        } 
        else if (in_char == 'i')
        {
        }
        else if (in_char == 'o')
        {
        }
    }
    // Ask for parameters.
    // What parameters?
    // Which data structure?
    // What do I want to do?
    // Give meal choices that will fill the daily nutritional needs in a randomized way!
    return 0;
}

// Temporary meal recordings will be here.
struct nutritional_label {
   int account_number;
   char *first_name;
   char *last_name;
   float balance;
};
