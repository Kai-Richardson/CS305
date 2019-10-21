#include <stdio.h>
#include <stdlib.h>


#define BAD -9999999

/* data to store into stack */
typedef int StackData;  // can change type by changing type after typedef
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



/* initializes a new stack */
Stack initStack()
{
    Stack s = (Stack)malloc(sizeof(StackType));
    s->top = NULL;
    return s;
}

/* empty returns 0 if S is empty and non-zero if S is not empty */
int empty(Stack S)
{
    return (S->top == NULL);
}

/* pushes d to S */
void push(Stack S, StackData d)
{
    Node *n = (Node *)malloc(sizeof(Node));
    n->data = d;
    n->next = S->top;
    S->top = n;
}

/* pops top item from S */
StackData pop(Stack S)
{
    if (empty(S))
    {
        printf("Stack is empty. Attempting to pop an empty stack. Exiting program.\n");
        exit(1); // exiting program
    }
    // there is data to pop
    StackData toReturn = S->top->data;
    Node *tmp = S->top;    // in order to free this later
    S->top = S->top->next; // move pointer to next item in stack
    free(tmp);
    return toReturn;
}

int isPalindrome(char *str)
{
    if (str == NULL)
    {
        return 0;
    }
    Stack s = initStack();
    int i = 0;
    // push each character of str to the stack
    while (str[i] != '\0')
    {
        push(s, str[i]);
        i++;
    }
    // now pop stack, checking that the value on top of the stack equals the str char
    i = 0;
    while (str[i] != '\0')
    {
        if (pop(s) == str[i]) {
            i++;
        }
        else
        {
            printf("%s is not a palindrome\n", str);
            break;
        }

    }
    return 1;
}

int main(void) {
    int succeed = 1;
    succeed = isPalindrome("bojjob");
    printf("%d\n", succeed);
    return 1;
}