/*****************************************************************
 * Program: palindrome.c
 *
 * Purpose: implements a recursive function for determining
 *   if a string is a palindrome
 *
 * Author: Steven R. Vegdahl, modified by Tammy VanDeGrift
 *
 *****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*****************************************************************
 * is_palindrome - determines whether a string of characters is a palindrome
 *
 * calling sequence:
 *    result = is_palindrome(str, first_index, last_index)
 *
 * parameters -
 *    str - the string to test
 *    first_index - index of the first character in the string
 *    last_index - index of the last character of the string
 *
 * result -
 *    Returns a 1 if the string in the range first_index..last_index is a
 *    palindrome; otherwise returns a 0.
 *
 * example -
 *    If idx1 is 0 and idx2 is 4, and str is "radar in range", then a 1 is
 *    returned; if the string were "rural", then 0 is returned. 
 *    
 * implementation -
 *    The first and last characters are examined.  If they don't match, 
 *    a zero is returned.  Otherwise we (recursively) test the string 
 *    without the first and last characters.
 *    
 *****************************************************************/
int is_palindrome(char *str, int first_index, int last_index) {
  if (first_index >= last_index) {  
    /* BASE CASE: string of length 1 or less: return 1 for true */
    return 1;
  }
  else if (str[first_index] != str[last_index]) { 
    /* BASE CASE: first and last chars mismatch: return 0 for false */
    return 0;
  }
  else { 
    /* RECURSIVE CASE: str[first_index] == str[last_index] */
    /* store result in temporary variable so that we can look at it
       in debugger */
    int result = 0; // update this to be the result of the recursive call
                    // should just be one line of code
    return result;
  }
}

/*****************************************************************
 * main - main program to exercise 'is_palindrome'
 *
 * This program prompts the user a string, and then calls 'is_palindrome' on the
 * string.
 * note: only works for strings of < 10000 characters
 * DO NOT MODIFY
 *****************************************************************/
int main(int argc, char *argv[]) {
  char buffer[10000]; /* buffer, hopefully plenty big to hold the string */
  buffer[0] = 0;      /* (in case empty string is typed) */
  printf("Please type a line of text: ");
  scanf("%9999[^\n]", &buffer);
  
  int length = strlen(buffer); /* length of string up to first null-character */
  printf("The string is %sa palindrome.\n",
	  is_palindrome(buffer, 0, length-1) ? "" : "not ");

  return EXIT_SUCCESS;
}
