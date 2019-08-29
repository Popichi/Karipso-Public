###############################################
# Anil Celik Maral - amaral
# amaral@ucsc.edu
# 1454995
# Lab - 2
# Lab: Friday, 9:00am - 10:00am
# Lab Partner: None
# Date: 04/27/17
###############################################


#I have used examples and structures that were provided in the 1st lab manual while creating this
#makefile. Therefore, there may be similarities.
CFLAGS = -Wall -Wextra -Wpedantic -Werror -g -std=c99
CC = gcc
OBJECTS = arraylist.o

.PHONY: all
all: arraylist

arraylist: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o arraylist
	 
arraylist.o: arraylist.c
	$(CC) $(CFLAGS) -c arraylist.c
	
clean:
	rm -f arraylist.o arraylist
