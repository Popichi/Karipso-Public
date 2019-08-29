#############################################
# Anil Celik Maral - amaral
# amaral@ucsc.edu
# 1454995
# Assignment - 1
# Lab: Friday, 9:00am - 10:00am
# Lab Partner: None
# Date: 04/22/17
###############################################


#I have used examples and structures that were provided in the lab manual while creating this
#makefile. Therefore, there may be similarities. -lm is used to link the math library.
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c99
CC = gcc
OBJECTS = bv.o parfait.o sieve.o

.PHONY: all
all: parfait

parfait: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o parfait -lm
	
parfait.o: parfait.c bv.c sieve.c
	$(CC) $(CFLAGS) -c parfait.c bv.c sieve.c
	
clean:
	rm -f parfait parfait.o bv.o sieve.o