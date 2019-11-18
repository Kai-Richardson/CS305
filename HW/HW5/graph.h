/*
 * Author: Tammy VanDeGrift, Tanya Crenshaw, Martin Cenek
 * graph.h
 * header file for graph implementation information
 * based on www.geeksforgeeks.org/graph-and-its-representations/
 */

#include <limits.h>   //for INT_MAX

#ifndef _GRAPH_H_
#define _GRAPH_H_

#define MAXWIDTH 3   // airport names are 3 char long

// for error codes and return values
#define ADD_SUCCESS 1
#define ADD_COST_FAILURE -1
#define ADD_NOT_FOUND -2
#define ADD_PARAM_FAILURE -3
#define ADD_ALLOC_FAILURE -4

// for dijkstra's algorithm
#define WHITE 1
#define BLACK 2
#define NIL -1
#define INF INT_MAX

/* Structs */

/* A structure to represent an adjacency list node. An adjacency
   list node contains the value of the node as well as the 
   cost to that node, in addition to a pointer to the next node
   in the list
*/
typedef struct AdjListNode {
  int dest;                    // numerical value of node
  int cost;
  struct AdjListNode* next;
} AdjListNode;
 
/* A structure to represent an adjacency list array.  Each entry of the
   adjacency list array contains the label of the node as well as
   a pointer to the head of the list of nodes detailing to whom this node
   is connected.
*/
typedef struct AdjList {
  char label[MAXWIDTH + 1];   // name of the node
  int pred;                   // The index of the predecessor to this node, 
                              // initially -1.
  int color;                  // The color of this node, initially white.
  int dValue;                 // The total distance from the source to this 
                              // node, initially -1.
  AdjListNode *head;          // pointer to head node of list
} AdjList;

/* A structure to represent a graph. A graph is an array of
   adjacency lists.  Size of array will be V (number of vertices in
   graph).  The jump table is array mapping node numbers to
   labels.  
*/
typedef struct Graph {
  int V;                     // number of vertices in graph
  char ** jump;              // maps node numbers to labels
  struct AdjList* array;     // array of adjacency lists
} Graph;

// function prototypes for functions defined in graph.c
AdjListNode * makeAdjListNode(int dest, int cost);
Graph * initialize(int V, char * labels[]);
int addEdge(Graph * graph, char * src, char * dest, int cost);
void printGraph(Graph * graph);
void printLabels(Graph * graph);
void freeGraph(Graph ** graphAddr, char***);

#endif
