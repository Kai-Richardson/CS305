#ifndef PRINTJOB_H
#define PRINTJOB_H

typedef struct printJob
{
	char *name; //10 chars max no spaces
	int size;
	struct printJob *next;
} printJob;

/* function prototypes */
void disposeTopJob(struct printJob *head);

#endif