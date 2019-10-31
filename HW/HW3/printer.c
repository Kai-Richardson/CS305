#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "printer.h"
#include "printJob.h"

/* create_job_for_printer(printer, char*, int)
 * Creates a given job name and size regarding printer settings and returns it
 */
printJob *create_job_for_printer(printer p, char *j_name, int size)
{

	//No operations on printer if offline.
	if (p.online == false)
		return NULL;

	//No operations on printer if bad size
	if (size < 1)
		return NULL;

	//Malloc new printjob + assign data
	printJob *new_job;
	new_job = (printJob *)malloc(sizeof(struct printJob));

	//so we don't use original temp and we have our own ptr
	char *jobname = malloc(sizeof(char) * MAX_NAME_LEN);
	strncpy(jobname, j_name, MAX_NAME_LEN);
	new_job->name = jobname;

	new_job->size = size;
	new_job->next = NULL;

	return new_job;
}

void add_job(printer p_arr[], printJob *passed_job, int p_index)
{
	//If the queue is empty, no need to traverse
	if (p_arr[p_index].printQueue == NULL)
	{
		p_arr[p_index].printQueue = passed_job;
		return;
	}

	//traverse to find tail
	printJob *tail = getTail(p_arr[p_index].printQueue);
	tail->next = passed_job;
	return;
}

void update_printer(printer p_arr[], int num_prints, int is_term)
{
	printf("\n");
	for (int i = 0; i < num_prints; i++)
	{
		int avail_speed = p_arr[i].speed;

		//only process if online
		if (p_arr[i].online == true)
		{
			//if queue is empty, no process to do
			if (p_arr[i].printQueue == NULL)
			{
			}
			else if (p_arr[i].printQueue->size <= avail_speed) //if we can finish, do & dispose top
			{
				if (is_term)
				{
					printf("\033[0;33mDone: \033[0;32m%s\033[0m:\033[0;31m%s\033[0m\n", p_arr[i].name, p_arr[i].printQueue->name);
				}
				else
				{
					printf("Done: %s:%s\n", p_arr[i].name, p_arr[i].printQueue->name);
				}

				p_arr[i].printQueue = getNewTopJob(p_arr[i].printQueue);
				avail_speed -= p_arr[i].speed;
			}
			else //if we can't
			{
				p_arr[i].printQueue->size -= avail_speed;
			}
		}

		print(p_arr[i], p_arr[i].printQueue, is_term);
	}
	printf("\n");

	return;
}

/* offline(printer[], int, int)
 * Turns given printer from the printer array offline.
 */
void offline(printer p_arr[], int p_index, int num_prints)
{
	p_arr[p_index].online = false;

	int curr_print = 0;	//current printer
	int curr_head_col = 0; //current header column
	printJob *first_to_process = p_arr[p_index].printQueue;

	while (p_arr[p_index].printQueue != NULL)
	{

		if (curr_print == 0)
		{
			curr_head_col += 2; //Move header col
		}

		//Only eat jobs if online
		if (p_arr[curr_print].online == true)
		{
			printJob *whereInsert = getListN(p_arr[curr_print].printQueue, curr_head_col - 2);
			printJob *toInsert = grabTopJob(p_arr[p_index], p_arr[p_index].printQueue);
			printJob *tempHolder = toInsert->next;

			if (whereInsert == NULL)
			{
				toInsert->next = p_arr[curr_print].printQueue;
				if (p_arr[curr_print].printQueue == NULL)
				{
					p_arr[curr_print].printQueue = toInsert;
				}
				else
				{
					p_arr[curr_print].printQueue->next = toInsert;
				}
			}
			else
			{
				toInsert->next = whereInsert->next;
				whereInsert->next = toInsert;
			}
			p_arr[p_index].printQueue = tempHolder;
		}

		curr_print++;

		//Couldn't find anything! Abort.
		if (first_to_process == p_arr[p_index].printQueue && (curr_print % num_prints == 0))
		{
			printf("Error: No online printers to distribute to. Aborting job distribution.\n");
			return;
		}

		curr_print = curr_print % num_prints; //wraparound
	}

	return;
}

/* online(printer[], int)
 * Sets the given printer in array index online if it is offline
 */
void online(printer p_arr[], int p_index)
{
	if (p_arr[p_index].online == false)
	{
		p_arr[p_index].online = true;
	}
}

/* print(printer, printJob*, int)
 * Prints information about given printer + its printjobs
 */
void print(printer p, printJob *head, int is_term)
{
	if (is_term)
	{
		char *online_str = "\033[0;32m";
		if (p.online == false)
		{
			online_str = "\033[7;32m";
		}

		printf("%s%s\033[0;33m@\033[0;36m%d\033[0m", online_str, p.name, p.speed); //print printer information
	}
	else
	{
		printf("%s@%d", p.name, p.speed); //print printer information
	}

	//Empty, early return
	if (head == NULL)
	{
		printf("\n");
		return;
	}
	else
	{
		printf("->");
	}

	//traverse + print all jobs
	printJob *j;
	j = head;
	while (j != NULL)
	{
		if (is_term)
		{
			printf("\033[0;31m%s\033[0;33m:%d\033[0m", j->name, j->size);
		}
		else
		{
			printf("%s:%d", j->name, j->size);
		}

		j = j->next;
		if (j != NULL)
		{
			printf("->");
		}
	}

	printf("\n"); //Done with printer, newline time
	return;
}
