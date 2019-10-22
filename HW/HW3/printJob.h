#ifndef PRINTJOB_H
#define PRINTJOB_H

#include "printJob.h"

typedef struct printJob {
  char* name[10]; //10 chars max no spaces
  int size;
  printJob* next;
} printJob;

/* function prototypes */
void create_printJob();
void print();

#endif