#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ll.h"

/* lengthList
 * parameter -- list
 * returns the length of the list (# nodes)
 */
int lengthList(LNode *list)
{
    if (list == NULL)
    {
        return 0;
    }
    else
    {
        return lengthList(list->next) + 1;
    }
}

/* freeList
 * parameter -- list
 * frees all nodes in the list
 */
void freeList(LNode *list)
{
    if (list == NULL)
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

/* copyList
 * parameter -- list
 * returns a copy of the list
 */
LNode *copyList(LNode *list)
{
    if (list == NULL)
    {
        return NULL;
    }
    else
    {
        return makeNode(list->value, copyList(list->next));
    }
}

/* mergeList
 * parameters: list1 and list 2
 * merges the two lists, keeping the values in ascending order
 * NOTE: only works if list1 and list2 are sorted
 */
LNode *mergeList(LNode *list1, LNode *list2)
{
    if (list1 == NULL)
    {
        return copyList(list2);
    }
    else if (list2 == NULL)
    {
        return copyList(list1);
    }
    else if (list1->value < list2->value)
    {

        return makeNode(list1->value, mergeList(list1->next, list2));
    }
    else
    {

        return makeNode(list2->value, mergeList(list1, list2->next));
    }
}

/* makeNode
 * parameters -- ptr (the ptr to store in the LNode)
 *            -- nextItem (the next link of the LNode)
 * slightly different than textbook version */
LNode *makeNode(airport *ptr, LNode *nextItem)
{
    LNode *ret = (LNode *)malloc(sizeof(LNode));
    ret->value = ptr;
    ret->next = nextItem;
    return ret;
}

/* print
 * parameter -- list (the linked list)
 * prints the values of the nodes (in order) of the list
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

/* findPort
 * parameters -- to_find (the string to search for)
 *            -- list (the linked list)
 * returns a pointer to the first airport found with id to_find
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

/* findNode
 * parameters -- to_find (the string to search for)
 *            -- list (the linked list)
 * returns a pointer to the first LNode found with airport id == to_find
 * if no such value is found, returns NULL
 */
LNode *findNode(char *to_find, LNode *list)
{
    while (list != NULL)
    {
        if (strcmp(list->value->id2, to_find) == 0)
        {
            return list;
        }
        list = list->next;
    }
    // no LNode with value n found
    return NULL; // or could return list, since list has value NULL
}

/* deleList
 * parameters -- toDelete (the LNode to find and delete)
 *            -- listPtr (pointer to the list)
 * note: must pass listPtr in case the first element of the list
 * is deleted -- passing the list by reference, so the address
 * to the first item in the list can get updated if necessary
 *
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

/* insertHead
 * parameters -- n (the value of the new LNode)
 *            -- listPtr (a pointer to the linked list for the insertion)
 *
 * inserts the new LNode at the front of the list, and returns it
 */
LNode *insertHead(airport *air, LNode *listPtr)
{
    // create new LNode
    listPtr = makeNode(air, listPtr);
    return listPtr;
}