#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include<string.h>

#define MAXSIZE 100

int main(void) {
	double* pDoub = malloc(MAXSIZE * sizeof(double));

	if (pDoub != NULL) {
		for (int i = 0; i < MAXSIZE; i++) {
			pDoub[i] = 0.1 * i;
		}
		for (int i = 0; i < MAXSIZE; i++) {
			printf("%2.2lf ", pDoub[i]);
		}
	}

	printf("\n\n");

	double* pTemp = realloc(pDoub, MAXSIZE * 2 * sizeof(double));
	if (pTemp == NULL) return EXIT_FAILURE;
	pDoub = pTemp;
	pTemp = NULL;

	memcpy((void*)(pDoub + 100), (void*)pDoub, MAXSIZE * sizeof(double));

	for (int i = 0; i < MAXSIZE * 2; i++) {
		printf("%2.2lf ", *(pDoub+i));
	}
	free(pDoub);

}