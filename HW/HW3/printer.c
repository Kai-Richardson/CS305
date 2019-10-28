#include "printer.h"
#include "printJob.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

/* add_job(printer, char*, int)
 * Adds a given job name and size to the end of given printer's LLqueue
 */
void add_job(printer p, char *j_name, int size)
{

    //No operations on printer if offline.
     if (p.online == false)
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

	new_job->name = j_name;
    new_job->size = size;
	new_job->next = NULL;

    //If the queue is empty, no need to traverse
    if (p.printQueue == NULL)
    {
        p.printQueue = new_job;
        return;
    }

    //traverse to find tail
    printJob *tail;
    tail = p.printQueue;
    while (tail != NULL)
    {
        tail = tail->next;
    }

    //Arrived at tail, time to append
    tail->next = new_job;
    return;
}

void update_printer()
{
    return;
}

/* offline(printer[], int, int)
 * Turns given printer from the printer array offline.
 */
void offline(printer p_arr[], int p_index, int num_prints)
{
    p_arr[p_index].online = false;
    for (int i = 0; i < queue_length(p_arr[p_index]); i++)
    {
        int curr_print = 0;

        if (p_arr[p_index].printQueue == NULL)
            return;

        //needs to weave-skip by one
        if (p_arr[i].online != false)
        {
            add_job(p_arr[curr_print], p_arr[p_index].printQueue->name, p_arr[p_index].printQueue->size);
            disposeTopJob(p_arr[p_index].printQueue); //delete old now that we're done with it
            curr_print++;
        }
        if (curr_print % num_prints != 0) //wraparound
        {
            curr_print = 0; //go back to 1st
        }
    }

    return;
}

/* online(printer*)
 * Sets the given printer online if it is offline
 */
void online(printer *p)
{
    if (p->online == false)
    {
        p->online = true;
    }
}

/* print(printer*)
 * Prints information about given printer + its printjobs
 */
void print(printer p)
{
    printf("%s@%d->", p.name, p.speed); //print printer information

    //Empty, early return
    if (p.printQueue == NULL)
    {
        printf("\n");
        return;
    }

    //traverse + print all jobs
    printJob *j;
    j = p.printQueue;
    while (j != NULL)
    {
        printf("%s:%d->", j->name, j->size);
        j = j->next;
    }

    printf("\n"); //Done with printer, newline time
    return;
}
