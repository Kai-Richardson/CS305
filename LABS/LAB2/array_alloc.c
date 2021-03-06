#include <stdio.h>
#include <stdlib.h>

/* CS 305, lab 2 */

/* get_array -- allocates and initializes an array */
double *get_array(int size) {
	//check to see if it's negative, then make it zero
	if (size < 0) {
		size = 0;
	}

	double *a_ptr = malloc(size * __SIZEOF_DOUBLE__);

	for (int i = 0; i < size; i++)
	{

		*a_ptr = i * 10;
		a_ptr++; //increment ptr across array
	}
	a_ptr -= size; //bring back to beginning

	return a_ptr;
}

/* print_array -- prints the elements of the array, unless null */
void print_array(double arr[], int length) {
	/* test for null; if not print array elements */
	if (arr == NULL) {
		printf("(null array)\n");
	}
	else {
		/* print the elements */
		int i;
		for (i = 0; i < length; i++) {
			printf("%d: %1.20lg\n", i, arr[i]);
		}
	}
}

/* main program -- call getArray and print its results */
int main() {
	/* variable to hold the array */
	double *the_array = NULL;

	/* prompt user for the size */
	int size = -1;
	while(size < 0) {
		printf("Please type a non-negative integer: ");

		if(scanf("%d", &size) != 1) {
			printf("Data not scanned well. Exiting.\n");
			return EXIT_FAILURE;
		}
	}

	/* call get_array to create an populate array; then print it */
	the_array = get_array(size);
	if(the_array != NULL) {
		print_array(the_array, size);
	}

	/* free memory */
	free(the_array);

	return EXIT_SUCCESS;
}
