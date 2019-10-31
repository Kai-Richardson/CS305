#ifndef PRINTJOB_H
#define PRINTJOB_H

typedef struct printJob
{
	char *name; //10 chars max no spaces
	int size;
	struct printJob *next;
} printJob;

/* not many prototypes here due to having printer-focused methodology */

printJob *getTail(printJob *);
printJob *getListN(printJob *, int);

#endif