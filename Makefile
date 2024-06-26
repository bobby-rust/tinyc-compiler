.DEFAULT_GOAL := build

CC = gcc
CFLAGS = -Wall -Wextra -pedantic

build:
	$(CC) $(CFLAGS) -o lexer lexer.c string.c file.c

asan:
	$(CC) $(CFLAGS) -g -fsanitize=address -o lexer_asan lexer.c string.c file.c 
