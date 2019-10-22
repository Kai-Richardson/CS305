#include "string.h"
#include "stdio.h"
#include "stdlib.h"

#include "printer.h"
#include "printJob.h"

void print() {
    return;
}

void create_printJob() {
    return;
}

printJob* yankTopJob(struct printJob* head)
{
    if (head == NULL)
        return NULL;

    // Move the head pointer to the next node
    printJob* old_head = head;
    if (head->next != NULL)
    {
         head = head->next;
    }

    return old_head;
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