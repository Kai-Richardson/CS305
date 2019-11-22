#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>
#include "main.h"
#include "graph.h"

void dijkstra(Graph *g, char *source)
{
	//already initialized

	int src_vrt = -1;

	//Iterate through all verticies
	for (int i = 0; i < g->V; i++)
	{
		//Check if we found our airport
		if (strncmp(g->jump[i], source, 4) == 0)
		{
			src_vrt = i;			//found it
			g->array[i].dValue = 0; //origin
			break;
		}
	}

	if (src_vrt == NIL) return; //We didn't find anything!

	while (!isEmpty(g))
	{
		int smallest_indx = getMinIndx(g); //

		if (smallest_indx == NIL)
			break;

		AdjList pretest = g->array[smallest_indx];
		AdjListNode *test = g->array[smallest_indx].head;

		int smallestD_and_cost = 0;
		if (g->array[smallest_indx].head != NULL)
		{
			smallestD_and_cost = g->array[smallest_indx].head->cost;
		}
		smallestD_and_cost += g->array[smallest_indx].dValue;

		while (g->array[smallest_indx].head != NULL)
		{
			int neighbor_indx = g->array[smallest_indx].head->dest;
			if (g->array[neighbor_indx].dValue > smallestD_and_cost)
			{
				g->array[neighbor_indx].dValue = smallestD_and_cost;
				g->array[neighbor_indx].pred = smallest_indx;
				break;
			}
			g->array[smallest_indx].head = g->array[smallest_indx].head->next;
		}

		g->array[smallest_indx].color = BLACK;
	}
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