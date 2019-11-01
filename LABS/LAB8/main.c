/* CS 305 Lab Starter
 * program to test tree code
 * Tammy VanDeGrift
 * main.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

/* prototypes */
void test1(void);

/* main function to test lab code */
int main(void) {
  test1();
  return EXIT_SUCCESS;
}

/* test1 -- builds BST */
void test1(void) {
  // create array of ints to insert into tree
  int arr[] = {3, 6, 2, -4, 8, 1, 7, 10, -5};
  TreeNode * tree = createTree(arr, sizeof(arr)/sizeof(*arr));
  printf("Inorder: ");
  inorder(tree);
  printf("\nPreorder: ");
  preorder(tree);
  printf("\nPostorder: ");
  postorder(tree);
  printf("\n");

  // insert more items
  insert(9, &tree);
  insertR(-2, &tree);

  printf("Inorder: ");
  inorder(tree);
  printf("\nPreorder: ");
  preorder(tree);
  printf("\nPostorder: ");
  postorder(tree);
  printf("\n");
  
  printf("\n");
  printf("Size: %d\n", size(tree));
  printf("Height: %d\n", height(tree));

  TreeNode * d = find(3, tree);
  TreeNode * e = find(0, tree);
  if(d != NULL) {
    printf("contains 3\n");
  }
  if(e != NULL) {
    printf("contains 0\n");
  }

  int max = findMax(tree);
  printf("max: %d\n", max);

  freeTree(&tree);
  return;
}
