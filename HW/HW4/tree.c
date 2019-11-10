#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tree.h"

#ifndef AIRPORT_H
#include "airport.h"
#endif

/* TreeNode *newNode(char *)
 * Returns a new node with the given value.
 */
TreeNode *newNode(airport *value)
{
	TreeNode *newND = (TreeNode *)malloc(sizeof(TreeNode));
	newND->value = value;
	newND->left = newND->right = NULL;
	return newND;
}

/* Given a non-empty binary search tree, return the node with minimum
   key value found in that tree. Note that the entire tree does not
   need to be searched. */
TreeNode *minValueNode(TreeNode *root)
{
	TreeNode *current = root;

	//find leftmost leaf
	while (current && current->left != NULL)
		current = current->left;

	return current;
}
//////////////////////////////////////////////////////////////////////////////////////

/* TreeNode *deleteNodeID(TreeNode*, char *)
 * Deletes the given id in the passed tree, returns it.
 * Note: Partially adapted from StackOverflow code.
 */
TreeNode* deleteNodeID(TreeNode* root, char* to_del)
{
    // base case
    if (root == NULL) return root;

    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if (strncmp(root->value->id2, to_del, MAX_STRINGLEN) < 0)
        root->left = deleteNodeID(root->left, to_del);

    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if (strncmp(root->value->id2, to_del, MAX_STRINGLEN) > 0)
        root->right = deleteNodeID(root->right, to_del);

    //found it
    else
    {
        // node with only one child or no child
        if (root->left == NULL)
        {
            TreeNode *temp = root->right;
			printf("Deleted");
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            TreeNode *temp = root->left;
			printf("Deleted");
            free(root);
            return temp;
        }

        // node with two children: Get the inorder successor (smallest
        // in the right subtree)
        TreeNode* temp = minValueNode(root->right);

        // Copy the inorder successor's content to this node
        root->value = temp->value;

        // Delete the inorder successor
        root->right = deleteNodeID(root->right, temp->value->id2);
    }
    return root;
}

/* TreeNode *insert(TreeNode *, airport *, int)
 * Inserts the given value into the given tree and returns the head back.
 */
TreeNode *insert(TreeNode *root, airport *value, int what_cmp)
{
	//empty, return new node
	if (root == NULL)
		return newNode(value);

	//else, there's stuff in the tree
	if (compareport(root, value, what_cmp) <= 0)
		root->left = insert(root->left, value, what_cmp);
	else
		root->right = insert(root->right, value, what_cmp);

	//return original head if we want it
	return root;
}

/* int compareport(TreeNode*, airport*, int)
 * Compares either the city or ID depending on last arg and returns the strncmp
 */
int compareport(TreeNode *node, airport *port, int what_cmp)
{
	switch (what_cmp)
	{
	case ID_SEARCH:
		return strncmp(node->value->id2, port->id2, MAX_STRINGLEN);

	case CITY_SEARCH:
		return strncmp(node->value->city, port->city, MAX_STRINGLEN);

	//search by default by ID
	default:
		return strncmp(node->value->id2, port->id2, MAX_STRINGLEN);
	}
}

/* void freeTree(TreeNode*)
 * Recursively frees all elements within the BST.
 */
void freeTree(TreeNode *node)
{
	if (node == NULL)
		return;

	//Recusrively call and free
	freeTree(node->left);
	freeTree(node->right);
	free(node);
}

/* TreeNode *findByID(TreeNode *, char *)
 * Finds the given TreeNode with id equal to passed char and returns it
 */
TreeNode *findByID(TreeNode *root, char *id_to_find)
{
	//Root is either NULL or our target from prev. recursions
	if (root == NULL || (strncmp(root->value->id2, id_to_find, MAX_STRINGLEN) == 0))
		return root;

	//else, there's stuff in the tree
	if (strncmp(root->value->id2, id_to_find, MAX_STRINGLEN) < 0)
		return findByID(root->left, id_to_find);
	else
		return findByID(root->right, id_to_find);
}

/* TreeNode *printByCity(TreeNode *, char *)
 * Finds all Nodes with given value of city
 */
void printByCity(TreeNode *root, char *city_to_find)
{
	if (root == NULL) //If we reached below a leaf
		return;
	else if ((strncmp(root->value->city, city_to_find, MAX_STRINGLEN) == 0)) //We found one!
	{
		printAirport(root->value);
	}

	//Keep looking
	if (strncmp(root->value->city, city_to_find, MAX_STRINGLEN) <= 0)
		return printByCity(root->left, city_to_find);
	else
		return printByCity(root->right, city_to_find);
}