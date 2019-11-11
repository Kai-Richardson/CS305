#ifndef TREE_H
#define TREE_H

#ifndef AIRPORT_H
#include "airport.h"
#endif

#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

#define ID_SEARCH 0
#define CITY_SEARCH 1

typedef struct TreeNode
{
	airport *value;
	struct TreeNode *left, *right;
} TreeNode;

//Used for findByID (circumventing lack of multiple returns)
typedef struct rootParentHolder
{
	TreeNode *root, *parent;
} rootParentHolder;

TreeNode *newNode(airport *value);
airport *deleteByID(char *to_del, TreeNode ** tptr, int what_cmp, char *opt_city);
TreeNode *insert(TreeNode *root, airport *value, int what_cmp);
rootParentHolder *findByID(TreeNode *root, char *id_to_find, rootParentHolder *to_set);
void printByCity(TreeNode *root, char *city_to_find);
int compareport(TreeNode *node, airport *port, int what_cmp);
void freeTree(TreeNode *root);

#endif