#include "load.h"
#include "hexmaze.h"
#include "hexcell.h"

board *file_load(char *filename)
{
    board *result;

    //Allocate gameboard and check for failure.
    board *gameboard = (board *)malloc(sizeof(struct board));
    if (gameboard)
    {
        FILE *fp = fopen(filename, "r");
        if (fp) //file failure check
        {
            //Reads/stores data from hexboard header format.
            fscanf(fp, "%d %d %d %d %d %d",
                   &gameboard->max_row,
                   &gameboard->max_col,
                   &gameboard->start_row,
                   &gameboard->start_col,
                   &gameboard->end_row,
                   &gameboard->end_col);
            //Check board dimensions >= 1
            if (gameboard->max_row >= 1 && gameboard->max_col >= 1)
            {
                //Check start/end points
                if (gameboard->max_row > gameboard->start_row && gameboard->max_row > gameboard->end_row && gameboard->max_col > gameboard->start_col && gameboard->max_col > gameboard->end_col && gameboard->start_col >= 0 && gameboard->end_col >= 0 && gameboard->start_row >= 0 && gameboard->end_row >= 0)
                {
                    //Allocate the rows for the hexcell array.
                    gameboard->hexcells = (hexcell **)malloc(sizeof(struct hexcell) * gameboard->max_row);
                    for (int i = 0; gameboard->max_row > i; ++i)
                    {
                        //Use void pointers to allocate space for the hexcells.
                        void **ptr_void = (void **)&gameboard->hexcells[i];
                        *ptr_void = malloc(sizeof(struct hexcell) * gameboard->max_col);
                        if (!gameboard->hexcells[i])
                        {
                            fprintf(stderr, "Could not allocate hexcells.\n");
                            free(gameboard);
                            return NULL;
                        }
                    }
                    for (int curr_row = 0; curr_row < gameboard->max_row; curr_row++)
                    {
                        for (int curr_col = 0; curr_col < gameboard->max_col; curr_col++)
                        {
                            fscanf(fp, "%d ", &gameboard->hexcells[curr_row][curr_col].obstacle);
                            //Check for invalid obstacle values
                            if (!(gameboard->hexcells[curr_row][curr_col].obstacle == no || gameboard->hexcells[curr_row][curr_col].obstacle == yes))
                            {
                                printf("Invalid hexcell value at %d:%d value %d\n", curr_row, curr_col, gameboard->hexcells[curr_row][curr_col].obstacle);
                                for (int i = 0; gameboard->max_row > i; ++i)
                                    free(gameboard->hexcells[i]);
                                free(gameboard->hexcells[curr_row]);
                                free(gameboard);
                                fclose(fp);
                                result = NULL;
                            }
                            //Initalize each cell with being white.
                            gameboard->hexcells[curr_row][curr_col].color = white;
                        }
                    }
                    fclose(fp);
                    result = gameboard; //success!
                }
                else
                {
                    printf(
                        "Incorrect start or end points entered:\nmxro:%d mxco:%d strw:%d stcl:%d enrw:%d encl:%d\n",
                        gameboard->max_row,
                        gameboard->max_col,
                        gameboard->start_row,
                        gameboard->start_col,
                        gameboard->end_row,
                        gameboard->end_col);
                    free(gameboard);
                    result = NULL;
                }
            }
            else
            {
                puts("Board dimension(s) must be 1 or greater.\n");
                free(gameboard);
                result = NULL;
            }
        }
        else

        {
            fprintf(stderr, "Could not open file for reading.\n");
            result = NULL;
        }
    }
    else
    {
        fprintf(stderr, "Could not allocate board in memory.\n");
        result = NULL;
    }
    return result;
}