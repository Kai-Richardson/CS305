/* selection sort
   using an array
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

// function prototypes
void printArray(Item arr[], int length);
void selectionSort(Item a[], int l, int r);
void swap(Item *p1, Item *p2);

/* main
   creates data, sorts it, and prints it
*/
int main(int argc, char * argv[]) {

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
  Item arr[] = {"Eve", "Poindexter", "Nathan", "Pandora", "Mo", "Marshall",
		"Adam"};
  int len = sizeof(arr)/sizeof(*arr);
#endif

  // print array before sorting
  printf("================ before sorting ================\n");
  printArray(arr, len);

  // sort the array
  selectionSort(arr, 0, len-1);

  // print the array after sorting
  printf("================ after sorting ================\n");
  printArray(arr, len);
}

/* printArray prints first 20 and last 20 items
   Parameters:
   - arr: the array to print
   - length: length of the array
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

/* selectionSort
 Parameters:
 - arr: the array
 - l: the left index of the range we're sorting
 - r: the right index of the range we're sorting
*/
void selectionSort(Item a[], int l, int r) {
  int i, j;

  // start at left, finding correct element
  for (i = l; i< r; i++) {
    // location of minimum element found so far on this iteration
    int minIdx = i;
    // loop through to find a
    for (j = i+1; j <= r; j++) {
	if (less(a[j], a[minIdx])) minIdx = j;
    }
    swap(&a[i], &a[minIdx]); // swap the "small" element into right spot
  }
}

/* swap -- exchanges the values of two pointers
   Parameters:
   - p1: pointer to first value
   - p2: pointer to second value
*/
void swap(Item *p1, Item *p2) {
  Item temp = *p1;
  *p1 = *p2;
  *p2 = temp;
}
