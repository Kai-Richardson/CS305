#ifndef PRINTER_H
#define PRINTER_H

#include "printJob.h"

#define true 1
#define false 0

#define MAX_NAME_LEN
#define MAX_PRINTERS 10
#define MAX_IN_QUEUE 10

typedef struct printer {
  char* name; //10 chars max no spaces
  printJob* printQueue; //head of a linked list that points to the printer’s linked list of print jobs (pointer is null if the printer does not have any jobs)
  int speed; //pages per minute
  int online; //bool
} printer;

/* function prototypes */
void add_job(printer* p, char j_name[MAX_NAME_LEN], int size);
void update_printer();
void offline(printer* p_arr[], int p_index, int num_prints);
void online(printer* p);
void print();

int queue_length(printer* j);

#endif