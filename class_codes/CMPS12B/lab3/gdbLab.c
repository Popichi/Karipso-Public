/*
 * This file is meant to be used with lab3. There is an error in this file which
 * results in a segmentation fault.
 *
 * Your job is to figure out which line of code causes this segmentation fault
 * and you also need to figure out why the segmentation fault occurs.
 *
 * TODO: 1. Compile Using
 *  gcc -Wall -Wextra -Werror -Wpedantic -std=c99 -g -o gdbLab gdbLab.c -lm
 *
 * TODO: 2. Execute Using
 *  ./gdbLab
 *
 * TODO: 3. Debug Using
 *  gdb ./gdbLab
 *
 * TIPS
 * -> Run the executable in GDB. It should tell you where the segmentation fault
 *    is occuring. Boom, thats one thing out of the way.
 *
 * -> Now is the hard part. Why is is occuring? This is where your brain might
 *    hurt. You will need to step through each instruction one at a time and
 *    validate the values held in the variables. Read the tutorial properly.
 *
 * -> Read all the comments in this file. The answer lies in them. It is an
 *    obvious answer as soon as you spot the problem.
 *
 * NOTE: In case you want to experiment with this source code, copy it
 *       into a new file and then experiment with it.
 */
// We are adding another header file because we used functions such as malloc()
// and free().
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

# define FIRST_X         (3.0f)
# define FIRST_Y         (5.0f)
# define SECOND_X        (4.0f)
# define SECOND_Y        (7.0f)

/* --- DO NOT CHANGE THIS CODE. THIS IS NOT WHAT SEG FAULTS THE CODE --- */
/* YOU MAY IGNORE WHAT IT DOES. BUT MAYBE YOU SHOULDN'T. */
# ifdef __clang__
# pragma clang diagnostic ignored "-Wreturn-stack-address"
# else
# ifdef __GNUC__
# pragma GCC diagnostic ignored "-Wreturn-local-addr"
# endif
# endif

# ifdef __linux__
int correctOS = 1;
# else
int correctOS = 0;
# endif
/* --- END --- */

struct cartesianCoordinate
{
    /* These two variables represent a point on the cartesian plane. */
    float x;
    float y;
};

/**
 * This function creates a new structure which can hold two integers. These two
 * integers collectively represent a point on the cartesian plane.
 *
 * @param x The value of the x axis.
 * @param y The value of the y axis.
 * @return Pointer to a structure of type cartesianCoordinate.
 */
struct cartesianCoordinate *makePoint(float x, float y)
{
    /* We make space to hold two points */
    // struct cartesianCoordinate thisCoordinate; -> part of the old code.

    struct cartesianCoordinate *structPointer = NULL; //It is good to initialize every variable 
                                                      //in C.
    // We malloc the struct because if we just create it on the stack, we don't create a new one 
    // (I believe that this may be wrong and it may be just that by keeping the address of the 
    // struct, we are still able to access it at the place where it once existed even though
    // "it technically doesn't not exist" anymore; however, I am not quite sure.) even when we
    // call the function more than once. We may have solved the segmentation fault problem 
    // by creating a pointer to the struct and returning it(as the function return type is a 
    // pointer to struct cartesianCoordinate type); however, if we do not malloc and just create 
    // the struct on the stack, both firstPointer and the secondPointer point to the same thing.
    // Therefore, we get "distance = 0" when we use the findDistance function. By using malloc,
    // we prevent values from being over written. For example, "x = 3.0" doesn't become x = 4.0.
    // because firstPointer and secondPointer point to different structs.
    structPointer = malloc(sizeof(struct cartesianCoordinate));
    if (structPointer == NULL)
    {
        return NULL;    // We are returning NULL to tell the main that something went wrong and
                        // we were not able to allocate memory for the struct.
    }
    
    // structPointer = &thisCoordinate; -> part of the old code.

    /* We set the respective values */
    // We have to use a different syntax because we are using a pointer this time.
    structPointer -> x = x;
    structPointer -> y = y;
    // thisCoordinate.x = x; -> part of the old code.
    // thisCoordinate.y = y; -> part of the old code.

    /*
     * We return the address of our new coordinate structure. We need to use the
     * ampersand operator here because we are returning the address of the
     * variable and not the variable itself. We need to do this because
     * thisCoordinate is not a pointer.
     */
    //return &thisCoordinate; -> part of the old code.

    // Simply returning a type "struct cartesianCoordinate *" which is a pointer to the struct
    // cartesianCoordinate solved the segmentation fault because otherwise the pointers
    // firstPointer and secondPointer had the values 0x0 which is equivalent to NULL.
    // As expected, dereferencing a null pointer in findDistance function caused segmentation
    // fault.
    return structPointer;
}

/**
 * This function is used to find out the distance between two points on the
 * cartesian plane. Notice how I broke the line in my function because my
 * arguments were too long.  This helps make the code more readable.
 *
 * Recall that the distance formula is:
 *  dist = sqrt((x2-x1)^2 + (y2-y1)^2)
 *
 * @param firstPoint The first point.
 * @param secondPoint The second point.
 * @return The distance between the two points.
 */
float findDistance(struct cartesianCoordinate *firstPoint,
                   struct cartesianCoordinate *secondPoint)
{
    float distance;
    float xDistance;
    float yDistance;

    /* Get x part */
    xDistance = secondPoint->x - firstPoint->x;
    xDistance = xDistance * xDistance;

    /* Get y part */
    yDistance = secondPoint->y - firstPoint->y;
    yDistance = yDistance * yDistance;

    /* Combine them together */
    distance = xDistance + yDistance;
    distance = sqrt(distance);

    return distance;
}

/**
 * The main function simply constructs two cartesian points and finds the
 * distance between them.
 *
 * @return 0
 */
int main(void)
{
    float distance;
    struct cartesianCoordinate *firstPoint;
    struct cartesianCoordinate *secondPoint;

    /* --- DO NOT CHANGE --- */
    if (!correctOS)
    {
        printf("Not using Linux. Please switch to the timeshare\n");
        return 1;
    }
    /* --- END --- */

    /* Get first point */
    firstPoint = makePoint(FIRST_X, FIRST_Y);
    // Check for errors. If something went wrong in function "makePoint" then return 1 to the OS to
    // tell that something went wrong.
    if (firstPoint == NULL)
    {
        return 1;
    }

    /* Get second point */
    secondPoint = makePoint(SECOND_X, SECOND_Y);
    // Check for errors. If something went wrong in function "makePoint" then return 1 to the OS to
    // tell that something went wrong.
    if (secondPoint == NULL)
    {
        return 1;
    }

    /* Get the distance and print it */
    distance = findDistance(firstPoint, secondPoint);
    printf("Distance Between Points: %.2f\n", distance);

    // Since we created two struct cartesianCoordinate types on the heap, we need to free them
    // to prevent a memory leak. Although they were created in "makePoint" function, firstPoint
    // and secondPoint pointers hold the address for these structs. So, we can use them to free
    // these structs with no problems.
    free(firstPoint);
    free(secondPoint);
    return 0;
}