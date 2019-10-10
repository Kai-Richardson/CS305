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
    if hexcell color is a successful path, print 'P'
    if hexcell color if a visited path, print 'V'
    if hexcell color is the origin point, print 'O'
    if hexcell color is the goal point, print 'G'
    if hexcell has an obstacle, print 'X'
    otherwise print '0'
*/
void print_board(board *board)
{

    for (int j = 0; j < board->max_col; j++)
        printf("/ \\ ");
    printf("\n");
    for (int i = 0; i < board->max_row; i++)
    {
        for (int j = 0; j < board->max_col; j++)
        {
            if (i % 2 && j == 0)
                printf("  ");
            char c = '0';
            if (board->hexcells[i][j].color == path)
            {
                c = 'P';
            }
            else if (board->hexcells[i][j].color == visited)
            {
                c = 'V';
            }
            else if (board->hexcells[i][j].color == origin)
            {
                c = 'O';
            }
            else if (board->hexcells[i][j].color == goal)
            {
                c = 'G';
            }
            else if (board->hexcells[i][j].obstacle == yes)
            {
                c = 'X';
            }
            printf("|%c| ", c);
        }
        printf("\n");

        for (int j = 0; j < board->max_col; j++)
        {
            if (j == 0 && i % 2)
                printf("/ \\ / ");
            else
                printf("\\ / ");
        }
        printf("\n");
    }
    printf("\n");
    return;
}

/* find_path
    args: char* f_name - File pointer that contains the hex data.
    returns: integer - if it encounters an error or runs fine
    operation:
        loads hexboard
        prints hexboard data
        starts search on hexboard
        prints finished hexboard if successful
        frees memory
*/
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
            printf("Success! There is a path.\n");
        }
        else
        {
            printf("Could not find a path. Board could not be solved.\n");
        }

        print_board(hexboard);
        printf("Thanks for playing!\n");
        free_board(hexboard);
        result = 1;
    }
    else
    {
        fprintf(stderr, "Could not create board or read from file.\n");
        result = 0;
    }

    return result;
}

/* free_board
    args: board* hexboard - our hexboard to free
    returns: void
    operation:
        frees all the rows/cols of the hexboard
        frees the hexcell array in the hexboard
        frees the hexboard
*/
void free_board(board *hexboard)
{
    for (int i = 0; i < hexboard->max_row; i++)
    {
        free(hexboard->hexcells[i]);
    }
    free(hexboard->hexcells);
    free(hexboard);
}

/* start_search
    args: board* hexboard - our hexboard to search
    returns: int - if it was solved or not
    operation:
        checks to make sure start and end aren't blocked
        sets origin cell to origin color
        calls the search method
        returns the result of the search method
*/
int start_search(board *hexboard)
{
    if (hexboard->hexcells[hexboard->start_row][hexboard->start_col].obstacle == no && hexboard->hexcells[hexboard->end_row][hexboard->end_col].obstacle == no)
    {
        hexboard->hexcells[hexboard->start_row][hexboard->start_col].color = origin;
        return search(hexboard, hexboard->start_row, hexboard->start_col, 99, 99);
    }
    printf("The start cell or the end cell are obstacles; board cannot be solved.\n");
    return 0;
}

/* search
    args:
        board* hexboard - our hexboard to search
        int row - row to use
        int col - col to use
    returns: int - if it found a path or not
    operation:
        checks if the passed row/col values are valid - used for bounds checking
        if at the goal - return that we made it and set current cell to goal
        if we haven't changed the color of this cell, mark it as visited
        call search function on neighbor cells
        if successful, mark current cell as a successful path
*/
int search(board *hexboard, int row, int col, int pr, int pc)
{
    int result;

    if (row < 0 || col < 0 || hexboard->max_row - 1 < row || hexboard->max_col - 1 < col) {
        printf("illegal: r%d c%d, pr%d pc%d\n", row, col, pr, pc);
        return 0;}
    if (hexboard->end_col != col || hexboard->end_row != row)
    {
        if (hexboard->hexcells[row][col].obstacle == no && (hexboard->hexcells[row][col].color == white || hexboard->hexcells[row][col].color == origin))
        {
            //Mark as visited if we haven't changed this already.
            if (hexboard->hexcells[row][col].color == white)
                hexboard->hexcells[row][col].color = visited; //Don't set origin/goal to path.
            result = (search(hexboard, row - 1, col - 1, row, col)
            || search(hexboard, row - 1, col, row, col)
            || search(hexboard, row, col + 1, row, col)
            || search(hexboard, row + 1, col, row, col)
            || search(hexboard, row + 1, col - 1, row, col)
            || search(hexboard, row, col - 1, row, col));

            //If successful, mark this as a successful path.
            if (result)
            {
                if (hexboard->hexcells[row][col].color == visited)
                    printf("yee: r%d c%d, pr%d pc%d\n", row, col, pr, pc);
                    hexboard->hexcells[row][col].color = path;
            }
        }
        else
        {
            printf("no: r%d c%d, pr%d pc%d\n", row, col, pr, pc);
            result = 0;
        }
    }
    else
    {
        //We've been successful, mark as the goal and return 1 up the chain.
        printf("------------------------Found Path-----------------------\n");
        result = 1;
        hexboard->hexcells[row][col].color = goal;
    }
    return result;
}