#include "printer.h"
#include "printJob.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void add_job(printer *p, char j_name[MAX_NAME_LEN], int size)
{

    //No operations on printer if offline.
    if (p->online == false)
        return;

    //No additions if the queue is full.
    if (queue_length(p) >= MAX_IN_QUEUE)
        return;

    //No operations on printer if bad size
    if (size < 1)
        return;

    //Malloc new printjob + assign data
    printJob *new_job;
    new_job = (printJob *)malloc(sizeof(struct printJob));
    strcpy(new_job->name, j_name);
    new_job->size = size;

    //If the queue is empty, no need to traverse
    if (p->printQueue == NULL)
    {
        p->printQueue = new_job;
        return;
    }

    //traverse to find tail
    printJob *tail;
    tail = p->printQueue;
    while (tail != NULL)
    {
        tail = tail->next;
    }

    //Arrived at tail, time to append
    tail->next = new_job;
    return;
}

void update_printer();

/* Turns a
 *
 */
void offline(printer* p_arr[], int p_index, int num_prints)
{
    p_arr[p_index]->online = false;
    for (int i = 0; i < num_prints; i++)
    {
        //done
        if (p_arr[p_index]->printQueue == NULL) return;

        if (p_arr[i]->online != false)
        {
            add
            addyankTopJob(p_arr[p_index]->printQueue);
        }

    }

        //go through printjobs and weave them into other printers round robin
    return;
}

/* online()
 * Sets the given printer online if it is offline
 */
void online(printer *p)
{
    if (p->online == false)
    {
        p->online = true;
    }
}

void print(printer *p)
{
    printf("<%s>:<spd: %d>->", p->name, p->speed);
    for (int i = 0; i < queue_length(p->printQueue); i++)
    {
        //traverse between all
        return;
    }
    return;
}
