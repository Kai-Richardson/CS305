//#define DEBUG 1
#include <stdio.h>

#ifndef AUTHOR
    #define AUTHOR "Captain Fantastic"
#endif

#ifndef ARRAYCONTENTS
    #define ARRAYCONTENTS {3,5,7,9,2,3,5,6,-6,8}
#endif

/* define swap macro */
#define swap(arr,a,b) \
  int temp = arr[a]; \
  arr[a] = arr[b]; \
  arr[b] = temp;

/* the array we're sorting */
int myArray[] =  ARRAYCONTENTS;

/* sorting function
   - parameters:
   - anArray: the array we're sorting
   - length: the number of elements in the array
*/

/* This is an implementation of selection sort */
void sort(int anArray[], int length) {

  /* for each position, find the element that belongs there */
  int i; /* outer-loop index */
  for (i = 0; i < length; i++) {
    /* index of smallest value so far */
#if DEBUG
    printf("Value of i: %d, array value at position %d is %d\n", i, i, anArray[i]);
#endif
    int bestIdx = i;

    /* find the position of the smallest element not yet placed */
    int j; /* inner-loop index */
    for (j = i+1; j < length; j++) {
      if (anArray[j] < anArray[bestIdx]) {
	/* found better value: update index */
#if DEBUG
	printf("Found smaller value, %d, at position %d; updating bestIdx\n", anArray[j], 
	       j);
#endif
	bestIdx = j;
      }
    }

    /* swap element at position 'i' with one that belongs there */
#if DEBUG
    printf("Swapping %d at position %d with %d at position %d\n", anArray[bestIdx],
	   bestIdx, anArray[i], i);
#endif
    swap(myArray, i, bestIdx);
  }
}

/* main function
     - parameters:
     - argc: number of command-line arguments
     - argv: the array of command-line arguments
*/
int main(int argc, char* argv[]) {

  /* print author */
  printf("Sorting program by ... %s\n", AUTHOR);

  /* sort the elements */
  sort(myArray, sizeof(myArray)/sizeof(*myArray));

  /* print the elements */
  int i;
  for (i = 0; i < sizeof(myArray)/sizeof(*myArray); i++) {
    printf("%d\n", myArray[i]);
  }
}
