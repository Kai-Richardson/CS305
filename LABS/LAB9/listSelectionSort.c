/* selection sort
   using a linked list
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
node *listSelectionSort(node *h);
static node *findmax(node *header);
node *createList(Item arr[], int len);
void printList(node *list);
void freeList(node *list);

// Function main() - create, sort and print a list
//
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
  list = listSelectionSort(list);

  // print the list after sorting
  printf("================ after sorting ================\n"); 
  printList(list);
  freeList(list);
}

/* Function: listSelectionSort()

 Parameter:
 - h: the first node in the list

 Result:
 - a pointer to the first node in the sorted version of the list

 Description:
   Sorts the list by modifying the pointers of the nodes in a list so
   that they are in sorted order.
*/
node *listSelectionSort(node *h) {
  // set dummy node, so h is pointing "one back"
  node dummy;
  dummy.next = h;
  h = &dummy;

  // our resulting list
  node *out = NULL;

  // keep extracting values until (non-dummy) portion of list
  // is empty
  while (h->next != NULL) {
    // find the node behind the one with the largest value
    node *max = findmax(h);	

    // extract the max-value node from the list
    node *t = max->next;
    max->next = t->next;

    // insert max-value node into the front of the result-list
    t->next = out;
    out = t;
  }

  // return the final list
  return out;
}

/* Function findmax() - helper function to find largest element in list

 Parameter:
 - pointer to a dummy node whose 'next' field is a pointer to the
   head of the linked list to search

 Result:
 - pointer to the node whose 'next' field points to the element with the
   largest data value in the list

 Preconditions:
   It is assumed that neither header nor header->next is NULL.
*/
static node *findmax(node *header) {
  // the current maximum, set to the first element
  node *curMax = header;

  // loop through the remaining elements of the list, updating
  // 'curMax' if whenever a larger value is found
  node *t;
  for (t = header->next; t->next != NULL; t = t->next) {
    if (less(curMax->next->item, t->next->item)) {
      curMax = t;
    }
  }
  return curMax;
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

/* Function: printList() - prints the first 10 elements in a list

 Parameter:
 - list: the list to print
*/
void printList(node *list) {
  // iterate through, printing each element
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
   -list to free (frees entire list)
*/
void freeList(node *list) {
  if(list == NULL){
    return;
  }
  freeList(list->next);
  free(list);
  list = NULL;
}
