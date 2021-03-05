/* Prototypes for generic stack ADT */

#ifndef STACK_H
#define STACK_H

// Return data of the TOP of stack if push is successful
// Else return NULL
void *push(void *data);

// Pops (frees) the top of the stack and returns the data to new top upon success
// else returns NULL if stack is already empty
void *pop(void);

// Returns data of the top of stack
// else returns NULL if stack is empty
void *getTop(void);

#endif /* STACK_H */
