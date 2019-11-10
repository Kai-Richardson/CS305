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

/* TreeNode *deleteNode(TreeNode*, char *, int)
 * Deletes the given id in the passed tree (determined by int), returns it.
 * Note: Partially adapted from StackOverflow code.
 */
TreeNode *deleteNode(TreeNode *root, char *thing_to_del, int what_cmp)
{
	// if NULL, error
	if (root == NULL)
		return root;

	//smaller than root value, on left
	if (what_cmp == ID_SEARCH && strncmp(root->value->id2, thing_to_del, MAX_STRINGLEN) < 0)
		root->left = deleteNode(root->left, thing_to_del, what_cmp);

	else if (what_cmp == CITY_SEARCH && strncmp(root->value->city, thing_to_del, MAX_STRINGLEN) < 0)
	{
		root->left = deleteNode(root->left, thing_to_del, what_cmp);
	}

	//larger than root value, on right
	else if (what_cmp == ID_SEARCH && strncmp(root->value->id2, thing_to_del, MAX_STRINGLEN) > 0)
		root->right = deleteNode(root->right, thing_to_del, what_cmp);

	else if (what_cmp == CITY_SEARCH && strncmp(root->value->id2, thing_to_del, MAX_STRINGLEN) > 0)
	{
		root->right = deleteNode(root->right, thing_to_del, what_cmp);
	}

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
		if (what_cmp == ID_SEARCH)
		{
			root->right = deleteNode(root->right, temp->value->id2, what_cmp);
		}
		else
		{
			root->right = deleteNode(root->right, temp->value->city, what_cmp);
		}
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

/* int height(TreeNode*)
 * Returns the height of the given tree
 */
int height(TreeNode *t)
{

	if (t == NULL)
	{
		return -1;
	}
	return (1 + max(height(t->left), height(t->right)));
}

/* void print_inorder(TreeNode*)
 * Prints the elements of the given tree inorder
 */
void print_inorder(TreeNode *root)
{
	if (root != NULL)
	{
		print_inorder(root->left);
		printAirport(root->value);
		print_inorder(root->right);
	}
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