/* Generic Stack ADT */

#include <stdio.h>  // For NULL, printfs
#include <stdlib.h> // For malloc

// Note: error handling is left to the api consumer,
//       we gracefully report what's wrong (and return NULL),
//       rest is the job of the consumer.

// Data structure for stack's node
struct node
{
    void *data;
    struct node *prev;
};

struct node *TOP = NULL;

// Return data of the TOP of stack if push is successful
// Else return NULL
void *push(void *input_data)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if (new_node == NULL)
    {
        fprintf(stderr, "error: memory for new_node can't be allocated\n");
        return NULL;
    }

    new_node->prev = TOP;
    TOP = new_node;
    new_node->data = input_data;
    return TOP->data;
}

// Pops (frees) the top of the stack and returns the data to new top upon success
// else returns NULL if stack is already empty
void *pop(void)
{
    if (TOP == NULL)
    {
        return NULL;
    }

    struct node *temp = TOP;
    TOP = TOP->prev;
    free(temp);
    return TOP == NULL ? NULL : TOP->data;
}

// Returns data of the top of stack
// else returns NULL if stack is empty
void *getTop(void)
{
    return TOP == NULL ? NULL : TOP->data;
}
