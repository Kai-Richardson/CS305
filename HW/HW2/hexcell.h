#ifndef HEXCELL_H
#define HEXCELL_H

// board's hexcell obstacle
typedef enum {yes=-1, no=0} obstacles;

// board's hexcell colors
typedef enum {white=1, visited=2, path=3} colors;

// 2D array row_max x col_max of hexcell struct defines the playing board
typedef struct hexcell{
   colors color;
   obstacles obstacle;
}hexcell;

#endif