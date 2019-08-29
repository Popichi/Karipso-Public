###############################################
# Anil Celik Maral - amaral
# amaral@ucsc.edu
# 1454995
# Lab - 3
# Lab: Friday, 9:00am - 10:00am
# Lab Partner: None
# Date: 05/11/17
###############################################

#I have used examples and structures that were provided in the 1st lab manual while creating this
#makefile. Therefore, there may be similarities.
CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c99 -g -lm
CC = gcc
OBJECTS = gdbLab.o

.PHONY: all
all: gdbLab

gdbLab: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o gdbLab
	 
gdbLab.o: gdbLab.c
	$(CC) $(CFLAGS) -c gdbLab.c
	
clean:
	rm -f gdbLab.o gdbLab
