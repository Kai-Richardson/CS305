/*****************************************************************
 * Program: print_num.C
 *
 * Purpose: implements/illustrates a recursive function for printing a
 *   number in an arbitrary base
 *
 * Author: Steven R. Vegdahl, modified by Tammy VanDeGrift
 *
 *****************************************************************/
#include <stdio.h>
#include <stdlib.h>

/*****************************************************************
 * print_num - prints a number in a given base
 *
 * calling sequence:
 *    print_num(val, base)
 *
 * parameters -
 *    val - the number to be printed
 *    base - the base to print it
 *
 * effect -
 *    The number is printed in the given base on the output stream.  The letters 'a'
 *    through 'z' are used to represent the "digits" 10 through 35, when applicable.
 *
 * restrictions -
 *    Only bases 2 through 36 are handled.  However, no checking is done that the
 *    base is in that range, so if you give it a bogus base, some very strange
 *    things might occur.
 *
 * example -
 *    print_num(cout, 20, 6) causes a "32" to be printed to standard output (because
 *    32 in base 6 is 20 (3*6 + 2*1).
 *
 * implementation -
 *    If the number is smaller than the base, its character-value is looked up in a table
 *    and is printed directly.  Otherwise, the number is divided by the base and printed
 *    (recursively); then the last digit is printed (recursively).
 *
 *****************************************************************/
void print_num(int val, int base) {
  /* this array is used to translate between number values and digit-characters */
  char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
  if (val < 0) {
    /* BASE CASE: val < 0, so print a minus sign and then call
       print_num on -val and base */
    printf("-");   // fix this by adding recursive call
    print_num(-val, base);
  }
  else if (val < base) {
    /* BASE CASE: val is less than base, so print digits[val] */
    printf("%c", digits[val]);

  }
  else {
    /* RECURSIVE CASE: val >= base, so print quotient and then
     remainder */
    // this case works
    int quotient = val / base;
    int remainder = val % base;
    print_num(quotient, base);
    print_num(remainder, base);
  }
}

/*****************************************************************
 * main - main program to exercise 'print_num'
 *
 * This program prompts the user for a number, and then prints the number in bases
 * 2 through 36.
 *
 *****************************************************************/
int main(int argc, char *argv[]) {
  int i;
  /* prompt user and read number */
  int val;
  printf("Please type a number: ");
  scanf("%d", &val); //note: does not do error-checking

  /* print the number in all bases from 2 through 36 */
  for (i = 2; i <= 36; i++) {
    printf("The number base %d is ", i);
    print_num(val, i);
    printf("\n");
  }
  return EXIT_SUCCESS;
}
