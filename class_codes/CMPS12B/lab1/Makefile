#############################################
# Anil Celik Maral - amaral
# amaral@ucsc.edu
# 1454995
# Lab-1
# Lab: Friday, 9:00am - 10:00am
# Lab Partner: None
#############################################

#I have used examples and structures that were provided in the lab manual while creating this
#makefile. Therefore, there may be similarities.
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c99
CC = gcc
OBJECTS = hello.o

.PHONY: all
all: hello cat

hello: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o hello
	
hello.o: hello.c
	$(CC) $(CFLAGS) -c hello.c
	
cat: cat.o
	$(CC) $(CFLAGS) cat.o -o cat
	
cat.o: cat.c
	$(CC) $(CFLAGS) -c cat.c
	
clean:
	rm -f hello hello.o cat cat.o