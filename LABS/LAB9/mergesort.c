/* merge sort
   using a linked list
   AUTHOR: Steven Vegdahl, Tammy VanDeGrift, Martin Cenek
   CS 305
*/

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DO_INT 1
#define LARGE 1

#if DO_INT
   typedef int Item;
   #define less(a,b) ((a)<(b))
   #define format "%d"
#else
   typedef char *Item;
   #define less(a,b) (strcmp((a),(b))<0)  // alphabetical
   //  #define less(a,b) (strcmp((a+1),(b+1))<0) // alphabetic, starting w/2nd
   //  #define less(a,b) (strlen(a)<strlen(b)) // length
   #define format "%s"
#endif

// linked list node type, patterned after book
typedef struct nodeTag node;
struct nodeTag {
  Item item;
  node *next;
};

// function prototypes
node* listMergesort(node* lst);
node* createList(Item arr[], int len);
int listLength(node* lst);
void printList(node *list);
static node* helpListMergesort(node* lst, int len);
static node* merge(node* lst1, node* lst2);

// Function main() - create, sort and print a list
//
int main(int argc, char * argv[]) {
#if DO_INT
#if LARGE
  srand(time(NULL));
  if(argc != 2) {
    printf("Usage: %s numToGenerate\n", argv[0]);
    return EXIT_FAILURE;
  }
  int len = atoi(argv[1]);
  int i;
  node *list = NULL;
  for (i = 0; i < len; i++) {
    node *newNode = malloc(sizeof(node));
    newNode->item = rand();
    newNode->next = list;
    list = newNode;
  }
#else
  Item arr[] = {3,4,-2,8,45,118,86,24,67};
  // create the initial list
  int len = sizeof(arr)/sizeof(*arr);
  node *list = createList(arr, len);
#endif
#else
  Item arr[] = {"Eve", "Poindexter", "Nathan", "Pandora", "Mo", "Marshall",
		"Adam"};
  // create the initial list
  int len = sizeof(arr)/sizeof(*arr);
  node *list = createList(arr, len);
#endif

  // print list before sorting
  printf("================ before sorting ================\n");
  printList(list);

  // sort the list
  list = listMergesort(list);

  // print the list after sorting
  printf("================ after sorting ================\n"); 
  printList(list);
}

// Function: listMergesort()
//
// Parameter:
// - lst: a pointer to the first node in the list
//
// Result:
// - a pointer to the first node in the sorted version of the list
//
// Description:
//   Sorts the list by modifying the pointers of the nodes in a list so
//   that they are in sorted order.
//
node* listMergesort(node* lst) {
  // compute length of list for use in helper-function
  int len = listLength(lst);
  // call helper-function to sort the list
  return helpListMergesort(lst, len);
}

// Function: helpListMergesort
//
// Parameters:
// - lst: a pointer to the first node in the list
// - len: the length of the list, which must be at least one
//
// Result:
// - a pointer to the first node in the sorted version of the list
//
// Description:
//   Sorts the list by modifying the pointers of the nodes in a list so
//   that they are in sorted order.
//
static node* helpListMergesort(node* lst, int len) {
  // base case: list length zero or 1: simply return the list
  if (len <= 1) return lst;

  // split the list in to two halves; if number of elements is
  // odd, first half will be one longer
  node* firstHalf = lst;
  node* secondHalf;
  int lenTemp = len-2; // account for wanting to be one behind
  while (lenTemp > 0) {
    lst = lst->next;
    lenTemp -= 2;
  }
  secondHalf = lst->next;
  lst->next = NULL; // null out end of first list: "clean split"

  // sort each half
  firstHalf = helpListMergesort(firstHalf, (len+1)/2);
  secondHalf = helpListMergesort(secondHalf, len/2);

  // merge the sorted lists
  return merge(firstHalf, secondHalf);
}
    
// Function: merge
//
// Parameters:
// - lst1: a pointer to the first node in the first list
// - lst2: a pointer to the first node in the second list
//
// Result:
// - a pointer to the first node in the sorted, merged list
//
// Description:
//   Merges two sorted lists into a single sorted list.
//
static node* merge(node* lst1, node* lst2) {
  // the resulting list
  node* result; // it will be initialized below

  // end-of-list location, where we'll add the always add next-smallest element
  node** lastSpot = &result;

  // repeatedly remove the smallest front element of the two lists and add it
  // to the end of the new list, until one of the original lists becomes empty;
  // at that point tack the remaining (non-empty list) onto the end of
  // the new list
  for (;;) {
    if (lst1 == NULL) {
      // first list is empty; tack the second list onto the end of the new list
      *lastSpot = lst2;
      break;
    }
    else if (lst2 == NULL) {
      // second list is empty; tack the first list onto the end of the new list
      *lastSpot = lst1;
      break;
    }
    else {
      // neither list empty
      if (less(lst1->item, lst2->item)) {
	// first list has smallest element: remove it from the first list
	// and push it onto the end of the new list
	*lastSpot = lst1; // put element at front of new list
	lastSpot = &lst1->next; // "end of list" pointer is now end of added one
	lst1 = lst1->next; // remove element from first list
      }
      else {
	// second list has smallest element: remove it from the second list
	// and push it onto the end of the new list
	*lastSpot = lst2; // put element at front of new list
	lastSpot = &lst2->next; // "end of list" pointer is now end of added one
	lst2 = lst2->next; // remove element from first list
      }
    }
  }
  return result;
}

// Function createList() - creates a list from the elements in an array
//
// Parameters:
// - arr: the array containing the elements
// - len: the length of the array
//
// Result:
//   a pointer to the first element of a newly allocated linked list,
//   containing the data values in the array, and in the same order.
//
node *createList(Item arr[], int len) {
  // the (eventual) completed list
  node *rtnVal = NULL;

  // Go through the array in reverese order, inserting elements into the
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

// Function listLength() - counts the elements in a list
// Parameter:
// - list: the list to print
// Returns:
//   the length of the list
int listLength(node* lst) {
  int rtnVal = 0;
  for (lst = lst; lst != NULL; lst = lst->next) {
    rtnVal++;
  }
  return rtnVal;
}


// Function: printList() - prints the elements in a list, but if longer than
// 20, prints only the first 10 and last 10
//
// Parameter:
// - list: the list to print
void printList(node *list) {
  // determine the length
  int len = listLength(list);

  if (len <= 20) {
    node* p = list;
    for (p = list ; p != NULL; p = p->next) {
      printf(format " ", p->item);
    }
  }
  else {
    node* p;
    int i;
    for (i = 0, p = list ; i < 10; i++, p = p->next) {
      printf(format " ", p->item);
    }
    for (; i < len-10; i++, p = p->next) {
    }
    printf("... ");
    for (; p != NULL; p = p->next) {
      printf(format " ", p->item);
    }
  }
  // terminate with newline
  printf("\n");
}

