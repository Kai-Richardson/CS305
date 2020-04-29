/*
 * Author: Tammy VanDeGrift, Tanya Crenshaw, Martin Cenek
 * dijkstra's algorithm
 * sets the distances in the graph
 * students program this part (new file)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "graph.h"

void dijkstra(Graph* graph, AdjList* src) {
  // At the start, the nodes are all colored white, as per the
  // graph initialization function.  If dijkstra was being called more
  // than once, we'd have to color the nodes white again.
  
  // Add everyone to the queue.  For this implementation, the "Queue"
  // comprises all the nodes in the graph that are white.

  if(graph==NULL) return;
  // Set the dValue of the source to 0.
  src->dValue = 0;
  
  int empty = 0;
  // While the queue is not empty...
  while(!empty) {
    // set graph empty flag and there must exist at least one white node
    // to reset the flag
    GHashTableIter iter;
    gpointer key, value;
    empty = 1;
    g_hash_table_iter_init (&iter, graph->array);
    while (g_hash_table_iter_next (&iter, &key, &value) && empty){
      if (((AdjList*)value)->color == WHITE)
        empty = 0;
    }
    //g_hash_table_foreach(graph->array, (GHFunc)isEmpty, &empty);
    if(empty == 1) return;

    // Get the next item out of the queue.  It is the white
    // node with the smallest dValue.
    AdjList* u = NULL;
    g_hash_table_iter_init (&iter, graph->array);
    while (g_hash_table_iter_next (&iter, &key, &value)){
        if(u == NULL){
          if(((AdjList*)value)->color == WHITE){
            u=(AdjList*)value;
          }
        }else{
          if(((AdjList*)value)->dValue < u->dValue){
            if(((AdjList*)value)->color == WHITE){
              u=(AdjList*)value;
            }
          }
        }
      }
    //g_hash_table_foreach(graph->array, (GHFunc)getMin, &u);
    if (u == NULL){
      return; // if not all destinations reachable u=-1->Stop
    }
    // Examine all the neighbors of this node.      
    AdjListNode* neighbor =  u->head;
    while(neighbor != NULL) {
      AdjList* edgeNeighbor = neighbor->dest;
      int edgeCost = neighbor->cost;
      // One at a time, relax the edges.
      if(edgeNeighbor->dValue > u->dValue + edgeCost) {
	       // Update the dValue.
	      edgeNeighbor->dValue = u->dValue + edgeCost;
	      // Update the pred.
	      edgeNeighbor->pred = u;
      }
      
      // Go to the next neighbor.
      neighbor = neighbor->next;  
    }
    
    // I've looked at all the neighbors of node u, so color
    // it BLACK to indicate that it is no longer in the queue.
    u->color = BLACK;
  } 
}

/*
 * getMin
 *
 * Given a pointer to the graph, return the index of the WHITE
 * node with the smallest dValue.
 *
 */
void getMin (gpointer key, gpointer value, AdjList** minNode) {
  if(*minNode == NULL){
    if(((AdjList*)value)->color == WHITE){
      *minNode=(AdjList*)value;
    }
  }else{
    if(((AdjList*)value)->dValue < (*minNode)->dValue){
      if(((AdjList*)value)->color == WHITE){
        *minNode=(AdjList*)value;
      }
      return;
    }
  }
}


/*
 * isEmpty
 *
 * return 0 if there are any white
 * nodes in the graph and 1 otherwise.
 *
 */
void isEmpty(gpointer key, gpointer value, int* empty) {
  if (((AdjList*)value)->color == WHITE)
    *empty = 0;
}

