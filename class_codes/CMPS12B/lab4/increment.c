/*###############################################
# Anil Celik Maral - amaral
# amaral@ucsc.edu
# 1454995
# Lab - 4
# Lab: Friday, 9:00am - 10:00am
# Lab Partner: None
# Date: 06/09/17
###############################################*/

# include <stdio.h>
# include <stdint.h>
# include <unistd.h>
# include <getopt.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>

# ifndef NIL
# define NIL (void *) 0
# endif

/* --Function Prototypes-- */

/*Sets up the threads with correct arguments so that they run correctly*/
void *threadSetUpFunction(void *threadArgumentStruct);

/*Increment the global variable by one per call*/
void incrementOnce();

/*--Global Variables--*/

int incrementedInteger = 0; // This is the integer that is being incremented.
pthread_mutex_t mutex;  // This is our global control variable to prevent a race conditions.

/* --Data type declarations-- */

/*This is the struct used to set up the threads so that they increment correct amount of times.*/
struct threadArgumentsForIncrement
{
    int incrementCounterForThreads; // The counter.
};

int main(int argc, char**argv)
{
    void* (*pointerToThreadSetUp)(void*) = NIL; // The function pointer to threadSetUpFunction.
    pthread_t *threadReferencesArray = NIL; // This is an array of pointers to threads.
    struct threadArgumentsForIncrement argumentsofThreadsForIncrement; // Struct for threads' info.
    char inputCharacter = 0; //Used for getopt input.
    char *nonNumberPartOfTheString = NIL; // Used by strtoull().
    uint64_t numberOfThreadsToBeOpened = 0;
    int pthreadCreateStatusCheck = -100; // pthread_create() returns 0 on success. Therefore, to
                                         // differentiate, we initialize to a negative number.
    int pthreadJoinStatusCheck = -100;   // pthread_join() returns 0 on success. Therefore, to
                                         // differentiate, we initialize to a negative number.
    int mutexInitializationCheck = -100; // mutex_init() returns 0 on success. Therefore, to
                                         // differentiate, we initialize to a negative number.
    int mutexDestroyCheck = -100;        // mutex_destroy() returns 0 on success. Therefore, to
                                         // differentiate, we initialize to a negative number.
    while ((inputCharacter = getopt(argc, argv, "n:")) != -1)
    {
        if (inputCharacter == 'n') // Choose the number of threads to spawn.
        {
            numberOfThreadsToBeOpened = strtoull(optarg, &nonNumberPartOfTheString, 10);
        }
    }
    mutexInitializationCheck = pthread_mutex_init(&mutex, NIL);
    if (mutexInitializationCheck != 0) // Did we succeed?
    {
        printf("\nMutex initialization error\n");
    }
    pointerToThreadSetUp = threadSetUpFunction; // Get the address of the function;
    argumentsofThreadsForIncrement.incrementCounterForThreads = 1000; // Default increment counter.
    threadReferencesArray = (pthread_t*)calloc(numberOfThreadsToBeOpened, sizeof(pthread_t));
    if (threadReferencesArray != NIL && pointerToThreadSetUp != NIL) // Did calloc succeed?
    {
        for (uint64_t i = 0; i < numberOfThreadsToBeOpened; i++) // Create all the threads.
        {
            pthreadCreateStatusCheck = pthread_create(&threadReferencesArray[i], NIL,
                                                      threadSetUpFunction,
                                                      &argumentsofThreadsForIncrement);
            if (pthreadCreateStatusCheck != 0) // Did we succeed creating?
            {
                printf("\nThread create failure\n");
            }
        }
        for (uint64_t i = 0; i < numberOfThreadsToBeOpened; i++) // Join threads with the main.
        {
            pthreadJoinStatusCheck = pthread_join(threadReferencesArray[i], NIL);
            if (pthreadJoinStatusCheck != 0) // Did we succeed joining?
            {
                printf("\nThread join failure\n");
            }
        }
    }
    mutexDestroyCheck = pthread_mutex_destroy(&mutex); // Free the memory allocated for mutex.
    if (mutexDestroyCheck != 0) // Did we successfully free?
    {
        printf("\nMutex destroy error\n");
    }
    printf("%d\n", incrementedInteger); // Final value of our global variable that is incremented.
    free(threadReferencesArray);
    return 0;
}

/*Sets up the threads with correct arguments so that they run correctly*/
void* threadSetUpFunction(void *threadArgumentStruct)
{
    struct threadArgumentsForIncrement *incrementArguments = 
    (struct threadArgumentsForIncrement*)threadArgumentStruct; // Cast the void pointer.
    int incrementCounter = incrementArguments->incrementCounterForThreads; // Set the counter.
	for (int i = 0; i < incrementCounter; i++)  // Call increment function for counter times(1000).
	{
		incrementOnce();
	}
    return NIL;
}

/*Increment the global variable by one per call*/
void incrementOnce()
{
    pthread_mutex_lock(&mutex); // Lock the mutex for critical section.
    ++incrementedInteger;
    pthread_mutex_unlock(&mutex); // Unlock it after the critical section.
    return;
}
