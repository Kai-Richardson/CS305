#include "stdio.h"
#include "stdlib.h"

#include "printer.h"
#include "printJob.h"

int main(int argv, char *argc[])
{
    //print_job(argc[1]);

    int num_prints;

    //Setup array of printer structs
    printer *p_arr[MAX_PRINTERS];
    *p_arr = (printer *)malloc(sizeof(struct printer) * MAX_PRINTERS);

    FILE *fp = fopen(argc[1], "r");
    if (fp) //file failure check
    {
        //Reads/stores data from printer datafile
        fscanf(fp, "%d", num_prints);
        for (int i = 0; i < num_prints; i++) //process printers
        {
            fscanf(fp, "%2s %d", p_arr[i]->name, p_arr[i]->speed);
        }
        int curr_printer;
        char tmp_name[10];
        int tmp_num;
        while (scanf("%2s %d", tmp_name, tmp_num) = EOF)
        {
            if (curr_printer % num_prints != 0) //wraparound
            {
                curr_printer = 0;
            }
            else
            {
                add_job(*p_arr[curr_printer], tmp_name, tmp_num);
            }
        }

        return EXIT_SUCCESS;
    }
