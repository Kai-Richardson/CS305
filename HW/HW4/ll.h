#ifndef LL_H
#define LL_H
#include "airport.h"

typedef struct LNode LNode;

struct LNode
{
	airport *value;
	LNode *next;
};

LNode *makeNode(airport *ptr, LNode *nextItem);
void print(LNode *list);
airport *findPort(char *, LNode *list);
LNode *findNode(char *, LNode *list);
int deleList(LNode *toDelete, LNode **listPtr);
LNode *insertHead(airport *, LNode *list);
void freeList(LNode *list);

#endif