/*
 * Author: Tammy VanDeGrift, Tanya Crenshaw, Martin Cenek
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
AdjListNode * makeAdjListNode(AdjList* dest, int cost) {
  // costs cannot be negative
  if (cost < 0) return NULL;
  // dest cannot be negative
  if (dest == NULL) return NULL;
  
  AdjListNode * newNode = (AdjListNode*) malloc(sizeof(AdjListNode));
  
  // malloc may have failed.
  if (newNode == NULL) return NULL;
  
  // Initialize all the fields with the values coming in
  // via function parameters.
  newNode->dest = dest;
  newNode->cost = cost;  
  return newNode;
}

/*
  resets the graph's adjacency edge pred, color, d_value so
  dijkstra can run on the graph multiple times
*/
void reset (gpointer key, gpointer value, gpointer user_data) {
    ((AdjList*)value)->pred = NULL;
    ((AdjList*)value)->color = WHITE;
    ((AdjList*)value)->dValue = INF;    
}

/*
 * buildThisGraph
 * construct edges from airport to airport
 */
Graph* buildGraph(char* fn) {
  FILE* fp = fopen(fn, "r");
  if (fp==NULL){
    printf("ERROR: Could not open file for reading\n");
    return NULL;
  }
  Graph* graph = (Graph*) malloc(sizeof(Graph));
  // malloc may have failed.
  if (graph == NULL) return NULL;   
  // Initialize the number of nodes.

  // Read and Check number of cities; otherwise,
  // return NULL to indicate nothing was created.
  fscanf(fp,"%d\n", &(graph->V));
  if( graph->V <= 0) return NULL;
  
  // Create an array of adjacency lists.  Size of array is V.
  graph->array = g_hash_table_new(g_str_hash, g_str_equal);
  //(AdjList*) malloc(graph->V * sizeof(AdjList));
  
  // malloc may have failed.
  if (graph->array == NULL) {
    free(graph);
    return NULL;  
  }
  
  // Initialize the graph data structure.
  // Initialize each adjacency list as empty by making head as NULL
  // and labeling the node using the name read from the file
  char name[MAXWIDTH+1], or[MAXWIDTH+1], dest[MAXWIDTH+1];
  name[MAXWIDTH]='\0';
  int dist;
  or[MAXWIDTH]='\0';
  dest[MAXWIDTH]='\0';
  for(int i=0;i<graph->V; i++){
    fscanf(fp,"%3s\n", name);
    AdjList* AirportNode = (AdjList*) malloc(sizeof(AdjList));
    AirportNode->label[MAXWIDTH] = '\0';
    AirportNode->pred = NULL;
    AirportNode->color = WHITE;
    AirportNode->dValue = INF;    
    AirportNode->head = NULL;
    strncpy(AirportNode->label,name, MAXWIDTH);
    g_hash_table_insert(graph->array, AirportNode->label, AirportNode);
  } 
  // Initialize the graph's edges.
  while (fscanf(fp,"%3s %3s %d\n", or, dest, &dist)==3){
    addEdge(graph, or, dest, dist);
  }
  fclose(fp);
  return graph;
}

/*
 * addEdge
 * Add an edge to an undirected graph using the src, dest, and cost for the 
 * edge.
 */
int addEdge(Graph* graph, char* src, char* dest, int cost) {
  // check arguments
  if (graph == NULL || src == NULL || dest == NULL) return ADD_PARAM_FAILURE;
  if (cost < 0) return ADD_COST_FAILURE;

  // Add an edge from src to dest.  A new node is added to the adjacency
  // list of src.  The node is added to the beginning of the list.
   // look up the source name
  AdjList* AirportNodeSrc = g_hash_table_lookup(graph->array, src);
  AdjList* AirportNodeDest = g_hash_table_lookup(graph->array, dest);

  // If the source's name or destination's name couldn't be found,
  // then return a failure code.
  if(AirportNodeSrc == NULL ||  AirportNodeDest==NULL){
    fprintf(stderr, "Could not add edge: Src/Dest airport does not exist");
    return ADD_NOT_FOUND; 
  }
 
  // Create a new node.  Make sure it was created successfully.
  AdjListNode* newNode = makeAdjListNode(AirportNodeDest, cost);
  if(newNode == NULL) return ADD_ALLOC_FAILURE;

  // Add the new node to the appropriate linked list.
  newNode->next = AirportNodeSrc->head;
  // Put new node at beginning
  AirportNodeSrc->head = newNode;

  return ADD_SUCCESS;
}

