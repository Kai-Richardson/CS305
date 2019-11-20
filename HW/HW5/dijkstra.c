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

int isEmpty(Graph *g)
{
    if (g == NULL)
        return 1;

    int num_of_verts = g->V;

    for (int i = 0; i < num_of_verts; i++)
    {
        if (g->array[i].color == WHITE)
            return 0;
    }

    return 1;
}

int getMin(Graph *g)
{
    if (g == NULL)
        return -1;

    int small_index;



}