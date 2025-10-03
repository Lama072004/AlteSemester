#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double getAngle(double*, int);

int main(void) {
	FILE* data = fopen("Input03.txt", "r");

	if (data == NULL) {
		printf("File could not be opened, check filename");
		return EXIT_FAILURE;
	}

	int fieldSize;
	if (fscanf(data, "%d", &fieldSize) != 1) {
		printf("Fieldsize could not be read, check file");
		return EXIT_FAILURE;
	}

	double* pDataHeight = (double*)malloc(sizeof(double) * fieldSize * fieldSize);
	if (pDataHeight == NULL) {
		printf("Memory allocation failed!");
		return EXIT_FAILURE;
	}

	for (int i = 0; i < fieldSize * fieldSize; i++) {
		if (fscanf(data, "%lf", pDataHeight + i) != 1) {
			printf("Error reading data, check file");
			return EXIT_FAILURE;
		}
	}

	//calculate and print
	printf("Biggest angle: %.2lf degrees", getAngle(pDataHeight, fieldSize));

	//close file, set pointer to null
	fclose(data);
	data = NULL;

	//free data pointer
	free(pDataHeight);
	return EXIT_SUCCESS;
}

