#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "printer.h"
#include "printJob.h"

/* printJob *getNewTopJob(printJob)
 * Deletes printer's current job and returns the next one in line.
 */
printJob *getNewTopJob(printJob *j)
{
	//got passed printer with no top job!
	if (j == NULL)
		return NULL;

	// Move the head pointer to the next node
	printJob *old_head = j;
	printJob *to_return = NULL;

	//If there's a next element, move it up the queue
	if (j->next != NULL)
	{
		to_return = j->next;
	}

	//free old job
	free(old_head->name);
	free(old_head);
	return to_return;
}

/* printJob *grabTopJob(printer, printJob)
 * Grabs the top job from a printer and moves everything up
 */
printJob *grabTopJob(printer p, printJob *head)
{
	//got passed null top job
	if (head == NULL)
		return NULL;

	// Move the head pointer to the next node
	printJob *old_head = head;
	printJob *temp = NULL;

	//If there's a next element, move it up the queue
	if (head->next != NULL)
	{
		temp = head->next;
	}
	p.printQueue = temp; //put previous next elem into head position

	return head;
}

/* printJob *getTail(printJob*)
 * Returns tail of given printjob*.
 */
printJob *getTail(printJob *head)
{
	//traverse to find tail
	printJob *tail;
	tail = head;
	while (tail != NULL)
	{
		//If there's further elements
		if (tail->next == NULL)
		{
			break; //we found the end
		}
		else
		{
			tail = tail->next;
		}
	}

	//Arrived at tail, return it
	return tail;
}

/* printJob *getListN(printJob *head, int n)
 * Returns the queue item at the nth depth of a given queue
 */
printJob *getListN(printJob *head, int n)
{

	if (n == 0)
		return head;

	//what we'll be returning
	printJob *to_return = head;

	for (int i = 0; i < n; i++)
	{
		if (to_return->next == NULL)
		{
			break;
		}
		else
		{
			to_return = to_return->next;
		}
	}

	return to_return;
}