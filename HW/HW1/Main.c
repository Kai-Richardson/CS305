#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int my_array[] = {1, 5, 10, 15};
	int* an_array[] = { &my_array[2], &my_array[0] };
	char name[] = "MartinC";

	int* p = my_array;
	char* pc = name;
	int** pp = &an_array[0];
	(*p)++;
	printf("Value of *p: %d\n", *p);

	p++;
	printf("Value of p: %p\n", p);
	p++;
	*p = 30;
	printf("Value of my_array[2]: %d\n", my_array[2]);

	  // draw picture for activity
	printf("DRAW FIRST DATA PICTURE\n\n");
	pp++;
	printf("Value of *pp: %p\n", *pp);
	printf("Value of **pp: %d\n", **pp);
	pp--;
	(*p)++;
	printf("Values in an_array: %p, %p\n", an_array[0], an_array[1]);
	printf("Dereferencing values in an_array: %d, %d\n", *an_array[0], *an_array[1]);

	// draw picture for activity
	printf("DRAW SECOND DATA PICTURE\n\n");
	printf("Value of *pc: %c\n", *pc);
	(*pc)++;
	printf("Value of *pc: %c\n", *pc);
	pc++;
	printf("Value of *pc: %c\n", *pc);
	printf("DRAW THIRD DATA PICTURE\n\n");
	return EXIT_SUCCESS;
}