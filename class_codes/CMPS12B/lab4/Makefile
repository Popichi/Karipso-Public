###############################################
# Anil Celik Maral - amaral
# amaral@ucsc.edu
# 1454995
# Lab - 4
# Lab: Friday, 9:00am - 10:00am
# Lab Partner: None
# Date: 06/09/17
###############################################

# I have used examples and structures that were provided in the 1st lab manual while creating this
# makefile. Therefore, there may be similarities.
CFLAGS = -Wall -Wextra -Wpedantic -Werror -g
CC = gcc
OBJECTS = increment.o

.PHONY: all
all: increment

increment: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o increment -lpthread
	 
increment.o: increment.c
	$(CC) $(CFLAGS) -c increment.c

clean:
	rm -f increment.o increment