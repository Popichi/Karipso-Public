###############################################
# Anil Celik Maral - amaral
# amaral@ucsc.edu
# 1454995
# Assignment - 4
# Lab: Friday, 9:00am - 10:00am
# Lab Partner: None
# Date: 05/27/17
###############################################

# I have used examples and structures that were provided in the 1st lab manual while creating this
# makefile. Therefore, there may be similarities.
CFLAGS = -Wall -Wextra -Wpedantic -Werror -g
CC = gcc
OBJECTS = stack.o queue.o encode.o insertionsort.o huffman.o bv.o

.PHONY: all
all: encode decode

encode: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o encode
	 
encode.o: encode.c stack.c queue.c insertionsort.c huffman.c bv.c
	$(CC) $(CFLAGS) -c encode.c

decode: decode.o stack.o queue.o huffman.o bv.o insertionsort.o
	$(CC) $(CFLAGS) decode.o insertionsort.o stack.o queue.o huffman.o bv.o -o decode
	 
decode.o: decode.c stack.c queue.c huffman.c insertionsort.c bv.c
	$(CC) $(CFLAGS) -c decode.c
	
clean:
	rm -f encode encode.o decode decode.o stack.o queue.o insertionsort.o huffman.o bv.o
