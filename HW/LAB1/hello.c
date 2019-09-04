#include <stdio.h>

/* main program prints Hello, world */
int main (int argc, char* argv[]) {

	if(argc != 2) {
		printf("I love C!\n");
	}
	else {
		printf("%s\n", argv[1]);
	}

	printf("Hello, world!\n");
	return 0;
}
