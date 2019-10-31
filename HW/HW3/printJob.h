#ifndef PRINTJOB_H
#define PRINTJOB_H

typedef struct printJob
{
	char *name; //10 chars max no spaces
	int size;   //size of the job
	struct printJob *next;
} printJob;

/* printJob helper functions */
printJob *getTail(printJob *);
printJob *getListN(printJob *, int);
printJob *getNewTopJob(printJob *);

#endif