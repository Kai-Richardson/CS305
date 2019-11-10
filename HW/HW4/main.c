#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "tree.h"
#include "ll.h"
#include "airport.h"

int main(int argc, char *argv[])
{
	int exited = false; //used to keep track if user has prompted exit

	LNode *llhead = NULL;		//Our master llist head
	TreeNode *tree_id = NULL;   //BST by ID2
	TreeNode *tree_city = NULL; //BST by City

	if (argc > 1)
	{

		int shuffle = 0;

		//Prompt user if they want to shuffle the input file or not
		printf("Shuffle input (permanent!) (1/0): ");
		scanf("%d", &shuffle);
		printf("\n");

		if (shuffle)
		{
			char filebuf[100];
			snprintf(filebuf, 99, "shuf -o %s <%s", argv[1], argv[1]);
			system(filebuf);
		}

		printf("Starting loading of %s...\n", argv[1]);
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

				tree_city = insert(tree_city, llhead->value, CITY_SEARCH);
				tree_id = insert(tree_id, llhead->value, ID_SEARCH);
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
		TreeNode *tmp;

		sscanf(input, " %s %s", in0, in1);

		switch (tolower(in0[0])) //1st char is command operation (allows for "quit", "delete", etc.)
		{
		case 'q': //quits program
			exited = true;
			break;

		case 'd': //deletes the airport by airport ID from the trees and LList and the struct itself and repairs the structures as needed
			deleteByID(in1, &tree_id);

			//deleteNodeID(tree_city, in1, CITY_SEARCH);

			deleList(findNode(in1, llhead), &llhead);
			break;

		case 's':
			switch (tolower(in0[1])) //switch on 2nd character
			{
			case 'n': //search for an ariport by airport ID in the id tree
				tmp = findByID(tree_id, in1);
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

		default:
			printf("Invalid input.\n");
			break;
		}
	}

	//quit the airport tracker and deallocate ALL memory
	freeList(llhead);
	freeTree(tree_city);
	freeTree(tree_id);

	return EXIT_SUCCESS;
}