/* Authors: Tammy VanDeGrift, Martin Cenek
 * CS 305
 * Stacks Lab
 * implements functions on stacks: initStack, empty, push, and pop
 */
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

/* initializes a new stack */
Stack initStack() {
  Stack s = (Stack) malloc(sizeof(StackType));
  s->top = NULL;
  return s;
}

/* empty returns 0 if S is empty and non-zero if S is not empty */
int empty(Stack S) {
  return (S->top == NULL);
}

/* pushes d to S */
void push(Stack S, StackData d) {
  Node * n = (Node *)malloc(sizeof(Node));
  n->data = d;
  n->next = S->top;
  S->top = n;
}

/* pops top item from S */
StackData pop(Stack S) {
  if(empty(S)) {
    printf("Stack is empty. Attempting to pop an empty stack. Exiting program.\n");
    exit(1);  // exiting program
  }
  // there is data to pop
  StackData toReturn = S->top->data;
  Node * tmp = S->top;  // in order to free this later
  S->top = S->top->next;  // move pointer to next item in stack
  free(tmp);
  return toReturn;
}

// LAB EXERCISE
/* peek: peeks at top value */
StackData peek(Stack S) {
  if(empty(S)) {
    printf("Stack is empty. No data item to peek.\n");
    return BAD;
  }
  return S->top->data;
}

// LAB EXERCISE
/* freeStack */
void freeStack(Stack S) {
  while (!empty(S))
  {
    pop(S);
  }
  free(S);
}

