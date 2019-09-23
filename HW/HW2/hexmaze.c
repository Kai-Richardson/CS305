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
            if(i%2&&j==0) printf("  ");
        printf("|%c| ",(board->hexcells[i][j].color==path?'P':(board->hexcells[i][j].obstacle==-1?'X':'0')));
    }
    printf("\n");
 
    for (int j=0; j<board->max_col;j++){
        if(j==0&& i%2)
            printf("/ \\ / ");
        else
            printf("\\ / ");
        }
        printf("\n");
    }
    printf("\n");
return;

}
