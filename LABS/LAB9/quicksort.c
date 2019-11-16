/* quicksort
   uses an array to store the data
   AUTHOR: Steven Vegdahl, Tammy VanDeGrift, Martin Cenek
   CS 305
*/
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
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
void swap(Item *p1, Item *p2);
void printArray(Item arr[], int length);
int partition(Item a[], int l, int r);
void quicksort(Item a[], int l, int r);


int main(int argc, char *argv[]) {
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
  quicksort(arr, 0, len-1);

  // print the array after sorting
  printf("================ after sorting ================\n"); 
  printArray(arr, len);
}

/* quicksort
   parameters:
   - a: the array we're sorting
   - l: the leftmost index of the portion we're sorting
   - r: the rightmost index of the portion we're sorting
*/ 
void quicksort(Item a[], int l, int r) {
  int i;
  // if there are one or fewer elements in the range, just return
  if (r <= l) return;

  // partition the array; i is the location of the "split"
  i = partition(a, l, r);

  // sort the left half (small elements)
  quicksort(a, l, i-1);

  // sort the right half (large elements)
  quicksort(a, i+1, r);
}

/* partition
   parameters:
   - a: the array we're sorting
   - l: the leftmost index of the portion we're sorting
   - r: the rightmost index of the portion we're sorting
   - returns the index in the array of the "split"
*/
int partition(Item a[], int l, int r) {
  // artificially start i out one lower than our range
  int i = l-1;
  // j starts at our rightmost element
  int j = r;

  // our pivot-element is the rightmost element
  Item v = a[r];

  // At this point we're looking at the array in the range l..r-1.
  // We'll look for:
  // - a larger-or-equal-pivot-element starting from the left, and
  // - a smaller-or-equal-pivot-element starting from the right
  // Then we'll swap those two elements.
  // 
  // We'll stop when our indices meet.

  for (;;) {
    // find a larger-than-pivot element starting from the left
    while (less(a[++i], v));
    // find a smaller-or-equal-than-pivot element starting from the right
    // (need to check for lower index bound, since we don't know
    // there is such an element)
    while (less(v, a[--j])) if (j == l) break;
    // if i and j have met, we're done with the loop
    if (i >= j) break;
    // exchange the elements at i and j
    swap(&a[i], &a[j]);
  }

  // at this point, the only problem is that our pivot is the rightmost
  // element, so swap into the pivot-position
  swap(&a[i], &a[r]);

  // return the index of the pivot-position
  return i;
}

/* printArray
   parameters:
   - arr: the array to print (only prints first 10 and last 10)
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

/* swaps elements in two locations
   Parameters:
   -p1: pointer to first element
   -p2: pointer to second element
*/
void swap(Item *p1, Item *p2) {
  Item temp = *p1;
  *p1 = *p2;
  *p2 = temp;
}
