#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "stack.h"

/* Note: prefer non-recursive solution whenever possible but DO NOT compromise performance */

// BST Node
struct node
{
    struct node *parent;
    struct node *left_child;
    struct node *right_child;
    int data;
    bool is_left_subtree_traversed;
    bool is_right_subtree_traversed;
};

// Allocates memory for new node, sets the data and returns pointer to it
struct node *getNewNode(int data)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if (new_node == NULL)
    {
        fprintf(stderr, "error: new_node memory failure\n");
        exit(-1);
    }

    new_node->parent = new_node->left_child = new_node->right_child = NULL;
    new_node->is_left_subtree_traversed = new_node->is_right_subtree_traversed = false;
    new_node->data = data;
    return new_node;
}

// Insert node to BST
struct node *insertNodeToBST(struct node *root, int data)
{
    // If tree is empty
    if (root == NULL)
    {
        root = getNewNode(data);
        return root;
    }

    struct node *new_node = getNewNode(data);
    struct node *cursor = root;

    // When we really need to insert in the BST
    while (cursor != NULL)
    {
        if (new_node->data <= cursor->data)
        {
            if (cursor->left_child == NULL)
            {
                new_node->parent = cursor;
                cursor->left_child = new_node;
                break;
            }
            cursor = cursor->left_child;
        }
        else if (new_node->data >= cursor->data)
        {
            if (cursor->right_child == NULL)
            {
                new_node->parent = cursor;
                cursor->right_child = new_node;
                break;
            }
            cursor = cursor->right_child;
        }
    }
    return root;
}

// Traverse binary tree recursively
void traverseRecursive(struct node *root)
{
    if (root != NULL)
    {
        printf("%d ", root->data);
        traverseRecursive(root->left_child);
        traverseRecursive(root->right_child);
    }
}

// Non recursive traversal with stack as an intermediate state manager
/* This function needs to be refactored for perf & simplicity. WIP.
void traverseNonRecursiveWithStack(struct node *root)
{
    if (root == NULL)
    {
        printf("BST empty\n");
        return;
    }

    unsigned int num_of_iterations = 0;
    struct node *nodeAtTop = NULL;
    do
    {
        if (root->is_left_subtree_traversed == false && root->is_right_subtree_traversed == false)
        {
            push(root);
            printf("%d\n", root->data);
            root->is_left_subtree_traversed = true;
            if (root->left_child != NULL)
            {
                root = root->left_child;
                nodeAtTop = getTop();
                continue;
            }
        }
        if (nodeAtTop->is_left_subtree_traversed == true && nodeAtTop->is_right_subtree_traversed == false)
        {
            nodeAtTop->is_right_subtree_traversed = true;
            if (root->right_child != NULL)
            {
                root = nodeAtTop->right_child;
                nodeAtTop = getTop();
                continue;
            }
        }
        if (nodeAtTop->is_left_subtree_traversed == true && nodeAtTop->is_right_subtree_traversed == true)
        {
            root = (struct node *)pop();
        }
        ++num_of_iterations;
        nodeAtTop = getTop();
    } while (nodeAtTop != NULL);

    printf("Number of iterations = %d\n", num_of_iterations);
}*/

// Finding minimum in BST
// Returns pointer to the node with minimum data
struct node *findMin(struct node *root)
{
    while (root->left_child != NULL)
    {
        root = root->left_child;
    }
    return root;
}

// Main Function
int main(void)
{
    // Pointer to Root of BST
    struct node *root = NULL;

    root = insertNodeToBST(root, 10);
    root = insertNodeToBST(root, 8);
    root = insertNodeToBST(root, -5);
    root = insertNodeToBST(root, 3);
    root = insertNodeToBST(root, 12);
    root = insertNodeToBST(root, -12);

    printf("The contents of BST are: ");
    traverseRecursive(root);
    printf("\n");
    printf("Minimum in current BST = %d\n", findMin(root)->data);

    return 0;
}
