#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "ll.h"
#include "airport.h"

#define false 0
#define true 1
#define MAX_STRINGLEN 50

int main(int argc, char *argv[])
{
	int exited = false; //used to keep track if user has prompted exit

	LNode *llhead = NULL; //Our master llist head

	int num_ports = 0;

	printf("Starting Init\n");

	if (argc > 1)
	{
		FILE *fp = fopen(argv[1], "r");
		if (fp) //file failure check
		{
			char buffer[500];
			int ret;
			while (ret = fscanf(fp, "%s", buffer) != EOF)
			{
				airport *air = (airport *)malloc(sizeof(airport));
				ret = fscanf(fp, "%s", buffer);
				air->name = strdup(buffer);
				ret = fscanf(fp, "%s", buffer);
				air->city = strdup(buffer);
				ret = fscanf(fp, "%s", buffer);
				air->country = strdup(buffer);
				ret = fscanf(fp, "%s", buffer);
				air->id1 = strdup(buffer);
				ret = fscanf(fp, "%s", buffer);
				air->id2 = strdup(buffer);
				ret = fscanf(fp, "%s", buffer);
				air->lat = atof(buffer);
				ret = fscanf(fp, "%s", buffer);
				air->lng = atof(buffer);
				ret = fscanf(fp, "%s", buffer);
				air->alt = atoi(buffer);
				ret = fscanf(fp, "%s", buffer);
				air->zone = strdup(buffer);
				ret = fscanf(fp, "%s", buffer);
				air->dst = strdup(buffer);
				ret = fscanf(fp, "%s", buffer);
				air->dst2 = strdup(buffer);
				ret = fscanf(fp, "%s", buffer);
				air->type = strdup(buffer);
				ret = fscanf(fp, "%s", buffer);
				air->source = strdup(buffer);

				llhead = insertHead(air, llhead);
			}

			fclose(fp);
		}
	}

	while (exited == false)
	{
		char input[MAX_STRINGLEN];

		printf("Enter Command: ");

		fgets(input, MAX_STRINGLEN, stdin);

		//arrays to store input
		char in0[MAX_STRINGLEN];
		char in1[MAX_STRINGLEN];

		sscanf(input, " %s %s", in0, in1);

		switch (in0[0]) //1st char is command operation (allows for "quit", "time", etc.)
		{
		case 'q':
			//quit the airport tracker and deallocate ALL memory
			exited = true;
			break;

		case 'd':
			//deletes the airport by airport ID from the trees and LListand the struct itself and repairs the structures as needed
			break;

		case 's':
			switch (in0[1]) //switch on 2nd character
			{
			case 'n':
				//search for an ariport by airport ID in the id tree
				break;

			case 'c':
				//search for all ariports in a search city in the city tree
				break;

			case 'l':
				//search for an ariport by airport ID in the LList
				break;

			default:
				break;
			}

		default:
			printf("Invalid input.\n");
			break;
		}
	}

	freeList(llhead);

	return EXIT_SUCCESS;
}