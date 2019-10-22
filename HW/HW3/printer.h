#ifndef PRINTER_H
#define PRINTER_H

#include "printJob.h"

#define true 1
#define false 0

#define MAX_PRINTERS 10

typedef struct printer {
  char* name[10]; //10 chars max no spaces
  printJob* printQueue; //head of a linked list that points to the printer’s linked list of print jobs (pointer is null if the printer does not have any jobs)
  int speed; //pages per minute
  int online; //bool
} printer;

/* function prototypes */
void add_job();
void update_printer();
void offline();
void online();
void print();
void weave(printer* p);
int queue_length(printJob* j);

#endif