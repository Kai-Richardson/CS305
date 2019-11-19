/*
 * Author: Tammy VanDeGrift, Tanya Crenshaw, Martin Cenek
 * Additions by Kai Richardson
 * graph.c
 * Graph function implementations, based on adjacency list
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

/*
 * makeAdjListNode
 * makes new adjacency list node using destination node value and cost to the
 * node
 */
AdjListNode *makeAdjListNode(int dest, int cost)
{
	// costs cannot be negative
	if (cost < 0)
		return NULL;
	// dest cannot be negative
	if (dest < 0)
		return NULL;

	AdjListNode *newNode = (AdjListNode *)malloc(sizeof(AdjListNode));

	// malloc may have failed.
	if (newNode == NULL)
		return NULL;

	// Initialize all the fields with the values coming in
	// via function parameters.
	newNode->dest = dest;
	newNode->cost = cost;
	return newNode;
}

/*
 * initialize
 * create new graph object with V vertices and labels for the vertices
 */
Graph *initialize(int V, char *labels[])
{
	// Check that input parameters are well-formed; otherwise,
	// return NULL to indicate nothing was created.
	if (V <= 0 || labels == NULL)
		return NULL;

	Graph *graph = (Graph *)malloc(sizeof(Graph));

	// malloc may have failed.
	if (graph == NULL)
		return NULL;
	// Initialize the number of nodes.
	graph->V = V;
	// Create an array of adjacency lists.  Size of array is V.
	graph->array = (AdjList *)malloc(V * sizeof(AdjList));

	// malloc may have failed.
	if (graph->array == NULL)
	{
		free(graph);
		return NULL;
	}

	// Create a jump table of labels to node numbers.  Simply
	// use the string array that was handed to this function.
	graph->jump = labels;
	// Initialize each adjacency list as empty by making head as NULL
	// and labeling the node using the appropriate element from the
	// label array.
	int i;
	for (i = 0; i < V; ++i)
	{
		graph->array[i].pred = NIL;
		graph->array[i].color = WHITE;
		graph->array[i].dValue = INF;
		graph->array[i].head = NULL;
		strcpy(graph->array[i].label, labels[i]);
	}
	return graph;
}

/*
 * addEdge
 * Add an edge to an undirected graph using the src, dest, and cost for the
 * edge.
 */
int addEdge(Graph *graph, char *src, char *dest, int cost)
{
	// check arguments
	if (graph == NULL || src == NULL || dest == NULL)
		return ADD_PARAM_FAILURE;
	if (cost < 0)
		return ADD_COST_FAILURE;

	// Add an edge from src to dest.  A new node is added to the adjacency
	// list of src.  The node is added to the beginning of the list.

	// look up the source name
	int i = 0;
	int srcNum = -1;
	while (i < graph->V && srcNum == -1)
	{
		if (strncmp(src, graph->array[i].label, MAXWIDTH) == 0)
		{
			srcNum = i;
		}
		i++;
	}

	// look up the dest name
	i = 0;
	int destNum = -1;
	while (i < graph->V && destNum == -1)
	{
		if (strncmp(dest, graph->array[i].label, MAXWIDTH) == 0)
		{
			destNum = i;
		}
		i++;
	}

	// If the source's name or destination's name couldn't be found,
	// then return a failure code.
	if (srcNum == -1 || destNum == -1)
		return ADD_NOT_FOUND;

	// Create a new node.  Make sure it was created successfully.
	AdjListNode *newNode = makeAdjListNode(destNum, cost);
	if (newNode == NULL)
		return ADD_ALLOC_FAILURE;

	// Add the new node to the appropriate linked list.
	newNode->next = graph->array[srcNum].head;
	// Put new node at beginning
	graph->array[srcNum].head = newNode;

	return ADD_SUCCESS;
}

/*
 * printLabels
 * print all labels and their integer values
 * helpful for debugging
 */
void printLabels(Graph *graph)
{
	// cannot print labels for NULL graph
	if (graph == NULL)
		return;

	int v;
	for (v = 0; v < graph->V; ++v)
	{
		printf("City %d: %s.  dValue: %d\n", v, graph->jump[v],
			   graph->array[v].dValue);
	}
	return;
}

/*
 * printGraph
 * prints the array of adjacency lists for the graph
 * helpful for debugging
 *
 */
void printGraph(Graph *graph)
{
	// cannot print labels for an empty graph.
	if (graph == NULL)
		return;

	int v;
	// For each adjacency list, print every node in the adjacency list,
	// using the graph's jump table to convert from a vertex's integer
	// value to a label.
	for (v = 0; v < graph->V; ++v)
	{
		AdjListNode *curr = graph->array[v].head;
		printf("\n Adjacency list for city #%d: %s\n", v, graph->array[v].label);

		// As long as the adjacency list still has nodes...
		while (curr != NULL)
		{
			printf("-> %s ", graph->jump[curr->dest]);
			curr = curr->next;
		}
		printf("\n");
	}
	return;
}

/*
 * freeGraph
 * frees all memory allocated to the graph
 */
void freeGraph(struct Graph **graphAddr, char ***airports, int numPorts)
{
	// check if graph and airports are non null
	if (graphAddr == NULL || airports == NULL)
		return;

	for (int i = 0; i < numPorts; i++)
	{
		free((*airports)[i]);
	}
	free((*airports));

	int num_of_verts = (*graphAddr)->V;

	for (int i = 0; i < num_of_verts; i++)
	{
		AdjListNode *node = (*graphAddr)->array[i].head;
		AdjListNode *holder;

		while (node != NULL)
		{
			holder = node->next;
			free(node);
			node = holder;
		}
	}

	free((*graphAddr)->array);
	free((*graphAddr));
}

