#include <stdio.h>
#include <unistd.h>

/* for lab on gdb
* Computes n factorial (n!) using a recursive
* algorithm. This program contains an intentional error.
*/

/* prototype for "factorial" */
int factorial(int);

/* our "main" function, where execution begins */
/* gets number from command line or input file and prints the factorial*/
int main (int argc, char *argv[]) {
  /* variable for reading number into */
  int n;

  /* if reading number from keyboard, print prompt onto screen */
  if (isatty(0)) fprintf(stderr, "please type a number: ");

  /* read the number */
  scanf("%d", &n);

  /* if number is out of range, exit with an error status, otherwise,
     compute and print the result */
  if (n < 0 || n > 12) {
    fprintf(stderr, "Number out of range.\n");
    return 1;
  }
  else {
    printf("%d! is %d\n", n, factorial(n));
  }
}

/* recursive factorial function */
int factorial(int n) {
  if ((n == 1) || (n == 0)) {
    // if n is zero or one, return a 1
    return 1;
  }
  else {
    // otherwise, multiply n by the result of (n-1)!
    return n * factorial(n-1);
  }
}
