# Executable file name
EXE_FNAME = bst
# Main program file name (the file which'll use the apis)
MAIN_FNAME = bst.c
# Main program object file name (the file which'll use the apis)
MAIN_OBJ_FNAME = bst.o
# Object files
OBJS = $(MAIN_OBJ_FNAME) stack.o
# GCC compiler flags
CFLAGS = -g -Wall -Werror -Wextra -std=c11


# Prevents conflict with same file name
.PHONY: clean

$(EXE_FNAME): $(MAIN_OBJ_FNAME) stack.o
		gcc $(CFLAGS) $(MAIN_OBJ_FNAME) stack.o -o $(EXE_FNAME)

$(MAIN_OBJ_FNAME): $(MAIN_FNAME)
		gcc $(CFLAGS) -c $(MAIN_FNAME)

stack.o: stack.c stack.h
		gcc $(CFLAGS) -c stack.c

clean:
		rm $(OBJS)
