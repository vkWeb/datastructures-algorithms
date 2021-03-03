# Prevents conflict with same file name
.PHONY: clean

# GCC compiler flags
CFLAGS = -g -Wall -Werror -Wextra -std=c11

# Object files
OBJS = bst.o stack.o

bst: bst.o
		gcc $(CFLAGS) bst.o stack.o -o bst

bst.o: bst.c stack.o
		gcc $(CFLAGS) -c bst.c

stack.o: stack.c stack.h
		gcc $(CFLAGS) -c stack.c

clean:
		rm $(OBJS)
