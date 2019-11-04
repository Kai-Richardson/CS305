#include <stdlib.h>

#include "tree.h"

TreeNode *newNode(void *value)
{
    TreeNode *newND = (TreeNode *)malloc(sizeof(TreeNode));
    newND->value = value;
    newND->left = newND->right = NULL;
    return newND;
}

TreeNode *deleteNode(TreeNode *root, void *value)
{
}

TreeNode *insert(TreeNode *node, void *value)
{
    //empty, return new node
    if (node == NULL)
        return newNode(value);

    //else, there's stuff in the tree
    if (value < node->value)
        node->left = insert(node->left, value);
    else
        node->right = insert(node->right, value);

    //return original head if we want it
    return node;
}

int height(TreeNode * t) {

  if (t == NULL)
  {
    return -1;
  }
    return 1+max(height(t->left), height(t->right));
}

void print_inorder(TreeNode *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%s ", root->value);
        inorder(root->right);
    }
}