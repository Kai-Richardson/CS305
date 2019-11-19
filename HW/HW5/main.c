/*
 * Author: Tammy VanDeGrift, Tanya Crenshaw, Martin Cenek
 * main.c
 * creates a graph of airports and runs dijkstra's algorithm to find
 * the shortest cost flight path from a source to a destination
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>
#include "main.h"
#include "graph.h"

/*
 * main
 * Creates a graph of airports and runs dijkstra's algorithm to find
 * the shortest path from a source airport to a destination airport.
 * usage: hw6 SampleRoutes.txt PDX MCO
 */
int main(int argc, char *argv[])
{

	// Check command line arguments.
	if (argc != REQ_PARAM)
	{
		usage(argv[0]);
	}
	// Are the city names too long?
	if (strlen(argv[SRC]) > MAXWIDTH)
	{
		err(argv[2]);
	}
	if (strlen(argv[DST]) > MAXWIDTH)
	{
		err(argv[3]);
	}

	// Sort the array of airport names lexicographically using the built-in
	// C function qsort().
	//qsort(airports, sizeof(airports)/sizeof(*airports), sizeof(*airports), compare);

	//printf("Creating a graph for %d airports.\n", numberOfAirports);

	// Given a number and a list of labels, initialize a graph data structure
	// for that many nodes, labeled with the labels.
	char **airports = NULL;
	int numberOfAirports = 0;
	struct Graph *flights = buildGraph(argv[1], &airports, &numberOfAirports);

	printGraph(flights);

	//UNCOMMENT HERE
	/*
  // Are the names given at the command line in the list of airports?
  int srcfound = 0;
  int dstfound = 0;
  for(int i = 0; i < numberOfAirports; i++) {
    if(strncmp(argv[SRC], airports[i], MAXWIDTH) == 0) srcfound = 1;
    if(strncmp(argv[DST], airports[i], MAXWIDTH) == 0) dstfound = 1;
  }

  if(!srcfound) {
    err(argv[SRC]);
  }
  if(!dstfound) {
    err(argv[DST]);
  }

  printf("\n------------------------------\n\n");

  // Find the shortest paths and print the result.
  dijkstra(flights, argv[SRC]);
  printLabels(flights);

  printf("\n------------------------------\n\n");

  int destNum = -1;
  int srcNum = -1;
  // Get the index number of the destination and the source.
  int i = 0;
  while(i < flights->V && srcNum == -1) {
    if( strncmp(argv[SRC], flights->array[i].label, MAXWIDTH) == 0) {
      srcNum = i;
    }
    i++;
  }

  i = 0;
  while(i < flights->V && destNum == -1) {
    if( strncmp(argv[DST], flights->array[i].label, MAXWIDTH) == 0) {
      destNum = i;
    }
    i++;
  }

  // Start at the destination, and going backwards to the source
  // find all of the members of the path from the source to the destination.
  // As I find each one, keep track of it in the path array.
  int path[numberOfAirports];

  printf("Getting the path from %d to %d. \n", srcNum, destNum);

  int j = 0;
  int pathFinder = destNum;
  while(pathFinder != srcNum) {
    path[j] = flights->array[pathFinder].pred;
    pathFinder = flights->array[pathFinder].pred;
    j++;
  }

  printf("The path is %d flight(s) long: \n\n", j);

  // Print the path backwards.
  j--;
  while(j >= 0) {
    printf("%s -> ", flights->jump[path[j]]);
    j--;
  }

  // Print the final destination.
  printf("%s. \n", argv[DST]);

  // Print the total mileage.
  printf("%d miles.\n", flights->array[destNum].dValue);
  printf("\n------------------------------\n");

//UNCOMMENT HERE
*/
	freeGraph(&flights, &airports, numberOfAirports);

	return EXIT_SUCCESS;
}

/*
 * buildThisGraph
 * construct edges from airport to airport
 */
Graph *buildGraph(char *fn, char ***citiesP, int *n)
{
	FILE *fp = fopen(fn, "r");
	if (fp == NULL)
	{
		printf("ERROR: Could not open file for reading\n");
		return NULL;
	}
	int citiesNum;
	char name[MAXWIDTH + 1];
	name[MAXWIDTH] = '\0';
	fscanf(fp, "%d\n", &citiesNum);
	*n = citiesNum;
	char **cities = (char **)malloc(sizeof(char *) * citiesNum);
	for (int i = 0; i < citiesNum; i++)
	{
		fscanf(fp, "%3s\n", name);
		cities[i] = strndup(name, MAXWIDTH);
	}
	*citiesP = cities;
	// Initialize the graph data structure.
	Graph *g = initialize(citiesNum, cities);
	if (g == NULL)
	{
		printf("ERROR: Could not create graph\n");
		return NULL;
	}

	char or [MAXWIDTH + 1], dest[MAXWIDTH + 1];
	or [MAXWIDTH] = '\0';
	dest[MAXWIDTH] = '\0';
	int dist;
	while (fscanf(fp, "%s %s %d\n", or, dest, &dist) == 3)
	{
		//printf("Read: %s %s %d\n", or, dest, dist);
		addEdge(g, or, dest, dist);
	}
	fclose(fp);
	return g;
};
/*
 * compare
 * Compare two strings.  That is, given two elements, extract the char
 * pointers from them and compare the strings using strncmp().
 */
int compare(const void *elem1, const void *elem2)
{

	char *s1 = *(char **)elem1;
	char *s2 = *(char **)elem2;

	return strncmp(s1, s2, MAXWIDTH);
}

/*
 * usage
 * Print the usage for this program and exit program.
 */
void usage(char *s)
{
	printf("usage: %s <source city name> <dest. city name>\n", s);
	printf("  This program finds the shortest flight path from the given source city to destination.\n");
	exit(-1);
}

/*
 * err
 * Print an error message for this program and exit proram.
 */
void err(char *s)
{
	printf("%s is not in this set of airports.\n", s);
	exit(-1);
}
