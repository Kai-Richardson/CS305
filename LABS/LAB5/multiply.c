/*****************************************************************
 * Program: multiply.C
 *
 * Purpose: implements/illustrates a recursive version of the russian
 *   peasant's algorithm for multiplication
 *
 * Author: Steven R. Vegdahl, modified by Tammy VanDeGrift
 *
 *****************************************************************/
#include <stdio.h>
#include <stdlib.h>

/*****************************************************************
 * multiply - multiplies two non-negative numbers
 *
 * calling sequence:
 *    result = multiply(num1, num2)
 *
 * parameters -
 *    num1 and num2 - the numbers to be multiplied
 *
 * result -
 *    The product of the two numbers is returned.
 *
 * restrictions -
 *    Overflow is not properly handled
 *
 * example -
 *    Multiply(23, 20) yields the result 460.
 *
 * method -
 *    This is essentially a recursive version of the "russian peasant's algorithm".
 *    If the num1 is zero, zero is returned.  Otherwise, if the number is even, the
 *    the product of num1/2 and num2*2 is returned.  Otherwise (the number is odd)
 *    the produce of (num1/2) and (num2*2) is computed, but num2 is added to the result
 *    to compensate for the fact that the division drops the remainder.
 *
 *****************************************************************/
int multiply(int num1, int num2) {
  /* BASE CASE: num1 == 0 */
  if(num1 == 0 || num2 == 0) {
    return 0;  /*multiplying by 0 results in 0*/
  }
  /* RECURSIVE CASE: for negative valued input */
  if (num1 < 0 && num2 < 0) {
    return multiply(-num1, -num2); /* negate arguments in recursive call */
  }
  /* RECURSIVE CASE: num1 is negative and num2 is positive */
  if (num1 < 0 && num2 > 0) {
    return -multiply(-num1, num2); /* negate result */
  }
  /* RECURSIVE CASE: num1 is positive and num2 is negative */
  if (num1 > 0 && num2 < 0) {
    return -multiply(num1, -num2); /* negate result */
  }
  /* RECURSIVE CASE: for positive num1 and positive num2 */
  else {
    /* recursive case: incomplete -- fix this case*/
    int result = 0;
    if (num1 % 2 == 0) {
      result = multiply(num1/2,num2*2);
    }
    else
    {
      result = (multiply(num1/2,num2*2) + num2);
    }


    return result;
  }
}


/*****************************************************************
 * main - main program to exercise 'multiply'
 *
 * This program prompts the user for two numbers, and them multiplies the numbers
 * together.
 *
 *****************************************************************/
int main(int argc, char *argv[]) {
  /* prompt user and read number */
  int num1, num2;
  printf("Please type two non-negative integers: ");
  scanf("%d %d", &num1, &num2); /*note: does not error-check input */

  /* compute the product */
  printf("Their product is %d.\n", multiply(num1, num2));

  return EXIT_SUCCESS;
}
