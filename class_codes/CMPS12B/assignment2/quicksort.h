/*###############################################
# Anil Celik Maral - amaral
# amaral@ucsc.edu
# 1454995
# Assignment - 2
# Lab: Friday, 9:00am - 10:00am
# Lab Partner: None
# Date: 04/29/17
###############################################*/

# ifndef _Quicksort
# define _Quicksort
# include <stdint.h>
# include <stdio.h>
# include <stdbool.h>

typedef struct partitionInfo {
    uint32_t *pivotPointer;
    uint32_t *pivotOfTheLeftArray;
    uint32_t lengthOfTheLeftPartOfTheArray;
    uint32_t *pivotOfTheRightArray;
    uint32_t lengthOfTheRightPartOfTheArray;
    uint32_t lengthOfTheArrayBeingPartitioned;
} partitionInfo;

void quickSort(uint32_t a[], uint32_t length);

void partitionTheArray(partitionInfo *partitionInfoStruct);
# endif
