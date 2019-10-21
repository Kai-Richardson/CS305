#ifndef STACK_H
#define STACK_H

#define BAD '!'

/* data to store into stack */
typedef char StackData;  // can change type by changing type after typedef
                         // and before StackData
                         // if data in stack is a struct, put struct type here


/* stack data structures */
typedef struct NodeTag Node;
typedef struct StackTag StackType;
typedef struct StackTag* Stack;

/* linked list implementation of stacks */
struct NodeTag {
  StackData data;
  Node *next;
};

struct StackTag {
  Node * top;
};

/* function prototypes on stacks */
Stack initStack();
int empty(Stack S);
void push(Stack S, StackData d);
StackData pop(Stack S);
StackData peek(Stack S);
void freeStack(Stack S);
#endif
