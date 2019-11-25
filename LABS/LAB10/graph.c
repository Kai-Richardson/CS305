/*
 * CS 305 Lab 10
 * Tammy VanDeGrift
 * Graph -- adjacency matrix representation for a directed, weighted graph
 */

#include <stdio.h>
#include <stdlib.h>

typedef enum
{
  white,
  gray,
  black
} COLOR;

typedef struct Graph
{
  int V;   //number of vertices in G
  int **M; //2D array of ints, adjacency matrix
} Graph;

typedef struct DFS
{
  COLOR color; // white, gray, or black
  int parent;
  int discover;
  int finish;
} DFS;

int time = 0; // note that this is a global variable (not great programming
              // practice) but need to have a global time count for DFS
              // it would be better to pass in a pointer to a variable that
              // stores the time that dfs could access and update, but
              // for the purpose of keeping this lab simple, we have a
              // global variable

// prototypes
Graph *createEmptyGraph(int numVertices);
int addEdge(Graph *g, int src, int dest);
int outDegree(Graph *g, int v);
int inDegree(Graph *g, int v);
int degree(Graph *g, int v);
void freeGraph(Graph *g);
void printGraph(Graph *g);
int isNeighbor(Graph *g, int x, int y);
DFS *dfsInit(Graph *g);
void dfs(Graph *g, DFS arr[], int src);
int getDistance(Graph *g, DFS arr[], int src, int dest);
void printReversePath(Graph *g, DFS arr[], int src, int dest);

/* main creates a graph and processes it (degrees, neighbors, DFS, paths) */
int main(void)
{
  // create graph
  printf("Creating graph.\n");
  Graph *g = createEmptyGraph(6);
  int ok1 = addEdge(g, 0, 5);
  int ok2 = addEdge(g, 0, 3);
  int ok3 = addEdge(g, 1, 2);
  int ok4 = addEdge(g, 3, 5);
  int ok5 = addEdge(g, 4, 3);
  int ok6 = addEdge(g, 2, 1);
  int ok7 = addEdge(g, 2, 3);
  int ok8 = addEdge(g, 1, 0);
  int ok9 = addEdge(g, -2, 0);
  int ok10 = addEdge(g, 2, 4);
  int ok11 = addEdge(g, 5, 4);
  int ok12 = addEdge(g, 4, -1);
  int ok13 = addEdge(g, 5, 1);
  int ok14 = addEdge(g, 7, 2);
  int ok15 = addEdge(g, 3, 1);
  int ok16 = addEdge(g, 2, 1);

  printf("\n");
  printGraph(g);

  // print degree information
  printf("out degree of 0: %d\n", outDegree(g, 0));
  printf("in degree of 0: %d\n", inDegree(g, 0));
  printf("total degree of 0: %d\n", degree(g, 0));
  printf("\n");

  // print neighbor information
  printf("Neighbors of 0:\t");
  int i;
  for (i = 0; i < g->V; i++)
  {
    if (isNeighbor(g, 0, i))
    {
      printf("%d  ", i);
    }
  }
  printf("\n\n");

  // print DFS information
  DFS *arr = dfsInit(g);
  dfs(g, arr, 0);
  for (i = 0; i < g->V; i++)
  {
    printf("Node %d: %d/%d, parent: %d\n", i, arr[i].discover, arr[i].finish, arr[i].parent);
  }

  // print paths
  printReversePath(g, arr, 0, 1);
  printReversePath(g, arr, 0, 2);
  printReversePath(g, arr, 0, 3);
  printReversePath(g, arr, 0, 4);
  printReversePath(g, arr, 0, 5);

  printf("Distance from 0 to 5: %d\n", getDistance(g, arr, 0, 5));
  printf("Distance from 0 to 1: %d\n", getDistance(g, arr, 0, 1));
  printf("Distance from 3 to 4: %d\n", getDistance(g, arr, 3, 4));
  printf("Distance from 0 to 4: %d\n", getDistance(g, arr, 0, 4));
  printf("Distance from 0 to 0: %d\n", getDistance(g, arr, 0, 0));

  freeGraph(g);
  return EXIT_SUCCESS;
}

/* createEmptyGraph sets up the graph data structure with numVertices */
Graph *createEmptyGraph(int numVertices)
{
  if (numVertices <= 0)
  {
    return NULL;
  }
  Graph *g = (Graph *)malloc(sizeof(Graph));
  if (g == NULL)
  {
    return NULL;
  }
  g->V = numVertices;
  g->M = (int **)malloc(sizeof(int *) * numVertices);
  int i;
  if (g->M != NULL)
  {
    for (i = 0; i < numVertices; i++)
    {
      g->M[i] = (int *)malloc(sizeof(int) * numVertices);
      if (g->M[i] == NULL)
      {
        freeGraph(g);
        return NULL;
      }
    }
  }
  int j;
  for (i = 0; i < numVertices; i++)
  {
    for (j = 0; j < numVertices; j++)
    {
      g->M[i][j] = 0;
    }
  }
  return g;
}

/* freeGraph frees all memory associated with the graph */
void freeGraph(Graph *g)
{
  if (g == NULL)
  {
    return;
  }
  int i;
  for (i = 0; i < g->V; i++)
  {
    free(g->M[i]);
  }
  free(g->M);
  free(g);
  g = NULL;
}

