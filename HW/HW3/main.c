#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "printer.h"
#include "printJob.h"

int main(int argc, char *argv[])
{
	int num_prints = -1; //starts at -1 so we don't have to deal with i-1
	int exited = false;  //used to keep track if user has prompted exit
	int time = 1;		 //system controller clock

	//Setup array of printer structs
	printer *p_arr;
	p_arr = malloc(sizeof(printer) * MAX_PRINTERS);

	//Initalize values from garbage
	for (int i = 0; i < MAX_PRINTERS; i++)
	{
		p_arr[i].online = 1;
		p_arr[i].speed = 0;
		p_arr[i].printQueue = NULL;
	}

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
			char *tmp_jname = malloc(sizeof(char) * MAX_NAME_LEN);
			int tmp_jnum = 0;

			while (fscanf(fp, "%10s %d", tmp_jname, &tmp_jnum) != EOF)
			{
				printJob *newjob;

				curr_printer = curr_printer % num_prints; //wraparound

				newjob = create_job_for_printer(p_arr[curr_printer], tmp_jname, tmp_jnum);

				add_job(p_arr, newjob, curr_printer);

				curr_printer++;
			}
			free(tmp_jname); //no longer needed
			fclose(fp);		 //close since we're done
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
			char in0[MAX_ALLOWED_INPUT];
			char in1[MAX_ALLOWED_INPUT];
			char in2[MAX_ALLOWED_INPUT];
			char in3[MAX_ALLOWED_INPUT];

			sscanf(input, " %s %s %s %s", in0, in1, in2, in3);

			switch (in0[0]) //1st char is command operation (allows for "quit", "time", etc.)
			{
			case 'q': //q --quit program
				printf("\033[0;31mQuitting...\033[0m\n");
				exited = true;
				break;
			case 't': //t --increment clocktime
				time++;
				break;
			case 'o': //o <printer name> --set <printer name > online
				for (int i = 0; i < MAX_PRINTERS; i++)
				{
					if (strncmp(p_arr[i].name, in1, sizeof(p_arr[i].name) / sizeof(char)))
					{
						online(p_arr[i]);
					}
				}
				break;
			case 'f': //f <printer name>  --set <printer name > offline and distributes jobs
				for (int i = 0; i < MAX_PRINTERS; i++)
				{
					if (p_arr[i].name == NULL)
						break;
					if (strncmp(p_arr[i].name, in1, sizeof(p_arr[i].name) / sizeof(char)) == 0)
					{
						offline(p_arr, i, num_prints);
						break;
					}
				}
				break;
			case 'a': //a <printer name> <job name> <job duration> --add a print job with its size to the printer's queue

				for (int i = 0; i < MAX_PRINTERS; i++)
				{
					if (strncmp(p_arr[i].name, in1, sizeof(p_arr[i].name) / sizeof(char)))
					{
						create_job_for_printer(p_arr[i], in2, atoi(in3));
					}
				}
				time++;
				break;
			case 'p': //p --explicit print callto print all printers and their queues.
				printf("\n");
				for (int i = 0; i < MAX_PRINTERS; i++)
				{
					if (p_arr[i].name != NULL)
					{
						print(p_arr[i]);
					}
				}
				printf("\n");
				//time++; -not sure tick should be advanced, otherwise will print again
				break;

			default:
				printf("\033[0;31mInvalid input.\033[0m\n");
				break;
			}
		}
		if (time_old < time) //tick advanced
		{
			update_printer(p_arr, num_prints); //processes non-empty printer queues
		}
	}

	//Free used memory
	for (int i = 0; i < MAX_PRINTERS; i++)
	{
		//job queue handling
		if (p_arr[i].printQueue != NULL)
		{

			printJob *job;
			printJob *other;

			job = p_arr[i].printQueue;
			while (job != NULL)
			{
				other = job;
				if (job->next != NULL)
				{
					job = job->next;
				}

				free(other->name);
				free(other);
			}
		}

		//free printer names
		free(p_arr[i].name);
	}

	//free printer array
	free(p_arr);

	return EXIT_SUCCESS;
}