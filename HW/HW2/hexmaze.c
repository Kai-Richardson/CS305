#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hexcell.h"
#include "load.h"
#include "hexmaze.h"


/* print_board
* args: pointer to the current board struct
* out: void
* prints the hexboard board:
    if hexcell color is path, print 'P'
    if hexcell has an obstacle, print 'X'
    otherwise print '0'
*/
void print_board(board* board){

    for (int j=0; j<board->max_col;j++)
        printf("/ \\ ");
    printf("\n");
    for (int i = 0; i<board->max_row;i++){
        for (int j=0; j<board->max_col;j++){
            if(i%2 && j == 0) printf("  ");
        printf("|%c| ",(board->hexcells[i][j].color==path?'P':(board->hexcells[i][j].obstacle==-1?'X':'0')));
    }
    printf("\n");

    for (int j=0; j<board->max_col;j++){
        if(j == 0 && i%2)
            printf("/ \\ / ");
        else
            printf("\\ / ");
        }
        printf("\n");
    }
    printf("\n");
return;

}

//find path

int find_path(char *f_name)
{
	int result;
	board *hexboard;

	hexboard = file_load(f_name);

	if (hexboard)
	{
		print_board(hexboard);

		if (start_search(hexboard))
		{
			printf("Success: Here is a path.");
		}
		else
		{
			printf("Could not find a path. Board could not be solved.");
		}

		print_board(hexboard);
		printf("Thanks for playing!");
		free_board(hexboard);
		result = 1;
	}
	else
	{
		fprintf(stderr, "Could not create board or read from file.");
		result = 0;
	}

	return result;
}

//free board

void free_board(board* hexboard) {
    for (int i = 0; i < hexboard->max_row; i++)
    {
        free(hexboard->hexcells[i]);
    }
    free(hexboard->hexcells);
    free(hexboard);

}

//start search

int start_search(board* hexboard) {
  if ( hexboard->hexcells[hexboard->start_row][hexboard->start_col].obstacle != yes
    && hexboard->hexcells[hexboard->end_row][hexboard->end_col].obstacle != yes )
  {
    return search(hexboard, hexboard->start_row, hexboard->start_col);
  }
  printf("Start or end cell are obstacles board cannot be solved");
  return 0;
}

//search board

int search(board* hexboard, int row, int col) {
    int result;

    if (row < 0 || col < 0 || hexboard->max_row - 1 < row || hexboard->max_col - 1 < col) {
        return 0;
    }
    if (hexboard->end_col != col || hexboard->end_row != row)
    {
        if (hexboard->hexcells[row][col].obstacle != yes && hexboard->hexcells[row][col].color == white)
        {
            hexboard->hexcells[row][col].color = 3;
            result = (search(hexboard, row-1, col-1)\
                   || search(hexboard, row-1, col  )\
                   || search(hexboard, row  , col+1)\
                   || search(hexboard, row+1, col  )\
                   || search(hexboard, row+1, col-1)\
                   || search(hexboard, row  , col-1));
        }
        else
        {
            result = 0;
        }
    }
    else
    {
        printf("------------------------Found Path-----------------------");
        result = 1;
    }
    return result;
}