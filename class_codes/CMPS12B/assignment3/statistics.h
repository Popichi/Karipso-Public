/*###############################################
# Anil Celik Maral - amaral
# amaral@ucsc.edu
# 1454995
# Assignment - 3
# Lab: Friday, 9:00am - 10:00am
# Lab Partner: None
# Date: 05/14/17
###############################################*/

# ifndef _STATISTICS
# define _STATISTICS
# include <stdint.h>
# include <stdio.h>
# include <stdbool.h>

extern uint8_t getStatistics;

/* Seeks - Every time you iterate
a linked list one step in ll.c increment
this counter (this should be exclusively
in findLL).*/
extern uint64_t seeks;

/* Average - The average number of seeks
per findLL call (simply count the number
of calls to findLL and divide the seeks
by this count).*/
extern double average;

/* Dictionary - The number of forbidden 
words in badspeak.txt (why is it named
this...I don't know?)*/
extern uint64_t dictionary;

/* Translations - The number of translations
in newspeak.txt*/
extern uint64_t translations;

/*Text - The number of words read from stdin
 using yylex()*/
extern uint64_t text;

/*Densities - The ratio of bits set to total
 bits for each bloom filter (Use countBf and
 lenBf to calculate this)*/
extern double densityOne; // Density of the first bloom filter.
extern double densityTwo;
# endif

