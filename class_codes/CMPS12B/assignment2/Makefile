###############################################
# Anil Celik Maral - amaral
# amaral@ucsc.edu
# 1454995
# Assignment - 2
# Lab: Friday, 9:00am - 10:00am
# Lab Partner: None
# Date: 04/29/17
###############################################

#I have used examples and structures that were provided in the 1st lab manual while creating this
#makefile. Therefore, there may be similarities.
CFLAGS = -Wall -Wextra -Wpedantic -Werror -g -std=c99
CC = gcc
OBJECTS = minsort.o sorting.o bv.o bubblesort.o insertionsort.o quicksort.o mergesort.o

.PHONY: all
all: sorting

sorting: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o sorting
	 
sorting.o: minsort.c sorting.c bv.c bubblesort.c insertionsort.c quicksort.c mergesort.c
	$(CC) $(CFLAGS) -c sorting.c
	
clean:
	rm -f sorting sorting.o minsort.o bv.o bubblesort.o insertionsort.o quicksort.o mergesort.o
