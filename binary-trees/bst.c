#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "stack.h"

// BST Node
struct node
{
    struct node *parent;
    struct node *left_child;
    struct node *right_child;
    int data;
    bool isLeftSubtreeTraversed;
    bool isRightSubtreeTraversed;
};

// Insert node to BST
struct node *insertNodeToBST(struct node *root, int data)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if (new_node == NULL)
    {
        printf("error: new_node failure\n");
        exit(-1);
    }

    new_node->parent = new_node->left_child = new_node->right_child = NULL;
    new_node->isLeftSubtreeTraversed = new_node->isRightSubtreeTraversed = false;
    new_node->data = data;

    if (root == NULL)
    {
        root = new_node;
        return root;
    }

    // Real logic
    struct node *cursor = root;
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
void traverseNonRecursiveWithStack(struct node *root)
{
    struct node *cursor = root;
    if (cursor == NULL)
    {
        printf("BST empty\n");
        return;
    }

    unsigned int num_of_iterations = 0;
    do
    {
        ++num_of_iterations;
        struct node *nodeAtTop = (struct node *)getTop();
        if (cursor != NULL && cursor->isLeftSubtreeTraversed == false && cursor->isRightSubtreeTraversed == false)
        {
            push(cursor);
            printf("%d\n", cursor->data);
            cursor->isLeftSubtreeTraversed = true;
            cursor = cursor->left_child;
        }
        else if (nodeAtTop->isLeftSubtreeTraversed == true && nodeAtTop->isRightSubtreeTraversed == false)
        {
            nodeAtTop->isRightSubtreeTraversed = true;
            cursor = nodeAtTop->right_child;
        }
        else if (nodeAtTop->isLeftSubtreeTraversed == true && nodeAtTop->isRightSubtreeTraversed == true)
        {
            cursor = (struct node *)pop();
        }
    } while ((struct node *)getTop() != NULL);
    printf("Number of iterations = %d\n", num_of_iterations);
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
    root = insertNodeToBST(root, 36);
    root = insertNodeToBST(root, 0);
    root = insertNodeToBST(root, 96);

    traverseNonRecursiveWithStack(root);

    printf("\n");
    return 0;
}
