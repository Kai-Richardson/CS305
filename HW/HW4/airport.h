#ifndef AIRPORT_H
#define AIRPORT_H

#define NOT_INIT -1
#define false 0
#define true 1
#define MAX_STRINGLEN 50

typedef struct airport
{
	char *name;
	char *city;
	char *country;
	char *id1;
	char *id2;
	float lat;
	float lng;
	int alt;
	char *zone;
	char *dst;
	char *dst2;
	char *type;
	char *source;
} airport;

void printAirport(airport *air);
void freeAirport(airport *air);

#endif