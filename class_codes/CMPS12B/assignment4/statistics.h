/*###############################################
# Anil Celik Maral - amaral
# amaral@ucsc.edu
# 1454995
# Assignment - 4
# Lab: Friday, 9:00am - 10:00am
# Lab Partner: None
# Date: 05/27/17
###############################################*/

# ifndef _STATISTICS
# define _STATISTICS
# include <stdint.h>
# include <stdio.h>
# include <stdbool.h>
# include "stack.h"

/* Pointer to get and then free the stack in main that is created in loadTree function */
extern void *loadTreeStack;

/* The number of bits(non-encoded) that the original file had! */
extern uint64_t bitCount;

/* The number of bits(encoded) that the original file had! */
extern uint64_t bitCountEncoded;

# endif