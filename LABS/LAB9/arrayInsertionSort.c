/* insertion sort
   using array
   AUTHOR: Steven Vegdahl, Tammy VanDeGrift, Martin Cenek
   CS 305
*/

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>

#define DO_INT 1
#define LARGE 1

// operations for ints
#if DO_INT
typedef int Item;
#define less(a,b) ((a)<(b))
#define format "%d"

// operations for strings
#else
typedef char *Item;
  #define less(a,b) (strcmp((a),(b))<0)  // alphabetical
//  #define less(a,b) (strcmp((a+1),(b+1))<0) // alphabetic, starting w/2nd
//  #define less(a,b) (strlen(a)<strlen(b)) // length
#define format "%s"
#endif

// function prototypes
void printArray(Item arr[], int length);
void insertionSort(Item a[], int l, int r);

/* main
   creates data and sorts data
*/
int main(int argc, char * argv[]) {
  // create ints to sort
#if DO_INT
#if LARGE
  srand(time(NULL));
  if(argc != 2) {
    printf("Usage: %s numToGenerate\n", argv[0]);
    return EXIT_FAILURE;
  }
  int len = atoi(argv[1]);
  Item* arr = malloc(len*sizeof(Item));
  int i;
  for (i = 0; i < len; i++) {
    arr[i] = rand();
  }
#else
  Item arr[] = {3,4,-2,8,45,118,86,24,67};
  int len = sizeof(arr)/sizeof(*arr);
#endif
#else
  Item arr[] = {"Evelyn", "Peter", "Michael", "Pheobe", "Mo", "Sara", "Adam"};
  int len = sizeof(arr)/sizeof(*arr);
#endif

  // print array before sorting
  printf("================ before sorting ================\n");
  printArray(arr, len);

  // sort the array
  insertionSort(arr, 0, len-1);

  // print the array after sorting
  printf("================ after sorting ================\n");
  printArray(arr, len);
}

/* printArray
   Parameters:
   - arr: the array
   - length: length of array

   prints the array (only first ten and last ten)
 */
void printArray(Item arr[], int length) {
  int i;
  for (i = 0; i < length; i++) {
    if (i < 10 || i >= length-10) {
      if (length > 20 && i == length-10) printf("... ");
      printf(format " ", arr[i]);
    }
  }
  printf("\n");
}

/* array-based insertion sort

   Parameters:
   - arr: the array
   - l: the left index of the range we're sorting
   - r: the right index of the range we're sorting
*/
void insertionSort(Item a[], int l, int r) {
  // starting with leftmost element, insert its right neighbor
  // into the correct place in the array
  int i;
  for (i = l; i < r; i++) {
    // the neighbor that we're inserting
    Item val = a[i+1];

    // find the correct spot for the element, shifting elements
    // over that are larger
    int j;
    for (j = i; j >= l && !less(a[j], val); j--) {
      a[j+1] = a[j];
    }

    // insert our element into the correct spot
    a[j+1] = val;
  }
}
