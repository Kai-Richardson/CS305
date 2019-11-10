#include "airport.h"
#include <stdio.h>
#include <stdlib.h>

void printAirport(airport *air)
{
	if (air == NULL) return;

	printf(" Name: %s | ", air->name);
	printf("City: %s | ", air->city);
	printf("Country: %s | ", air->country);
	printf("ID1: %s | ", air->id1);
	printf("ID2: %s | ", air->id2);
	printf("Lat: %f | ", air->lat);
	printf("Long: %f | ", air->lng);
	printf("Alt: %i | ", air->alt);
	printf("Zone: %s | ", air->zone);
	printf("Dst: %s | ", air->dst);
	printf("Dst2: %s | ", air->dst2);
	printf("Type: %s | ", air->type);
	printf("Source: %s\n", air->source);
}

void freeAirport(airport *air)
{
	free(air->name);
	free(air->city);
	free(air->country);
	free(air->id1);
	free(air->id2);
	free(air->zone);
	free(air->dst);
	free(air->dst2);
	free(air->type);
	free(air->source);
	free(air);
}