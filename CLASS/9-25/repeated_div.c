/***********************************************
 * CS 305 lecture
 * algorithm analysis - printing prime numbers
 * 
 * repeated_div.c
 * Authors: Vegdahl, VanDeGrift, Cenek
 ***********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUM_PARAMS 2

/* prints primes up to the number specified by the user
 * at command line
 */
int main(int argc, char * argv[]) {

  // check that # of command-line arguments is correct
  if(argc != NUM_PARAMS) {
    printf("usage:\nargv[0] max_num\nto print primes up to max_num\n");
    return EXIT_FAILURE;
  }
  // check that # entered is non-negative
  if(atoi(argv[1]) < 0) {
    printf("max_num must be non-negative. exiting\n");
    return EXIT_FAILURE;
  }

  /* heart of the algorithm */
  int i, j;
  int max = atoi(argv[1]);
  for(i = 2; i <= max; i++) {  // go through each number
    bool found_prime = true;  // assume we have a prime # to start
    // look for a smaller number that divides i
    for(j = 2; j*j <= i; j++) {
      if (i % j == 0) {
	// found divisor
	found_prime = false;
	break;
      }
    }
    // print it to the screen if prime
    if (found_prime) {
      printf("%d\n", i);
    }
  }
  return EXIT_SUCCESS;
}



