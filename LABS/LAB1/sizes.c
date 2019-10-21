#include <stdio.h>

/* program to show the sizes of different variable types */
int main(int argv, char* argc[]) {
  int intVar = 10;
  char charVar = 'a';
  double doubleVar = 25.78;
  int * intPointer;
  char * charPointer;
  double * doublePointer;
  long longVar = 993756245;
  
  int s_int = sizeof(intVar);
  int s_char = sizeof(charVar);
  int s_double = sizeof(doubleVar);
  int s_intPointer = sizeof(intPointer);
  int s_charPointer = sizeof(charPointer);
  int s_doublePointer = sizeof(doublePointer);
  int s_long = sizeof(longVar);

  printf("Size of int in bytes: %d\n", s_int);
  printf("Size of char in bytes: %d\n", s_char);
  printf("Size of double in bytes: %d\n", s_double);
  printf("Size of int pointer in bytes: %d\n", s_intPointer);
  printf("Size of char pointer in bytes: %d\n", s_charPointer);
  printf("Size of double pointer in bytes: %d\n", s_doublePointer);
  printf("size of long: %d\n", s_long);


  /* now assign the pointers */
  intPointer = &intVar;   // this assigns the address of intVar to intPointer
  charPointer = &charVar;
  doublePointer = &doubleVar;

  /* print the values of the variables */
  printf("Value of intVar: %d\n", intVar);
  printf("Value of charVar: %c\n", charVar);
  printf("Value of doubleVar: %lf\n", doubleVar);
  
  /* print the values of the pointers */
  printf("Value of intPointer: %ld\n", intPointer);
  printf("Value of charPointer: %ld\n", charPointer);
  printf("Value of doublePointer: %ld\n", doublePointer);

  return 0;
}
