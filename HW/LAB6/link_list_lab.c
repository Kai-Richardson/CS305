/**************************************************
 * CS 305
 * Lab on linked lists
 * Implements a linked list of ints and some operations
 * on the list
 * Authors: Tammy VanDeGrift, Martin Cenek
 **************************************************/
#include <stdlib.h>
#include <stdio.h>

typedef struct nodeTag Node;

/* similar to the textbook -- a Node represents one node in the linked list */
struct nodeTag {
  int num; 	// value stored in node
  Node * next; 	// pointer to next node in list
};

// book also defines Node * as NodePtr
// A better practice is to use type Node * instead of NodePtr for the reminder
// of the pointer type

/* function prototypes on linked lists from lecture */
Node * makeNode(int n, Node * nextItem);
int    length(Node * list);
void   print(Node * list);
void   insertTail(int n, Node ** list);
Node * find(int n, Node * list);
int    delete(Node * toDelete, Node ** listPtr);
void   insertHead(int n, Node ** list);
int    numPos(Node * list);

/* function prototypes on linked lists for lab */
int    lengthRec(Node * list);
void   freeList(Node * list);
Node * copyList(Node * list);
Node * mergeList(Node * list1, Node * list2);

/* main function */
int main(void) {
  // LAB EXERCISE: update main to test the new functions
  Node * lst1 = NULL;
  Node * lst2 = NULL;

  insertHead(8, &lst1);
  insertHead(7, &lst1);
  insertHead(5, &lst1);
  insertHead(4, &lst1);
  insertHead(2, &lst1);

  printf("lst1 length: %d\n", length(lst1));
  printf("lst1 length (rec): %d\n", lengthRec(lst1));

  insertHead(25, &lst2);
  insertHead(21, &lst2);
  insertHead(20, &lst2);
  insertHead(15, &lst2);
  insertHead(13, &lst2);
  insertHead(10, &lst2);
  insertHead(7, &lst2);
  insertHead(4, &lst2);

  printf("lst2 length: %d\n", length(lst2));
  printf("lst2 length (rec): %d\n", lengthRec(lst2));

  Node * lst3 = copyList(lst1);
   printf("cpy: ");
  print(lst3);

  Node * mergedList = mergeList(lst1, lst2);
  printf("Merged List: ");
  print(mergedList);

  freeList(lst1);
  freeList(lst2);
  freeList(lst3);
  freeList(mergedList);

  return EXIT_SUCCESS;

}
/*********** function definitions new for lab *****/

/* lengthRec
 * parameter -- list
 * returns the length of the list (# nodes)
 */
int lengthRec(Node * list) {
  if(list == NULL) {
    return 0;
  } else {
    return lengthRec(list->next) + 1;
  }
}

/* freeList
 * parameter -- list
 * frees all nodes in the list
 */
void freeList(Node * list) {
  if(list == NULL) {
    return;
  } else {
    freeList(list->next);
    free(list);
  }
}

/* copyList
 * parameter -- list
 * returns a copy of the list
 */
Node * copyList(Node * list) {
  if(list == NULL) {
    return NULL;
  } else {
    return makeNode(list->num, copyList(list->next));
  }
}

/* mergeList
 * parameters: list1 and list 2
 * merges the two lists, keeping the values in ascending order
 * NOTE: only works if list1 and list2 are sorted
 */
Node * mergeList(Node * list1, Node * list2) {
  if (list1 == NULL) {
    return copyList(list2);
  } else if (list2 == NULL) {
    return copyList(list1);
  } else if (list1->num < list2->num) {

    return makeNode(list1->num, mergeList(list1->next, list2));

  } else {

    return makeNode(list2->num, mergeList(list1, list2->next));

  }
}


/********************* function definitions from lecture ****/

/* makeNode
 * parameters -- n (the number to store in the node)
 *            -- nextItem (the next link of the node)
 * slightly different than textbook version */
Node * makeNode(int n, Node * nextItem) {
  Node * ret = (Node * ) malloc(sizeof(Node));
  ret->num = n;
  ret->next = nextItem;
  return ret;
}

/* length
 * parameter -- list (the linked list)
 * returns the length (# nodes) in the linked list
 * implemented iteratively */
int length(Node * list) {
  int len = 0;
  while(list != NULL) {
    len++;
    list = list->next;
  }
  return len;
}

/* print
 * parameter -- list (the linked list)
 * prints the values of the nodes (in order) of the list
 */
void print(Node * list) {
  printf("Linked list contents: ");
  while(list != NULL) {
    printf("%d ", list->num);
    list = list->next;
  }
  printf("\n");
}

/* insertTail
 * parameters -- n (the value of the node to insert)
 *            -- list (the linked list)
 * inserts new node at the end with value n
 * note: this is done by passing the pointer to list, so
 * when the function returns, the list object that was
 * passed to this function has been altered
 */
void insertTail(int n, Node ** listPtr) {
  Node * list = *listPtr;
  if(list == NULL) {
    // create a 1-node list
    *listPtr = makeNode(n, NULL);
    return;
  }
  while(list != NULL) {
    if(list->next == NULL) {
      // insert new node here since we found the last node
      list->next = makeNode(n, NULL);
      return;
    }
    list = list->next;
  }
}

/* find
 * parameters -- n (the value to search for)
 *            -- list (the linked list)
 * returns a pointer to the first node found with value n
 * if no such value is found, returns NULL
 */
Node * find(int n, Node * list) {
  while(list != NULL) {
    if(list->num == n) {
      return list;
    }
    list = list->next;
  }
  // no node with value n found
  return NULL; // or could return list, since list has value NULL
}

/* delete
 * parameters -- toDelete (the node to find and delete)
 *            -- listPtr (pointer to the list)
 * note: must pass listPtr in case the first element of the list
 * is deleted -- passing the list by reference, so the address
 * to the first item in the list can get updated if necessary
 *
 * returns 0 if no item found and deleted
 * returns 1 if a node is deleted
 */
int delete(Node * toDelete, Node ** listPtr) {
  Node * list = *listPtr;  // list is the linked list
  // case: either toDelete or list is null -- will not be deleting
  if(toDelete == NULL || list == NULL) {
    return 0;  // indicates no change to the list
  }

  // special case: toDelete is first node in list
  if(toDelete == list) {
     *listPtr = list->next;   // now list->next becomes first node in list
                              // returning new first address via pointer
     free(toDelete);
    return 1;  // indicates that a node was deleted
  }

  // case: need to find toDelete somewhere other than first node in list
  Node * before = list;
  list = list->next;
  while(list != NULL) {
    if(toDelete == list) {
      // redo pointers and then free memory
      before->next = list->next;
      free(list);
      return 1;
    }
    before = list;  // update for next iteration
    list = list->next;
  }
  return 0;  // toDelete not found
}

/* insertHead
 * parameters -- n (the value of the new node)
 *            -- listPtr (a pointer to the linked list for the insertion)
 *
 * inserts the new node at the front of the list
 */
void insertHead(int n, Node ** listPtr) {
  // create new node
  *listPtr = makeNode(n, *listPtr);
}

/* numPos
 * parameters -- list (list to search)
 *
 * returns the number of positive ints in the list
 */
int numPos(Node * list) {
  int countPos = 0;
  if(list == NULL) {
    return 0;
  }
  while(list != NULL) {
    if(list->num > 0) {
      countPos++;
    }
    list = list->next;
  }
  return countPos;
}

