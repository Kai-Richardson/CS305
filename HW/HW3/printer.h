#ifndef PRINTER_H
#define PRINTER_H

#include "printJob.h"

#define true 1
#define false 0

#define MAX_NAME_LEN 10
#define MAX_PRINTERS 10
#define MAX_ALLOWED_INPUT 40

typedef struct printer
{
	char *name;			  //10 chars max no spaces
	printJob *printQueue; //head of a linked list that points to the printer's linked list of print jobs (pointer is null if the printer does not have any jobs)
	int speed;			  //pages per minute
	int online;			  //bool
} printer;

/* function prototypes */
printJob *create_job_for_printer(printer p, char *j_name, int size);
void add_job(printer p_arr[], printJob *pj, int p_index);
void update_printer(printer p_arr[], int num_prints, int is_term);
void offline(printer p_arr[], int p_index, int num_prints);
void online(printer p_arr[], int p_index);
void print(printer p, printJob *j, int is_term);
printJob *grabTopJob(printer p, printJob *head);
#endif