/*
* iterator printer function passed to hash's foreach as a function pointer
* argument
*/
void iteratorLabel(gpointer key, gpointer value, gpointer user_data) {
 printf(user_data, (char*)key, ((AdjList*)value)->dValue);
}

/*
 * printLabels
 * print all labels and their integer values
 * helpful for debugging
 */
void printLabels(Graph* graph) {
  // cannot print labels for NULL graph
  if(graph == NULL) return;
  GHashTableIter iter;
  gpointer key, value;
  g_hash_table_iter_init (&iter, graph->array);
  while (g_hash_table_iter_next (&iter, &key, &value)){
    printf("City %3s.  dValue: %d\n", (char*)key, ((AdjList*)value)->dValue);
  }     
  //g_hash_table_foreach(graph->array, (GHFunc)iteratorLabel, "City %3s.  dValue: %d\n");
  return;
}

/*
* iterator printer function passed to hash's foreach as a function pointer
* argument
*/
void iteratorGraph(gpointer key, gpointer value, gpointer AirportHash) {
 printf("\nAdjacency list for city: %3s\n", ((AdjList*)value)->label);
 AdjListNode* curr = ((AdjList*)value)->head;
 while (curr != NULL) {
    AdjList* tmp = g_hash_table_lookup((GHashTable*)AirportHash, curr->dest->label);
    printf("-> %3s ", tmp->label);
    curr = curr->next;
  }
  printf("\n");
}

/*
 * printGraph
 * prints the array of adjacency lists for the graph
 * helpful for debugging
 *
 */
void printGraph(Graph* graph) {
  // cannot print labels for an empty graph.
  if(graph == NULL) return;
  
  // For each adjacency list, print every node in the adjacency list,
  GHashTableIter iter;
  gpointer key, value;
  g_hash_table_iter_init (&iter, graph->array);
  while (g_hash_table_iter_next (&iter, &key, &value)){
    printf("\nAdjacency list for city: %3s\n", ((AdjList*)value)->label);
    AdjListNode* curr = ((AdjList*)value)->head;
    while (curr != NULL) {
      //AdjList* tmp = g_hash_table_lookup((GHashTable*)AirportHash, curr->dest->label);
      printf("-> %3s ", curr->dest->label);
      curr = curr->next;
    }
    printf("\n");
  }

  //g_hash_table_foreach(graph->array, (GHFunc)iteratorGraph, graph->array);
  return;
}
/*
free adjList nodes
*/
void freeAdjList(gpointer key, gpointer value, gpointer temp){
    AdjListNode* curr = ((AdjList*)value)->head;
    while (curr != NULL) {
      AdjListNode* nxt = curr->next;
      free(curr);
      curr=nxt;
    }
}
/*
 * freeGraph
 * frees all memory allocated to the graph
 */
void freeGraph(struct Graph ** graphAddr) {
  if(graphAddr == NULL) return;
  GHashTableIter iter;
  gpointer key, value;
  g_hash_table_iter_init (&iter, (*graphAddr)->array);
  while (g_hash_table_iter_next (&iter, &key, &value)){
    AdjListNode* curr = ((AdjList*)value)->head;
    while (curr != NULL) {
      AdjListNode* nxt = curr->next;
      free(curr);
      curr=nxt;
    }
  }
  //g_hash_table_foreach((*graphAddr)->array, (GHFunc)freeAdjList, NULL);
  g_hash_table_destroy((*graphAddr)->array);
  free(*graphAddr);
  // set the pointer to NULL
  *graphAddr = NULL;


}
