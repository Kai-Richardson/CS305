#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "ll.h"
#include "airport.h"

#define false 0
#define true 1
#define MAX_ALLOWED_INPUT 40

int main(int argc, char *argv[])
{
	int exited = false; //used to keep track if user has prompted exit

	printf("Starting Init\n");

	while (exited == false)
	{
		char input[MAX_ALLOWED_INPUT];

		fgets(input, MAX_ALLOWED_INPUT, stdin);

		//arrays to store input
		char in0[MAX_ALLOWED_INPUT];
		char in1[MAX_ALLOWED_INPUT];

		sscanf(input, " %s %s", in0, in1);

		printf("Enter Command: ");

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

	return EXIT_SUCCESS;
}