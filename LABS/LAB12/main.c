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
#include <glib.h>
#include "main.h"
#include "graph.h"

/* 
 * main
 * Creates a graph of airports and runs dijkstra's algorithm to find 
 * the shortest path from a source airport to a destination airport.
 * usage: hw6 SampleRoutes.txt PDX MCO
 */
int main(int argc, char * argv[]) {
  // Check command line arguments.
  if(argc != REQ_PARAM) {
    usage(argv[0]);
  }
  Graph* graph = buildGraph(argv[1]);
  if (graph == NULL ) exit(0);
  // Sort the array of airport names lexicographically using the built-in
  // C function qsort().
  //qsort(airports, sizeof(airports)/sizeof(*airports), sizeof(*airports), compare);

  //printf("Creating a graph for %d airports.\n", numberOfAirports);

  // Given a number and a list of labels, initialize a graph data structure
  // for that many nodes, labeled with the labels.
  // &numberOfAirports does not exist any more get it from graph->V

  //printGraph(graph);

  printf("Enter search source and destination airports separated by space\n");
  printf("Non existant airport will terminate the program\n");
  printf("Usage Example: \"PDX ATL\"\n");
  char source[MAXWIDTH+1], dest[MAXWIDTH+1];
  source[MAXWIDTH]='\0';
  dest[MAXWIDTH]='\0';
  while(scanf("%3s %3s", source, dest)==2){
  	 // Are the city names too long?
    if(strlen(source) > MAXWIDTH) {
      err(source);
    }
  	if(strlen(dest) > MAXWIDTH) {
    	err(dest);
  	}
  
    // Are the names given at the command line in the list of airports?
	  AdjList* AirportNodeSrc = g_hash_table_lookup(graph->array, source);
    AdjList* AirportNodeDest = g_hash_table_lookup(graph->array, dest);
    if(AirportNodeSrc==NULL ||AirportNodeDest==NULL){
      fprintf(stderr, "Source or Dest Airport not in graph, cannot lookup route");
      break;
    }

    printf("\n------------------------------\n\n");

    // Find the shortest paths and print the result.  
    dijkstra(graph, AirportNodeSrc);
    //printLabels(graph);

    printf("\n------------------------------\n\n");
  
    // Start at the destination, and going backwards to the source
    // print all hops from the source to the destination.

    printf("Getting the path from %s to %s. \n", AirportNodeSrc->label, AirportNodeDest->label);
    printf("%s ", AirportNodeSrc->label);
    //printf("Dest %s c: %d dV: %d", AirportNodeDest->label,AirportNodeDest->color,AirportNodeDest->dValue);
    
    if(AirportNodeDest->dValue < 0)
      printf("Destination is not reachable, try again\n");
    else{
      printPath(AirportNodeDest);
    
      // Print the total mileage.
        printf(" %d miles.\n", AirportNodeDest->dValue);
      }
      printf("\n------------------------------\n");
      
      //reset each node of graph
      GHashTableIter iter;
      gpointer key, value;
      g_hash_table_iter_init (&iter, graph->array);
      while (g_hash_table_iter_next (&iter, &key, &value)){
        ((AdjList*)value)->pred = NULL;
        ((AdjList*)value)->color = WHITE;
        ((AdjList*)value)->dValue = INF;    
      }
      //g_hash_table_foreach(graph->array, (GHFunc)reset, NULL);
      }
    freeGraph(&graph);

  return EXIT_SUCCESS;
}

void printPath(AdjList* airport){
  if(airport->pred == NULL)
    return;
  else{
    printPath(airport->pred);
    printf("-> %s ", airport->label);
  }
}

/*
 * compare
 * Compare two strings.  That is, given two elements, extract the char
 * pointers from them and compare the strings using strncmp().
 */
int compare (const void * elem1, const void * elem2) {
  
  char * s1 = *(char **)elem1;
  char * s2 = *(char **)elem2;
  
  return  strncmp(s1, s2, MAXWIDTH); 
}


/* 
 * usage
 * Print the usage for this program and exit program.
 */
void usage(char * s) {
  printf("usage: %s <source city name> <dest. city name>\n", s);
  printf("  This program finds the shortest flight path from the given source city to destination.\n");
  exit(-1);
}

/* 
 * err
 * Print an error message for this program and exit proram.
 */
void err(char * s) {
  printf("%s is not in this set of airports.\n", s);
  exit(-1);
}
