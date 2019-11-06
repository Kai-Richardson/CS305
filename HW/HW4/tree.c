#include <stdlib.h>
#include <string.h>

#include "tree.h"

/* TreeNode *newNode(char *)
 * Returns a new node with the given value.
 */
TreeNode *newNode(char *value)
{
    TreeNode *newND = (TreeNode *)malloc(sizeof(TreeNode));
    newND->value = value;
    newND->left = newND->right = NULL;
    return newND;
}

/* Given a non-empty binary search tree, return the node with minimum
   key value found in that tree. Note that the entire tree does not
   need to be searched. */
TreeNode *minValueNode(TreeNode *node)
{
    TreeNode *current = node;

    //find leftmost leaf
    while (current && current->left != NULL)
        current = current->left;

    return current;
}

/* TreeNode *deleteNode(TreeNode*, char *)
 * Deletes the given value in the passed tree, returns it.
 * Note: Partially adapted from StackOverflow code.
 */
TreeNode *deleteNode(TreeNode *root, char *value)
{
    // if NULL, error
    if (root == NULL)
        return root;

    //smaller than root value, on left
    if (value < root->value)
        root->left = deleteNode(root->left, value);

    //larger than root value, on right
    else if (value > root->value)
        root->right = deleteNode(root->right, value);

    //else, we found the node to delete
    else
    {
        //only one child or no child
        if (root->left == NULL)
        {
            TreeNode *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            TreeNode *temp = root->left;
            free(root);
            return temp;
        }

        //two children, find inorder successor
        TreeNode *temp = minValueNode(root->right);

        //move inorder successor
        root->value = temp->value;
        root->right = deleteNode(root->right, temp->value);
    }
    return root;
}

/* TreeNode *insert(TreeNode *, char *)
 * Inserts the given value into the given tree and returns the head back.
 */
TreeNode *insert(TreeNode *node, char *value)
{
    //empty, return new node
    if (node == NULL)
        return newNode(value);

    //else, there's stuff in the tree
    if (strcmp(value, node->value) <= 0)
        node->left = insert(node->left, value);
    else
        node->right = insert(node->right, value);

    //return original head if we want it
    return node;
}

/* int height(TreeNode*)
 * Returns the height of the given tree
 */
int height(TreeNode *t)
{

    if (t == NULL)
    {
        return -1;
    }
    return 1 + max(height(t->left), height(t->right));
}

/* void print_inorder(TreeNode*)
 * Prints the elements of the given tree inorder
 */
void print_inorder(TreeNode *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%s ", root->value);
        inorder(root->right);
    }
}