/* Authors: Tammy VanDeGrift, Martin Cenek
 * main.c
 * CS 305
 * Stacks Lab
 * tests the Stack data structure
 */

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

/* prototypes */
void test1();
void test2();
void test3();
void testMatch();

int main(void)
{
  //test1();
  //test2();
  //test3();
  testMatch();
  return EXIT_SUCCESS;
}

/* test stack */
void test1()
{
  // create a new stack
  Stack s = initStack();
  push(s, 8);
  push(s, 10);
  push(s, 11);
  push(s, 3);
  push(s, 15);

  while (!empty(s))
  {
    printf("%d ", pop(s));
  }
  printf("\n");
}

/* test peeking */
void test2()
{
  // test out peek
  Stack s = initStack();
  push(s, 10);
  push(s, 20);
  push(s, 13);
  push(s, 18);
  StackData p = peek(s);
  printf("peek: %d\n", p);
  push(s, 4);
  while (!empty(s))
  {
    printf("%d ", pop(s));
  }
  printf("\n");

  Stack s2 = initStack();
  StackData p2 = peek(s);
  printf("peek: %d\n", p2);
}

void test3()
{
  Stack s = initStack();
  push(s, 10);
  push(s, 20);
  push(s, 13);
  printf("peek: %d\n", peek(s));
  free(s); //No way to check if something has been freed in C. This works though.
  printf("freed peek: %d\n", peek(s));
}

// LAB EXERCISE
/* test checking for matching ( ) and [ ] */
void testMatch()
{
  printf("Enter an expression:\n");
  char *input = malloc(sizeof(char) * 100);
  size_t read;
  size_t numread = getline(&input, &read, stdin);

  // determine if input has properly nested matching ( ) and matching [ ]
  int i;
  Stack s = initStack();
  for (i = 0; i < numread; i++)
  {
    if (input[i] == '(')
    {
      push(s, input[i]);
    }
    else if (input[i] == '[')
    {
      push(s, input[i]);
    }
    else if (input[i] == ')')
    {
      if (pop(s) != '(')
      {
        printf("Not in proper format.\n");
        break;
      }
    }
    else if (input[i] == ']')
    {
      if (pop(s) != '[')
      {
        printf("Not in proper format.\n");
        break;
      }
    }
  }
  if (empty(s))
  {
    printf("In proper format.\n");
  }
  else
  {
    printf("Not in proper format.\n");
  }
}
