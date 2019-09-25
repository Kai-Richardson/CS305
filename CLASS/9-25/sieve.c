/***********************************************
 * CS 305 lecture
 * algorithm analysis - printing prime numbers
 * 
 * sieve.c
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

  /* heart of algorithm */
  int i, j;
  int max = atoi(argv[1]);
  int len = max + 1;     // length of array
  int prime_count = 0;   // number of primes found
  bool * hits = malloc(len*sizeof(bool));  // array to store T/F for primes
  
  // clear hits array
  for (i = 0; i < len; i++) {
    hits[i] = false;
  }

  // go through array until at sqrt(len)
  // mark off multiples of primes
  for (i = 2; i*i <= len; i++) {
    if (!hits[i]) { // mark off its multiples in hits
      for (j = i*2; j < len; j = j+i) {
	hits[j] = true;
      }
    }
  }

  // print primes
  for (i = 2; i < len; i++) {
    if (!hits[i]) {
      printf("%d\n", i);
    }
  }

  free(hits);
  return EXIT_SUCCESS;
}
