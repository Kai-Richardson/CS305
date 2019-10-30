#include "string.h"
#include "stdio.h"
#include "stdlib.h"

#include "printer.h"
#include "printJob.h"

/* printJob *getNewTopJob(printer)
 * Deletes printer's current job and returns the next one in line.
 */
printJob *getNewTopJob(printer p)
{
	//got passed printer with no top job!
	if (p.printQueue == NULL)
		return NULL;

	// Move the head pointer to the next node
	printJob *old_head = p.printQueue;
	printJob *to_return = NULL;

	//If there's a next element, move it up the queue
	if (p.printQueue->next != NULL)
	{
		to_return = p.printQueue->next;
	}

	//free old job
	free(old_head->name);
	free(old_head);
	return to_return;
}

/* int queue_length(printer)
 * Returns length of current printer's queue.
 */
int queue_length(printer p)
{

	if (p.printQueue == NULL)
		return 0; //print queue is empty

	int length = 0;
	printJob *i;
	i = p.printQueue;
	while (i != NULL)
	{
		i = i->next;
		length++;
	}
	return length;
}