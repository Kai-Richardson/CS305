/* CS 305 Lab: Trees
 * Tree code definitions
 * Tammy VanDeGrift
 * tree.c
 */
#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

/* function definitions for binary search trees */

/* newTreeNode
 * helper function, creates a new tree node with value d
 * returns the address of the new node
 */
TreeNode * newTreeNode(TreeData d) {
  TreeNode * toReturn = (TreeNode *) malloc(sizeof(TreeNode));
  toReturn->value = d;
  toReturn->left = NULL;
  toReturn->right = NULL;
  return toReturn;
}

/* createTree
 * creates a binary search tree with data stored in array a
 */
TreeNode * createTree(TreeData a[], int size) {
  if(size <= 0) {
    return NULL;
  }
  TreeNode * toReturn = newTreeNode(a[0]); // insert first item from list
  int i;
  for(i = 1; i < size; i++) {
    insert(a[i], &toReturn);
  }
  return toReturn;
}

/* insert
 * inserts data item d into tree; note that this is a BST so it is ordered
 */
void insert(TreeData d, TreeNode ** tptr) {
  // create new node for data
  TreeNode * toInsert = newTreeNode(d);
  TreeNode * curr = *tptr;
  if(curr == NULL) {
    *tptr = toInsert;  // make this the tree
    return;
  }
  // check value of t to see if new node should be to the right or left of curr
  while(curr != NULL) {
    if(d < curr->value) { // goes to left
      if(curr->left == NULL) {
	curr->left = toInsert;
	return;
      }
      // keep going left
      curr = curr->left;
    } else { // goes to right
      if(curr->right == NULL) {
	curr->right = toInsert;
	return;
      }
      // keep going right
      curr = curr->right;
    }
  }
}

/* insertR
 * inserts data item d into tree; note that this is a BST so it is ordered
 * note: this function is written recursively
 */
void insertR(TreeData d, TreeNode **tptr) {
  if(*tptr == NULL) {
    *tptr = newTreeNode(d);
  } else if(d < (*tptr)->value) {
    insertR(d, &(*tptr)->left);
  } else {
    insertR(d, &(*tptr)->right);
  }
}

/* delete
 * deletes node with data value d from the tree
 * note: passing in a pointer to the root of the tree in case the
 * root is updated
 */
void delete(TreeData d, TreeNode ** tptr) {
  TreeNode * curr = *tptr;
  TreeNode * found = NULL;
  TreeNode * parent = NULL;
  if(curr == NULL) { // no data in tree
    return;
  }
  parent = NULL;
  while(curr != NULL) {
    if(d == curr->value) {
      found = curr;
      break;
    } else if(d < curr->value) {
      parent = curr;
      curr = curr->left;
    } else {
      parent = curr;
      curr = curr->right;
    }
  }
  if(found == NULL) {
    return;   // not found in tree
  }

  // case 1: found is a leaf (just delete the node)
  if(found->left == NULL && found->right == NULL) {
    // printf("case 1\n");
    // update parent's correct child
    if(parent == NULL) {
      // found was the only node in the tree
      free(found);
      *tptr = NULL;
      return;
    }
    // parent is not null, so need to update its child to be null
    if(parent->left == found) {
      parent->left = NULL;
    } else if(parent->right == found) {
      parent->right = NULL;
    } else {
      printf("something went wrong: parent has invalid children\n");
      return;
    }
    free(found);
    return;
  }

  // case 2: found is an interior node with just one child on right side
  if(found->left == NULL) {
    // printf("case 2:\n");
    // determine if found is left or right child of parent
    if(parent->left == found) {
      parent->left = found->right;
    } else if(parent->right == found) {
      parent->right = found->right;
    } else {
      printf("something went wrong: parent has invalid children\n");
      return;
    }
    free(found);
    return;
  }

  // case 3: found is an interior node with just one child on the left side
  if(found->right == NULL) {
    // printf("case 3:\n");
    // determine if found is left or right child of parent
    if(parent->left == found) {
      parent->left = found->left;
    } else if(parent->right == found) {
      parent->right = found->left;
    } else {
      printf("something went wrong: parent has invalid children\n");
      return;
    }
    free(found);
    return;
  }

  // case 4: found is an interior node with two children
  // find next larger element in tree (go right, then go left as far as
  // possible)
  // printf("case 4:\n");
  TreeNode * traverse = found->right;
  TreeNode * traverseParent = found;
  // now go left until reach a node with no left child
  while(traverse->left != NULL) {
    traverseParent = traverse;
    traverse = traverse->left;
  }
  // at this point traverse should be the next largest node in the tree
  found->value = traverse->value;  // put data in found
  // check if traverse is a leaf node
  if(traverse->left == NULL && traverse->right == NULL) {
    // leaf node -- just delete it
    if(traverseParent->left == traverse) {
      traverseParent->left = NULL;
      free(traverse);
    } else if(traverseParent->right == traverse) {
      traverseParent->right = NULL;
      free(traverse);
    } else {
      printf("something went wrong: parent of traversed node has invalid children");
      return;
    }
    return;
  }
  // traverse has a right subtree
  if(traverse->left == NULL && traverse->right != NULL) {
    if(traverseParent->left == traverse) {
      traverseParent->left = traverse->right;
      free(traverse);
    } else if(traverseParent->right == traverse) {
      traverseParent->right = traverse->right;
      free(traverse);
    }
  }
  return;
  // that is all the cases
}

