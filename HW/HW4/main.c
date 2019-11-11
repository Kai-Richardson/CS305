/* main.c for CS305 HW4
 * @author - Kai Richardson
 * @date 2019-11-10
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "tree.h"
#include "ll.h"
#include "airport.h"

int main(int argc, char *argv[])
{
	char input_buf[MAX_STRINGLEN]; //Our input buffer

	int exited = NOT_INIT; //used to keep track if user has prompted exit

	LNode *llhead = NULL;		//Our master llist head
	TreeNode *tree_id = NULL;   //BST by ID2
	TreeNode *tree_city = NULL; //BST by City

	if (argc > 1)
	{
		//Prompt user if they want to shuffle the input file or not (better for searching)
		printf("Shuffle input (permanent!) (Y/N): ");
		fgets(input_buf, 2, stdin);
		printf("\n");

		if (input_buf[0] == 'Y')
		{
			char filebuf[100];
			snprintf(filebuf, 99, "shuf -o %s <%s", argv[1], argv[1]);
			system(filebuf);
		}
		fflush(stdin);

		//Start loading of given file now that it may or may not be shuffled
		printf("Starting loading of %s...\n", argv[1]);
		FILE *fp = fopen(argv[1], "r");
		if (fp) //file failure check
		{
			char buffer[500]; //Buffer to temp. hold scanned input
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

				llhead = insertHead(air, llhead); //Insert created airport into LL

				tree_city = insert(tree_city, llhead->value, CITY_SEARCH); //Insert created airport into city tree
				tree_id = insert(tree_id, llhead->value, ID_SEARCH);	   //Insert created airport into ID tree
			}

			fclose(fp);
		}
	}

	while (exited == false || exited == NOT_INIT) //Loop to process usr input
	{

		if (exited == NOT_INIT) //To catch the case caused by the shuffle input prompt
		{
			exited = false;
		}
		else
		{
			printf("Enter Command: ");
		}

		fgets(input_buf, MAX_STRINGLEN, stdin);

		//arrays to store input
		char in0[MAX_STRINGLEN];
		char in1[MAX_STRINGLEN];

		//'empty' both char arrays, to eliminate garbage input
		in0[0] = '\0';
		in1[0] = '\0';

		TreeNode *tmp;												 //temporary holder of node ptr
		airport *tmp_port;											 //temporary holder of airport ptr
		rootParentHolder *holder = malloc(sizeof(rootParentHolder)); //Holder for deleting/searching ID trees, freed once done

		sscanf(input_buf, " %s %s", in0, in1);

		switch (tolower(in0[0])) //1st char is command operation (allows for "quit", "delete", etc.)
		{
		case 'q': //quits program
			printf("Quiting...\n");
			exited = true;
			break;

		case 'd': //deletes the airport by airport ID from the trees and LList and the struct itself
			tmp_port = deleteByID(in1, &tree_id, ID_SEARCH, NULL); //Del from IDtree and retains airport info for city del
			deleteByID(in1, &tree_city, CITY_SEARCH, tmp_port->city);
			deleList(findNode(in1, llhead), &llhead);
			break;

		case 's':
			switch (tolower(in0[1])) //switch on 2nd character
			{
			case 'n': //search for an ariport by airport ID in the id tree

				tmp = findByID(tree_id, in1, holder)->root; //can return NULL if not found, so check below
				if (tmp != NULL)
					printAirport(tmp->value);
				break;

			case 'c': //search for all ariports in a search city in the city tree
				printByCity(tree_city, in1);
				break;

			case 'l': //search for airport by ID and print info
				printAirport(findPort(in1, llhead));
				break;

			default:
				break;
			}
			break;

		case 'h': //help
			printf("q: quit, d <ID>: delete ID, sn <ID>: ID Tree Search, sc <City>: City Tree Search, sl <ID>: ID LL Search\n");
			break;

		case '\0': //empty input, caused by strange input
			break;

		default:
			printf("Invalid input.\n");
			break;
		}
		free(holder);
	}

	//quit the airport tracker and deallocate ALL memory
	freeList(llhead);
	freeTree(tree_city);
	freeTree(tree_id);

	return EXIT_SUCCESS;
}