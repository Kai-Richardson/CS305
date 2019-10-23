#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "printer.h"
#include "printJob.h"

int main(int argc, char *argv[])
{
    int num_prints = -1; //starts at -1 so we don't have to deal with i-1

    //Setup array of printer structs
    printer *p_arr[MAX_PRINTERS];
    *p_arr = (printer *)malloc(sizeof(struct printer) * MAX_PRINTERS);

    //Only setup if we have a second arg, else just listen.
    if (argc > 1)
    {
        FILE *fp = fopen(argv[1], "r");
        if (fp) //file failure check
        {
            //Reads/stores data from printer datafile
            fscanf(fp, "%d", &num_prints);
            for (int i = 0; i < num_prints; i++) //process printers
            {
                fscanf(fp, "%10s %d", p_arr[i]->name, p_arr[i]->speed);
            }
            int curr_printer;
            char tmp_name[10];
            int tmp_num;
            while (fscanf("%10s %d", tmp_name, tmp_num) != EOF)
            {
                if (curr_printer % num_prints != 0) //wraparound
                {
                    curr_printer = 0;
                }
                else
                {
                    add_job(p_arr[curr_printer], tmp_name, tmp_num);
                }
            }

            return EXIT_SUCCESS;
        }
    }
}