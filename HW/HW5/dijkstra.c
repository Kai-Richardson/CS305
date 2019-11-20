#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>
#include "main.h"
#include "graph.h"

void dijkstra(Graph *g, char *source)
{
}

/* int isEmpty(Graph *)
 *
 * Returns 0 if provided graph is non-empty, 1 if empty
 */
int isEmpty(Graph *g)
{
	if (g == NULL)
		return 1;

	//Iterate through all verticies
	for (int i = 0; i < g->V; i++)
	{
		if (g->array[i].color == WHITE)
			return 0;
	}

	return 1;
}

/* int getMinIndx(Graph *)
 *
 * Returns the index of the smallest white node in the provided graph
 */
int getMinIndx(Graph *g)
{
	if (g == NULL)
		return -1;

	int small_index = -1;
	int small_value = INT_MAX;

	//Iterate through all verticies
	for (int i = 0; i < g->V; i++)
	{
		if ((g->array[i].color == WHITE) && (g->array[i].dValue < small_value))
		{
			small_index = i;
			small_value = g->array[i].dValue;
		}
	}

	return small_index;
}