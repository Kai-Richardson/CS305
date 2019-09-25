#include "load.h"
#include "hexmaze.h"
#include "hexcell.h"

board* file_load(char *filename)
{
    board* result;
    void** v5;
    int v6;
    long v7;          // [rsp+0h] [rbp-40h]
    int i_num;          // [rsp+14h] [rbp-2Ch]
    board* gameboard; // [rsp+20h] [rbp-20h]
    FILE* fp;         // [rsp+28h] [rbp-18h]

    gameboard = (board*)malloc(sizeof(struct board));
    if (gameboard)
    {
        fp = fopen(filename, "r");
        if (fp)
        {
            fscanf(fp,"%d %d %d %d %d %d",\
                gameboard,\
                &gameboard->max_col,\
                &gameboard->start_row,\
                &gameboard->start_col,\
                &gameboard->end_row,\
                &gameboard->end_col);
            if (gameboard->max_row > 0 && gameboard->max_col > 0)
            {
                if (gameboard->max_row > gameboard->start_row && gameboard->max_row > gameboard->end_row && gameboard->max_col > gameboard->start_col && gameboard->max_col > gameboard->end_col && gameboard->start_col >= 0 && gameboard->end_col >= 0 && gameboard->start_row >= 0 && gameboard->end_row >= 0)
                {
                    gameboard->hexcells = (hexcell**)malloc(sizeof(struct hexcell) * gameboard->max_row);
                    for (int i = 0; gameboard->max_row > i; ++i)
                    {
                        v5 = (void **)&gameboard->hexcells[i];
                        *v5 = malloc(8LL * gameboard->max_col);
                        if (!gameboard->hexcells[i])
                        {
                            fwrite("Could not allocate hexcells", 1uLL, 0x1BuLL, stderr);
                            free(gameboard);
                            return 0LL;
                        }
                    }
                    i_num = 0;
                LABEL_36:
                    int j;
                    if (gameboard->max_row > i_num)
                    {
                        for (j = 0;; j++)
                        {
                            if (gameboard->max_col <= j)
                            {
                                ++i_num;
                                goto LABEL_36;
                            }
                            fscanf(fp, "%d ", &gameboard->hexcells[i_num][j].obstacle, filename);
                            v6 = gameboard->hexcells[i_num][j].obstacle == no || gameboard->hexcells[i_num][j].obstacle == yes;
                            if (!v6)
                                break;
                            gameboard->hexcells[i_num][j].color = 1;
                        }
                        printf("Invalid hexcell value at %d:%d value %d\n", i_num, j, gameboard->hexcells[i_num][j].obstacle);
                        for (int i = 0; gameboard->max_row > i; ++i)
                            free(gameboard->hexcells[i]);
                        free(gameboard->hexcells[i_num]);
                        free(gameboard);
                        fclose(fp);
                        result = 0;
                    }
                    else
                    {
                        fclose(fp);
                        result = gameboard;
                    }
                }
                else
                {
                    printf(
                        "Incorrect start or end points entered\nmx:%d my:%d\nsx:%d sy:%d\nex:%d ey:%d\n",
                        gameboard->max_row,
                        gameboard->max_col,
                        gameboard->start_col,
                        gameboard->start_row,
                        gameboard->end_col,
                        gameboard->end_row);
                    free(gameboard);
                    result = 0;
                }
            }
            else
            {
                puts("Board dimension(s) must be 0");
                free(gameboard);
                result = 0;
            }
        }
        else
        {
            fprintf(stderr, "Could not open file for reading");
            result = 0;
        }
    }
    else
    {
        fprintf(stderr, "Could not allocate board in memory");
        result = 0;
    }
    return result;
}