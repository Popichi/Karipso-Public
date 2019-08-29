/*###############################################
# Anil Celik Maral - amaral
# amaral@ucsc.edu
# 1454995
# Assignment - 2
# Lab: Friday, 9:00am - 10:00am
# Lab Partner: None
# Date: 04/29/17
###############################################*/

// minsort.h
// Author: Prof. Darrell Long

# ifndef _Minsort
# define _Minsort
# include <stdint.h>
# include <stdio.h>
# include <stdbool.h>

uint32_t minIndex(uint32_t a[], uint32_t first, uint32_t last);

void minSort(uint32_t a[], uint32_t length); 
# endif