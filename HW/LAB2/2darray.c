#include <stdio.h>
#include <stdlib.h>
/* cs305 lab 2 */

/* free memory for 2D array */
void free2Darray(int **a, int height)
{
	int i = 0;
	for (i = 0; i < height; i++)
	{
		free(a[i]);
	}
	free(a);
}

/* make 2D array and initialize each location with its row number */
int **make2Darray(int width, int height)
{
	int **a = NULL;
	int i = 0;
	int j = 0;

	if (width < 0)
	{
		width = 0;
	}
	if (height < 0)
	{
		height = 0;
	}
	/* allocate memory to store pointers for each row */
	a = (int **)calloc(height, sizeof(int *));
	if (a != NULL)
	{
		/* allocate memory to store data for each row */
		for (i = 0; i < height; i++)
		{
			a[i] = (int *)calloc(width, sizeof(int));
			if (a[i] == NULL)
			{
				/*clean up */
				free2Darray(a, height);
				return NULL; /*aborting here*/
			}
		}
	}

	for (int n = 0; n < height; n++)
	{
		for (int m = 0; m < width; m++)
		{
			a[n][m] = n;
		}
	}

	return a;
}

/* print contents of 2D array */
void print2Darray(int **a, int width, int height)
{
	int i, j;
	if (a == NULL)
	{
		printf("null array\n");
		return;
	}
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			printf("%d\t", a[i][j]);
		}
		printf("\n");
	}
}

/* create a 2d array of ints and prints it to the screen */
int main()
{
	int width, height;
	int **array = NULL;

	printf("Enter the width:\n");
	if (scanf("%d", &width) != 1)
	{
		printf("Aborting.\n");
		return EXIT_FAILURE;
	}

	printf("Enter the height:\n");
	if (scanf("%d", &height) != 1)
	{
		printf("Aborting.\n");
		return EXIT_FAILURE;
	}

	printf("width: %d\n", width);
	printf("height: %d\n", height);

	array = make2Darray(width, height);
	if (array != NULL)
	{
		print2Darray(array, width, height);
		/* free memory */
		free2Darray(array, height);
	}
	array = NULL;
	return EXIT_SUCCESS;
}
