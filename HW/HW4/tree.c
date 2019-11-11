/* tree.c for CS305 HW4
 * @author - Kai Richardson
 * @date 2019-11-10
 * Note: Portions of this code were part of a previous lab assignment, but has been modified.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tree.h"

#ifndef AIRPORT_H
#include "airport.h"
#endif

/* TreeNode *newNode(airport *)
 * Returns a new node with the given airport.
 */
TreeNode *newNode(airport *value)
{
	TreeNode *newND = (TreeNode *)malloc(sizeof(TreeNode));
	newND->value = value;
	newND->left = newND->right = NULL;
	return newND;
}

/* TreeNode *minValueNode(TreeNode *)
 * Returns the node with minimum value in the tree (leftmost)
 */
TreeNode *minValueNode(TreeNode *root)
{
	TreeNode *current = root;

	//find leftmost leaf
	while (current && current->left != NULL)
		current = current->left;

	return current;
}
//////////////////////////////////////////////////////////////////////////////////////

/* deleteByID(char*, Treenode**, int, char*)
 * deletes node with data value d from the tree
 * note: this is a heavily modified version from a previous lab
 */
airport *deleteByID(char *to_del, TreeNode **tptr, int what_cmp, char *opt_city)
{
	TreeNode *curr = *tptr;	//holds ptr to current node
	TreeNode *found = NULL;	//holds ptr to found target
	TreeNode *parent = NULL;   //holds ptr to parent of target
	airport *to_return = NULL; //holds airport to return
	if (curr == NULL)
	{ // no data in tree
		return NULL;
	}
	parent = NULL;
	if (what_cmp == ID_SEARCH)
	{
		//All of this is used to circumvent the lack of multiple returns in C, while trying to keep things clean
		rootParentHolder *holder = malloc(sizeof(rootParentHolder)); //Holder for root/parent, freed once done
		holder = findByID(curr, to_del, holder);
		found = holder->root;
		parent = holder->parent;
		free(holder);
	}
	else //search by city case
	{

		while (curr != NULL)
		{
			//Depending on what type of tree, either true if id2 == del or true if id2 == to_del && city == opt_city
			if (((strncmp(opt_city, curr->value->city, MAX_STRINGLEN) == 0) && (strncmp(to_del, curr->value->id2, MAX_STRINGLEN) == 0)))

			{
				found = curr;
				break;
			}
			//Depending on what type of tree, either true if id2 < del or true if city <= opt_city
			else if (((strncmp(opt_city, curr->value->city, MAX_STRINGLEN) <= 0)))
			{
				parent = curr;
				curr = curr->left;
			}
			else
			{
				parent = curr;
				curr = curr->right;
			}
		}
	}
	if (found == NULL)
	{
		return NULL; // not found in tree
	}

	// case 1: found is a leaf (just delete the node)
	if (found->left == NULL && found->right == NULL)
	{
		// printf("case 1\n");
		// update parent's correct child
		if (parent == NULL)
		{
			// found was the only node in the tree
			to_return = found->value;
			free(found);
			*tptr = NULL;
			return to_return;
		}
		// parent is not null, so need to update its child to be null
		if (parent->left == found)
		{
			parent->left = NULL;
		}
		else if (parent->right == found)
		{
			parent->right = NULL;
		}
		else
		{
			printf("something went wrong: parent has invalid children\n");
			return NULL;
		}
		to_return = found->value;
		free(found);
		return to_return;
	}

	// case 2: found is an interior node with just one child on right side
	if (found->left == NULL)
	{
		// printf("case 2:\n");
		// determine if found is left or right child of parent
		if (parent->left == found)
		{
			parent->left = found->right;
		}
		else if (parent->right == found)
		{
			parent->right = found->right;
		}
		else
		{
			printf("something went wrong: parent has invalid children\n");
			return NULL;
		}
		to_return = found->value;
		free(found);
		return to_return;
	}

	// case 3: found is an interior node with just one child on the left side
	if (found->right == NULL)
	{
		// printf("case 3:\n");
		// determine if found is left or right child of parent
		if (parent->left == found)
		{
			parent->left = found->left;
		}
		else if (parent->right == found)
		{
			parent->right = found->left;
		}
		else
		{
			printf("something went wrong: parent has invalid children\n");
			return NULL;
		}
		to_return = found->value;
		free(found);
		return to_return;
	}

	// case 4: found is an interior node with two children
	// find next larger element in tree (go right, then go left as far as
	// possible)
	// printf("case 4:\n");
	TreeNode *traverse = found->right;
	TreeNode *traverseParent = found;

	to_return = found->value;
	// now go left until reach a node with no left child
	while (traverse->left != NULL)
	{
		traverseParent = traverse;
		traverse = traverse->left;
	}
	// at this point traverse should be the next largest node in the tree
	found->value = traverse->value; // put data in found
	// check if traverse is a leaf node
	if (traverse->left == NULL && traverse->right == NULL)
	{
		// leaf node -- just delete it
		if (traverseParent->left == traverse)
		{
			traverseParent->left = NULL;
			free(traverse);
		}
		else if (traverseParent->right == traverse)
		{
			traverseParent->right = NULL;
			free(traverse);
		}
		else
		{
			printf("something went wrong: parent of traversed node has invalid children");
			return NULL;
		}
		return to_return;
	}
	// traverse has a right subtree
	if (traverse->left == NULL && traverse->right != NULL)
	{
		if (traverseParent->left == traverse)
		{
			traverseParent->left = traverse->right;
			free(traverse);
		}
		else if (traverseParent->right == traverse)
		{
			traverseParent->right = traverse->right;
			free(traverse);
		}
	}
	return to_return;
	// that is all the cases
}

/* TreeNode *insert(TreeNode *, airport *, int)
 * Inserts the given value into the given tree (and tree type) and returns the head back.
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

/* rootParentHolder *findByID(TreeNode *, char *, rootParentHolder *)
 * Finds the given TreeNode with id equal to passed char and returns it and its parent
 */
rootParentHolder *findByID(TreeNode *root, char *id_to_find, rootParentHolder *to_set)
{

	//Root is either NULL or our target from prev. recursions
	if (root == NULL || (strncmp(root->value->id2, id_to_find, MAX_STRINGLEN) == 0))
	{
		to_set->root = root;
		return to_set;
	}

	//else, there's stuff in the tree
	if (strncmp(root->value->id2, id_to_find, MAX_STRINGLEN) < 0)
	{
		to_set->parent = root;
		return findByID(root->left, id_to_find, to_set);
	}
	else
	{
		to_set->parent = root;
		return findByID(root->right, id_to_find, to_set);
	}
}

/* TreeNode *printByCity(TreeNode *, char *)
 * Finds/prints all Nodes with given value of city
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