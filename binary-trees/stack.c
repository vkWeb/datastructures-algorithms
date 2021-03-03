#include <stdio.h>  // For NULL, printfs
#include <stdlib.h> // For malloc

// Note: error handling is left to the api consumer,
//       we gracefully report what's wrong, rest is the job of the consumer.

// Data structure for stack's node
struct node
{
    void *value;
    struct node *prev;
};

struct node *TOP = NULL;

// Return pointer to the TOP of stack if push is successful
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
    new_node->value = input_data;
    return TOP->value;
}

// Pops (frees) the top of the stack and returns pointer to the new top if success
// else returns NULL if stack if already empty
void *pop(void)
{
    if (TOP == NULL)
    {
        return NULL;
    }

    struct node *temp = TOP;
    TOP = TOP->prev;
    free(temp);
    return TOP == NULL ? NULL : TOP->value;
}

// Returns top of stack
void *getTop(void)
{
    return TOP == NULL ? NULL : TOP->value;
}
