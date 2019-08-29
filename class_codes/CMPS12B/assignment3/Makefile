###############################################
# Anil Celik Maral - amaral
# amaral@ucsc.edu
# 1454995
# Assignment - 3
# Lab: Friday, 9:00am - 10:00am
# Lab Partner: None
# Date: 05/14/17
###############################################

# I have used examples and structures that were provided in the 1st lab manual while creating this
# makefile. Therefore, there may be similarities. Additionally, we use flex to produce a .c file
# from the words.l file. Afterward, we combine this into our exacutable banhammer.
CFLAGS = -Wall -Wextra -Wpedantic -Werror -g
CC = gcc
OBJECTS = banhammer.o bf.o lex.yy.o aes.o ll.o hash.o bv.o

.PHONY: all
all: banhammer

banhammer: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o banhammer -lfl
	 
banhammer.o: banhammer.c bf.c lex.yy.c ll.c hash.c bv.c
	$(CC) $(CFLAGS) -c banhammer.c

lex.yy.o : lex.yy.c
	$(CC) -c lex.yy.c

lex.yy.c: words.l
	flex words.l
	
clean:
	rm -f banhammer banhammer.o bf.o lex.yy.o lex.yy.c aes.o ll.o hash.o bv.o

