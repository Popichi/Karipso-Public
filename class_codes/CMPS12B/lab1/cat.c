/*#############################################
# Anil Celik Maral - amaral
# amaral@ucsc.edu
# 1454995
# Lab-1
# Lab: Friday, 9:00am - 10:00am
# Lab Partner: None
###############################################
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdint.h>

int main(int argc, char**argv)
{
    int closedFlag = 0;		//This flag is used to check if close function worked properly or
				//not.
    int fileDirectory = 0;	//This holds the reference to a specific file that we open.
    ssize_t bytesRead = 0;	//This holds the number of bytes(characters) in the file tht we
				//are reading.
    uint8_t buffer[1024];	//The characters are saved into this character array.
    char fileName[128];		//This file contains the name of the file that we are trying to
				//open. We get this information from the input of the user.

    //Below is the loop for getting the arguments(file names) one by one.  
    for (int i = 1; i < argc; ++i) {
	//Using sprintf, we save the first argument that we care to an array to use later in open
	//function. Notice that we start the index from 1 because we don't care about the function
	//itself which is called as "./cat". We don't want to save it or do anything with it so we
	//skip it.
        sprintf(fileName, "%s", argv[i]);
        fileDirectory = open(fileName, O_RDONLY);	//Here we open the file and save the
							//reference to it.
        if (fileDirectory == -1) {			//If we fail to open the file we call
							//perror and then we call exit to warn the
							//user about the error.
            perror("cat");
            exit(errno);
        }
	bytesRead = read(fileDirectory, buffer, 1024);  //Here we read the file and save the
							//characters in our buffer. We also save the
							//number of bytes that we read. I am
							//assuming that the null character is not
							//counted.
	if (bytesRead == -1) {				//If we fail to read the file we call
							//perror and then we call exit to warn the
							//user about the error.
	    perror("cat");
	    exit(errno);
	}
	//We print as many bytes as we have read using the function read previously. This helps us
	//counter the issue of reading the uninitialized parts of our buffer which can be a problem
	//if we use "characterBeingReadAndPrinted != bytesRead". We also reset the bufferIndex and
	//the variable that holds the character that will be printed right below this comment by
	//re-initializing them.
	int bufferIndex = 0;
	char characterBeingReadAndPrinted = 0;
	//In this while loop we print the characters that we read from the file and we do it until
	//we have printed as many bytes as we have read. 
	while (bufferIndex != bytesRead){
	    characterBeingReadAndPrinted = buffer[bufferIndex];
	    printf("%c", characterBeingReadAndPrinted);
	    ++bufferIndex;
	}
	closedFlag = close(fileDirectory);	//Here, we close the file that we have previously
						//opened so that we can open another one without
						//problems while we use "fileDirectory" variable.
	if (closedFlag == -1) {			//If we fail to close the file we call perror and
						//then we call exit to warn the user about the
						//error.
            perror("cat");
            exit(errno);
        }
    }
    return 0;	//If the program successfully parses all of the program we return '0' to signal 
		//the success.
}
