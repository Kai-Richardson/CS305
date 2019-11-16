/* insertion sort
   using linked list
   AUTHOR: Steven Vegdahl, Tammy VanDeGrift, Martin Cenek
   CS 305
*/

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// do we sort ints or strings?
#define DO_INT 1
#define LARGE 1

#if DO_INT
  // sort ints, so:
  // - type Item is int
  // - comparison is <
  // - formatting string is "%d"
  typedef int Item;
  #define less(a,b) ((a)<(b))
  #define format "%d"
#else
  // sort strings, so:
  // - type Item is char*
  // - comparison is based in strcmp
  // - formatting string is "%s"
  typedef char *Item;
  #define less(a,b) (strcmp((a),(b))<0)  // alphabetical
//  #define less(a,b) (strcmp((a+1),(b+1))<0) // alphabetic, starting w/2nd
//  #define less(a,b) (strlen(a)<strlen(b)) // length
  #define format "%s"
#endif

// linked list node type
typedef struct nodeTag node;
struct nodeTag {
  Item item;
  node *next;
};

// function prototypes
node *listInsertionSort(node* h);
node *createList(Item arr[], int len);
void printList(node *list);
void freeList(node *list);

/* Function main() - create, sort and print a list
 */
int main(int argc, char * argv[]) {
  // initial data, depending on whether we're doing ints or strings
#if DO_INT
#if LARGE
  srand(time(NULL));
  if(argc != 2) {
    printf("Usage: %s numToGenerate\n", argv[0]);
    return EXIT_FAILURE;
  }
  int len = atoi(argv[1]);
  Item* data = malloc(len*sizeof(Item));
  int i;
  for (i = 0; i < len; i++) {
    data[i] = rand();
  }

#else
  Item data[] = {3,4,-2,8,45,118,86,24,67};
  int len = sizeof(data)/sizeof(*data);
#endif
#else
  Item data[] = {"Eve", "Poindexter", "Nathan", "Pandora", "Mo", "Marshall",
		"Adam"};
  int len = sizeof(data)/sizeof(*data);
#endif
  // create the initial list
  node *list = createList(data, len);

  // print list before sorting
  printf("================ before sorting ================\n");
  printList(list);

  // sort the list
  list = listInsertionSort(list);

  // print the list after sorting
  printf("================ after sorting ================\n"); 
  printList(list);
}

/* Function: listInsertionSort()

 Parameter:
 - h: a pointer to the first node in the list

 Result:
 - a pointer to the first node in the sorted version of the list

 Description:
   Sorts the list by modifying the pointers of the nodes in a list so
   that they are in sorted order.
*/
node *listInsertionSort(node *h) {
  // unsorted list: contains the original elements
  node* a = h;
  // to-be sorted list: we'll insert things into this one
  node* b = NULL;
  // loop-iteration variable
  node** spot;

  // as long as the unsorted list has elements, removed an element, and
  // insert it into the right place in the sorted list
  while (a != NULL) {
    node *myNode = a; // the node we're inserting into new list
    a = a->next; // set up for next iteration
    // find the right spot for the node
    for (spot = &b;
	 *spot != NULL && !less(myNode->item, (*spot)->item);
	 spot = &(*spot)->next) {
    }

    // at this point, spot points to the location where we need to insert
    // the node
    // do pointer-moves to insert node into position
    myNode->next = *spot;
    *spot = myNode;
  }

  // return the final list
  return b;
  freeList(a);
  freeList(b);
}

/* Function createList() - creates a list from the elements in an array

 Parameters:
 - arr: the array containing the elements
 - len: the length of the array

 Result:
   a pointer to the first element of a newly allocated linked list,
   containing the data values in the array, and in the same order.
*/
node *createList(Item arr[], int len) {
  // the (eventual) completed list
  node *rtnVal = NULL;

  // Go through the array in reverse order, inserting elements into the
  // front of the list.  This will create a list whose data is in the
  // same order as the array.
  int i;
  for (i = len-1; i >= 0; i--) {
    // create node for current data; insert into front
    node *newNode = malloc(sizeof(node));
    newNode->item = arr[i];
    newNode->next = rtnVal;
    rtnVal = newNode;
  }

  // return the resulting list
  return rtnVal;
}

/* Function: printList() - prints the elements in a list

 Parameter:
 - list: the list to print
*/
void printList(node *list) {
  // iterate through, printing only first 10 elements
  node *p;
  int count = 0;
  for (p = list; p != NULL && count < 10; p = p->next) {
    printf(format " ", p->item);
    count++;
  }
  // terminate with newline
  printf("\n");
}

/* freeList
   Parameter:
   - list: list to free (frees entire list)
*/
void freeList(node *list) {
  if(list == NULL) {
    return;
  }
  freeList(list->next);
  free(list);
  list = NULL;
}
