#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "ll.h"
#include "airport.h"

#define false 0
#define true 1
#define MAX_ALLOWED_INPUT 40
#define MAX_STRINGLEN 50

int main(int argc, char *argv[])
{
	int exited = false; //used to keep track if user has prompted exit

	list *llhead = NULL; //Our master llist head
	list *lltail = NULL; //Keep track of tail for fast addition

	printf("Starting Init\n");

	if (argc > 1)
	{
		FILE *fp = fopen(argv[1], "r");
		if (fp) //file failure check
		{
			//All overwritten every time, init here
			char *tmp_name = malloc(sizeof(char) * MAX_STRINGLEN);
			char *tmp_city = malloc(sizeof(char) * MAX_STRINGLEN);
			char *tmp_country = malloc(sizeof(char) * MAX_STRINGLEN);
			char *tmp_id1 = malloc(sizeof(char) * MAX_STRINGLEN);
			char *tmp_id2 = malloc(sizeof(char) * MAX_STRINGLEN);
			float tmp_lat = -9999;
			float tmp_lng = -9999;
			int tmp_alt = -9999;
			char *tmp_zone = malloc(sizeof(char) * MAX_STRINGLEN);
			char *tmp_dst = malloc(sizeof(char) * MAX_STRINGLEN);
			char *tmp_dst2 = malloc(sizeof(char) * MAX_STRINGLEN);
			char *tmp_type = malloc(sizeof(char) * MAX_STRINGLEN);
			char *tmp_source = malloc(sizeof(char) * MAX_STRINGLEN);

			while (fscanf(fp, "%s %s %s %s %s %f %f %d %s %s %s %s %s", tmp_name, tmp_city, tmp_country, tmp_id1, tmp_id2, &tmp_lat, &tmp_lng, &tmp_alt, tmp_zone, tmp_dst, tmp_dst2, tmp_type, tmp_source) != EOF)
			{
				airport *new_air = malloc(sizeof(airport));

				new_air->name = tmp_name;
				new_air->city = tmp_city;
				new_air->country = tmp_country;
				new_air->id1 = tmp_id1;
				new_air->id2 = tmp_id2;
				new_air->lat = tmp_lat;
				new_air->lng = tmp_lng;
				new_air->alt = tmp_alt;
				new_air->zone = tmp_zone;
				new_air->dst = tmp_dst;
				new_air->dst2 = tmp_dst2;
				new_air->type = tmp_type;
				new_air->source = tmp_source;

				if (llhead == NULL)
				{
					llhead = malloc(sizeof(list));
					llhead->value = new_air;

				}

			}

			//Free all temp. holders
			free(tmp_name);
			free(tmp_city);
			free(tmp_country);
			free(tmp_id1);
			free(tmp_id2);
			free(tmp_zone);
			free(tmp_dst);
			free(tmp_dst2);
			free(tmp_type);
			free(tmp_source);
		}
	}

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