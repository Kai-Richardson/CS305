#include <stdio.h>
#include <stdlib.h>

/* CS 305, lab 2
   shows how pointers can access memory outside array boundaries */
int main() {
  /* create 2 arrays */
  int b[4] = {100, 101, 102, 103};
  int a[8] = {1, 2, 3, 4, 5, 6, 7, 8};

  int *ap = a;
  int *bp = b;
  int i = 0;

  /* add too many to ap */
  ap = ap + 10;
  printf("value of *ap: %d\n", *ap);

  /* subtract from *ap */
  ap = ap - 5;
  printf("value of *ap: %d\n", *ap);

  /* subtract from bp */
  bp = bp - 2;
  printf("value of *bp: %d\n", *bp);

  /* print values for a[0] to a[25] - add your code here */


  /* end your code here */

  return EXIT_SUCCESS;
}