/* printGraph prints the graph as a matrix */
void printGraph(Graph *g)
{
  if (g == NULL)
  {
    return;
  }
  int i, j;
  printf("Matrix for graph:\n");
  for (i = 0; i < g->V; i++)
  {
    for (j = 0; j < g->V; j++)
    {
      printf("%d\t", g->M[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

///////////////////////////////////////////////////////////
// Lab exercises below
//////////////////////////////////////////////////////////

/* addEdge should do error-checking of the parameters and put a
   1 in the adjacency matrix at M[src][dest] */
int addEdge(Graph *g, int src, int dest)
{
  if (g == NULL)
  {
    printf("Graph is null. Cannot add edge.\n");
    return 0;
  }

  if ((src < 0 || src >= g->V) || (dest < 0 || dest >= g->V))
  {
    printf("Vertex invalid. Cannot add edge.\n");
    return 0;
  }

  if (g->M[src][dest] == 1)
  {
    printf("Edge already exists between %d and %d. Cannot add edge.\n", src, dest);
    return 0;
  }

  g->M[src][dest] = 1; //add edge in our matrix
  return 1;

  return 0;
}

/* outDegree returns the out degree of a vertex v */
int outDegree(Graph *g, int v)
{
  if (g == NULL)
  {
    return 0;
  }

  if (v < 0 || v >= g->V) //out-of-bounds check
  {
    return 0;
  }
  int edges = 0;

  for (int i = 0; i < g->V; i++)
  {
    edges += g->M[v][i]; //row-major lookup of endpoints
  }

  return edges;
}

/* inDegree returns the in degree of a vertex v */
int inDegree(Graph *g, int v)
{
  if (g == NULL)
  {
    return 0;
  }

  if (v < 0 || v >= g->V) //out-of-bounds check
  {
    return 0;
  }

  int edges = 0;
  for (int i = 0; i < g->V; i++)
  {
    edges += g->M[i][v]; //row-major lookup of startpoints
  }

  return edges;
}

/* degree returns the degree of a vertex v
 DONE FOR YOU */
int degree(Graph *g, int v)
{
  return inDegree(g, v) + outDegree(g, v);
}

/* isNeighbor returns 1 if edge (x, y), x to y, exists; 0 otherwise */
int isNeighbor(Graph *g, int x, int y)
{
  if (g == NULL)
  {
    return 0;
  }

  if ((x < 0 || x >= g->V) || (y < 0 || y >= g->V)) //out-of-bounds check
    return 0;

  int edges = 0;
  for (int i = 0; i < g->V; i++)
  {
    edges += g->M[x][y]; //row-major lookup of endpoints
  }

  return edges;
}

////////////////////////////////////////////////////////
// Depth First Search Code Below
///////////////////////////////////////////////////////

/* dfsInit initializes the array of DFS structs, so that the parent
   is -1 for all nodes, color is white for all nodes, and discover and finish
   times are -1 */
DFS *dfsInit(Graph *g)
{
  if (g == NULL || g->V <= 0)
  {
    time = 0;
    return NULL;
  }
  DFS *arr = malloc(sizeof(DFS) * g->V);
  int i;
  for (i = 0; i < g->V; i++)
  {
    arr[i].parent = -1;
    arr[i].color = white;
    arr[i].discover = -1;
    arr[i].finish = -1;
  }
  time = 0;
  return arr;
}

/* dfs does depth-first search of the graph from src, filling in the arr
   of DFS structs as it processes, should be recursive */
void dfs(Graph *g, DFS arr[], int src)
{
  // do DFS from src node in graph g
  if (g == NULL || arr == NULL)
  {
    return;
  }
  if (src < 0 || src >= g->V)
  {
    return;
  }

  if (src == 0)
  {
    printf("visited 0\n");
  }

  arr[src].color = gray;
  time++;
  arr[src].discover = time;

  for (int i = 0; i < g->V; i++)
  {
    if (isNeighbor(g, src, i))
    {
      if (arr[i].color == white)
      {
        arr[i].parent = src;
        dfs(g, arr, i);
      }
    }
  }
  arr[src].color = black;
  time++;
  arr[src].finish = time;

}

/* printReversePath prints the path from dest <- node <- node <- src <-
   note that you may assume that dfs has already filled in arr when
   doing dfs from the src */
void printReversePath(Graph *g, DFS arr[], int src, int dest)
{
  // print path from dest to src
  // note: assuming arr has values set from dfs from src
  if (g == NULL || arr == NULL)
  {
    printf("graph or arr is invalid. No path.\n");
    return;
  }
  // start with dest and put it into an array
  printf("PATH: %d <-", dest);
  int current = dest;

  while (arr[current].parent != -1)
  {
    printf("%d <-", arr[current].parent);
    current = arr[current].parent;
  }

  printf("\n");
}

//Returns distance from src to dest using the DFS data
int getDistance(Graph *g, DFS arr[], int src, int dest) {
  if (g == NULL || arr == NULL)
  {
    printf("graph or arr is invalid. No path.\n");
    return -1;
  }

  int ancestor = dest;
  int distance = 0;

  while (arr[ancestor].parent != -1)
  {
    distance++;
    if (arr[ancestor].parent == src)
    {
      return distance;
    }
    ancestor = arr[ancestor].parent;
  }

  return -1;
}