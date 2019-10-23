#include "string.h"
#include "stdio.h"
#include "stdlib.h"

#include "printer.h"
#include "printJob.h"

void create_printJob()
{
    return;
}

void disposeTopJob(struct printJob *head)
{
    if (head == NULL)
        return;

    // Move the head pointer to the next node
    printJob *old_head = head;
    if (head->next != NULL)
    {
        head = head->next;
        free(old_head);
    }
    return;
}

int queue_length(printer *j)
{

    if (!j->printQueue)
        return 0; //print queue is empty

    int length = 0;
    printJob *i;
    i = j->printQueue;
    while (i != NULL)
    {
        i = i->next;
        length++;
    }
    return length;
}