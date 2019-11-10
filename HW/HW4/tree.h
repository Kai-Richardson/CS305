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

TreeNode *newNode(airport *value);
//TreeNode *deleteNodeID(TreeNode *root, char *id_to_del);
void deleteByID(char *to_del, TreeNode ** tptr);
TreeNode *insert(TreeNode *root, airport *value, int what_cmp);
TreeNode *findByID(TreeNode *root, char *id_to_find);
void printByCity(TreeNode *root, char *city_to_find);
int compareport(TreeNode *node, airport *port, int what_cmp);
void freeTree(TreeNode *root);

#endif