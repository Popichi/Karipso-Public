/*###############################################
# Anil Celik Maral - amaral
# amaral@ucsc.edu
# 1454995
# Assignment - 2
# Lab: Friday, 9:00am - 10:00am
# Lab Partner: None
# Date: 04/29/17
###############################################*/

# ifndef _INSTRUMENTED
# define _INSTRUMENTED
# include <stdint.h>
# include <stdio.h>
# include <stdbool.h>

extern uint64_t moveCount;
extern uint64_t compares;

# ifdef _INSTRUMENTED
# define SWAP(x,y) { uint32_t t = x; x = y; y = t; ; moveCount += 3; }
# else
# define SWAP(x,y) { uint32_t t = x; x = y; y = t; ; }
# endif
# endif

