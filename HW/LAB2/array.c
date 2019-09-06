#include <stdio.h>
#include <stdlib.h>

/* CS305, lab 2 */

extern void abc(int *x);
extern void abc(int x[20]);
extern void abc(int x[]);

void abc(int x[3]) {
  printf("inside abc: size is %d\n", sizeof(x));
}

int main() {
  int y[15];
  printf("outside abc: size is %d\n", sizeof(y));
  abc(y);
  return EXIT_SUCCESS;
}
