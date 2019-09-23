#include "stdio.h"
#include "stdlib.h"

#include "load.h"
#include "hexcell.h"
#include "hexmaze.h"
/*
* Hexmaze path finder logic
* CS305 HW2 solution
* Author: Martin Cenek
* version: 1: 20190917
*/

int main(int argv, char* argc[]){

	if(argv != 2){
		fprintf(stderr, "Cound not open file");
		return EXIT_FAILURE;
	}
	find_path(argc[1]);

	return EXIT_SUCCESS;
}