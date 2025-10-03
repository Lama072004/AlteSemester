#include <stdio.h>

#define DEBUG

void readFile(FILE stream);


int main(void) {
	char filename[100];

	printf("Please enter filename:\n");
	scanf_s("%99s", &filename[0]);

	FILE* fopen(filename, r);
	



	return 0;
}