/* size
 * returns the number of nodes in the tree
 */
int size(TreeNode * t) {
  if(t == NULL) {
    return 0;
  }
  return 1 + size(t->left) + size(t->right);
}

/* visit
 * prints value of node, called in traversal functions
 */
void visit(TreeNode * t) {
  printf("%d ", t->value);
}

/* inorder
 * visits the nodes inorder (left, current, right) traversal
 */
void inorder(TreeNode * t) {
  if(t != NULL) {
    inorder(t->left);
    visit(t);
    inorder(t->right);
  }
}

/* should visit the nodes in preorder fashion */
void preorder(TreeNode * t) {
  if(t != NULL) {
    visit(t);
    preorder(t->left);
    preorder(t->right);
  }
}

/* freeTree
 * frees all memory associated with a tree and sets
 * *tptr to null
 */
void freeTree(TreeNode ** tptr) {
  if(*tptr == NULL) {
    return;
  }
  freeTree(&(*tptr)->left);
  freeTree(&(*tptr)->right);
  *tptr = NULL;
  free(*tptr);
}

/* the following 3 functions print the tree
 * for debugging and to visualize tree
 */
void printWithTab(int n, int data) {
  int i = 0;
  for(i = 0; i < n; i++) {
    printf("   ");
  }
  printf("%d\n", data);
}

void printR(int n, TreeNode * t) {
  if(t == NULL) {
    printWithTab(n, 0);  // note: value 0 is used to indicate null
    return;
  }
  printWithTab(n, t->value);
  printR(n+1, t->right);
  printR(n+1, t->left);
}

void print(TreeNode * t) {
  printf("\nTREE:\n");
  printR(0, t);
}


/************************* LAB activites ********************/

/* helper function, returns the maximum of two ints */
int max(int a, int b) {
  if(a > b) return a;
  else return b;
}

/* lab activity */
/* should return the height of the tree
 * remember: the height of an empty tree is 0; otherwise, the
 * height of the tree is the max of (1+height of left subtree) and
 * (1+height of right subtree)
 */
int height(TreeNode * t) {

  if (t == NULL)
  {
    return -1;
  }
    return 1+max(height(t->left), height(t->right));
}

/* lab activity */
/* should visit the nodes in postorder fashion */
void postorder(TreeNode * t) {

  if (t == NULL) return;

  postorder(t->left);
  postorder(t->right);
  visit(t);

  return;
}

/* lab activity */
/* should return NULL if the value d is not found in the tree t
 * should return address of node if the value d is not found in the tree
 */
TreeNode * find(TreeData d, TreeNode * t) {

  if (t == NULL) return NULL;
  if (d == t->value) return t;

  find(d, t->left);
  find(d, t->right);

}

/* lab activity */
/* should return the max value found in tree (go all the way to the right)
 * if tree is empty, return -99999.
 */
TreeData findMax(TreeNode * t) {

  if (t == NULL) return -99999;

  return max(max(findMax(t->left), findMax(t->right)), t->value);
}
