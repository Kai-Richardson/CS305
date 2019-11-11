/* ll.c for CS305 HW4
 * @author - Kai Richardson
 * @date 2019-11-10
 * Note: Sections of the LL logic were copied from an earlier lab done in class.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ll.h"

/* void freeList(LNode *)
 * frees all nodes in the list (and their airports), including the passed list itself
 */
void freeList(LNode *list)
{
    if (list == NULL) //passed null (likely recusrively)
    {
        return;
    }
    else
    {
        freeList(list->next);
        freeAirport(list->value);
        free(list);
    }
}

/* LNode *makeNode(airport *, LNode *)
 * Makes a node with the given airport and sets next equal to passed LNode
 */
LNode *makeNode(airport *ptr, LNode *nextItem)
{
    LNode *ret = (LNode *)malloc(sizeof(LNode));
    ret->value = ptr;
    ret->next = nextItem;
    return ret;
}

/* void print(LNode *)
 * prints the names of all the airports in the list in order
 */
void print(LNode *list)
{
    printf("Linked list contents: ");
    while (list != NULL)
    {
        printf("%s ", list->value->name);
        list = list->next;
    }
    printf("\n");
}

/* airport *findPort(char *, LNode *)
 * returns a pointer to the first airport found with id to_find in given list
 * if no such value is found, returns NULL
 */
airport *findPort(char *to_find, LNode *list)
{
    while (list != NULL)
    {
        if (strcmp(list->value->id2, to_find) == 0)
        {
            return list->value;
        }
        list = list->next;
    }
    // no LNode with value n found
    return NULL; // or could return list, since list has value NULL
}

/* LNode *findNode(char *, LNode *)
 * returns a pointer to the first LNode found with airport id == to_find
 * if no such value is found, returns NULL
 */
LNode *findNode(char *to_find, LNode *list)
{
    while (list != NULL)
    {
        if (strcmp(list->value->id2, to_find) == 0) //if ids are equal
        {
            return list;
        }
        list = list->next;
    }
    // no LNode with value n found
    return NULL; // or could return list, since list has value NULL
}

/* int deleList(LNode *, LNode **)
 * deletes the given LNode from the given LNode list pointer
 * returns 0 if no item found and deleted
 * returns 1 if a LNode is deleted
 */
int deleList(LNode *toDelete, LNode **listPtr)
{
    LNode *list = *listPtr; // list is the linked list
    // case: either toDelete or list is null -- will not be deleting
    if (toDelete == NULL || list == NULL)
    {
        return 0; // indicates no change to the list
    }

    // special case: toDelete is first LNode in list
    if (toDelete == list)
    {
        *listPtr = list->next; // now list->next becomes first LNode in list
                               // returning new first address via pointer
        freeAirport(toDelete->value);
        free(toDelete);
        return 1; // indicates that a LNode was deleted
    }

    // case: need to find toDelete somewhere other than first LNode in list
    LNode *before = list;
    list = list->next;
    while (list != NULL)
    {
        if (toDelete == list)
        {
            // redo pointers and then free memory
            before->next = list->next;
            freeAirport(list->value); //Frees the airport in the list since we run this last
            free(list);
            return 1;
        }
        before = list; // update for next iteration
        list = list->next;
    }
    return 0; // toDelete not found
}

/* LNode *insertHead(airport *, LNode *)
 * inserts the new LNode at the front of the list, and returns it
 */
LNode *insertHead(airport *air, LNode *listPtr)
{
    // create new LNode
    listPtr = makeNode(air, listPtr);
    return listPtr;
}