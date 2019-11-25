#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "main.h"

/* void dijkstra(Graph *, char *)
 * Sets up the given graph with distance values and paths emmanating from source node specified by char*
 */
void dijkstra(Graph *g, char *source)
{
	int sourceIndex = -1;
	//get the index of our source airport
	for (sourceIndex = 0; sourceIndex < g->V; sourceIndex++)
		if (strcmp(g->jump[sourceIndex], source) == 0)
			break;

	//if we didn't find it, return error
	if (sourceIndex == NIL)
		return;

	//Set src to 0 to let getMin function find it
	g->array[sourceIndex].dValue = 0;

	//while each node has not been visited and is still white
	while (isEmpty(g) != NIL)
	{
		//find the small_value dValue in our graph
		int minIndex = getMin(g);
		if (minIndex == NIL)
			return;

		AdjListNode *neighborNode = g->array[minIndex].head;

		//go through the neighbors of the node
		while (neighborNode != NULL)
		{
			if (g->array[neighborNode->dest].dValue > g->array[minIndex].dValue + neighborNode->cost)
			{
				g->array[neighborNode->dest].dValue = (g->array[minIndex].dValue + neighborNode->cost); //set dValue to our calc'd cost
				g->array[neighborNode->dest].pred = minIndex;
			}

			neighborNode = neighborNode->next; //move to next neighbor
		}
		g->array[minIndex].color = BLACK; //set node as traversed
	}
}

/* int isEmpty(Graph *)
 * Checks if the graph is empty, returns 1 if empty.
 */
int isEmpty(Graph *g)
{
	//if graph is null, error
	if (g == NULL)
		return NIL;

	//check if any node is white
	for (int i = 0; i < g->V; i++)
	{
		if (g->array[i].color == WHITE)
			return 0; //found one, not empty
	}
	return 1; //not found, empty
}

/* int getMin(Graph *)
 * Gets the node with the smallest dValue in the graph that's white
 */
int getMin(Graph *g)
{
	//if graph is null, error
	if (g == NULL)
		return NIL;

	int small_value = INF; //keep track of value, set to intmax for comparison/set
	int small_index;	   //keep track of index

	//try and find a dValue smaller than our tracked smallest
	for (int i = 0; i < g->V; i++)
	{
		if (g->array[i].color == WHITE && g->array[i].dValue < small_value)
		{
			small_value = g->array[i].dValue; //Found one! Set our values.
			small_index = i;
		}
	}
	//if no change from init, error
	if (small_value == INT_MAX)
		return NIL;

	return small_index;
}
