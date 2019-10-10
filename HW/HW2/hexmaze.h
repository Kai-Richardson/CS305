#ifndef HEXMAZE_H
#define HEXMAZE_H

#include "hexcell.h"
#include "stdio.h"
#include "stdlib.h"

// hexboard struct -- height/width defined as row_max col_max
// start cell defined as start_row start_col cooridnates
// goal cell defined as end_row end_col coordinates
// hexcells is 2D array of
typedef struct board {
  int max_row;
  int max_col;
  int start_col;
  int start_row;
  int end_col;
  int end_row;
  hexcell** hexcells;
} board;

/* function prototypes */
int find_path(char*);
int start_search(board*);
int search(board*, int, int, int, int);
int check_board(board*);
int is_safe(int, int, int, int);
void print_board(board*);
void free_board(board*);

#endif
