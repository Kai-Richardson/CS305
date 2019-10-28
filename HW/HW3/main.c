#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "printer.h"
#include "printJob.h"

int main(int argc, char *argv[])
{
    int num_prints = -1; //starts at -1 so we don't have to deal with i-1
    int exited = false; //used to keep track if user has prompted exit
    int time = 1; //system controller clock

    //Setup array of printer structs
    printer *p_arr;
    p_arr = malloc(sizeof(printer) * MAX_PRINTERS);

    //Only read from file if we have a second arg, else just listen.
    if (argc > 1)
    {
        FILE *fp = fopen(argv[1], "r");
        if (fp) //file failure check
        {
            //Reads/stores data from printer datafile
            fscanf(fp, "%d", &num_prints);
            for (int i = 0; i < num_prints; i++) //process printers
            {
                char *temp_name = malloc(sizeof(char) * MAX_NAME_LEN);

                fscanf(fp, "%10s %d", temp_name, &p_arr[i].speed);
                p_arr[i].name = temp_name; //heap -> stack
            }

            //process jobs
            int curr_printer = 0;
            char *tmp_jname = malloc(sizeof(tmp_jname) * MAX_NAME_LEN);
            int tmp_jnum = 0;
            while (fscanf(fp, "%10s %d", tmp_jname, &tmp_jnum) != EOF)
            {
                if (curr_printer % num_prints != 0) //wraparound
                {
                    curr_printer = 0;
                }
                else
                {
                    add_job(p_arr[curr_printer], tmp_jname, tmp_jnum);
                }
            }
            fclose(fp); //close since we're done
        }
    }

    while (exited == false)
    {
        int time_old = time;

        char input[MAX_ALLOWED_INPUT];
        printf("\033[0m[\033[0;36m Time: \033[0m%d | \033[0;32mPrinters: \033[0m%d ]: \033[0;33m", time, num_prints);
        fgets(input, MAX_ALLOWED_INPUT, stdin);
        if (input != NULL)
        {
            switch (input[0]) //1st char is command operation
            {
            case 'q':
                printf("\033[0;31mQuitting...\033[0m\n");
                exited = true;
                break;
            case 't':
                time++;
                break;
            case 'o':
                //online();
                break;
                //o <printer name> --set <printer name > online
            case 'f':
                //offline();
                break;
                //f <printer name>  --set <printer name > offline and distributes jobs
            case 'a':
                //add_job(YEET, INPUT1st, INPUTCHAR);
                time++;
                break;
                //a <printer name> <job name> <job duration> --add a print job with its size to the printer’s queue
            case 'p':
                // print(all printers bby);
                time++;
                break;
                //explicit print callto print all printers and their queues. After every printer or queue update, the print function of all printers+queuesis executed by default.
            default:
                printf("\033[0;31mInvalid input.\033[0m\n");
                break;
            }
        }
        if (time_old < time) //tick advanced
        {
            update_printer();
            //processes non-empty printer queues
        }
    }

    //temp
    free(p_arr);

    return EXIT_SUCCESS;
}