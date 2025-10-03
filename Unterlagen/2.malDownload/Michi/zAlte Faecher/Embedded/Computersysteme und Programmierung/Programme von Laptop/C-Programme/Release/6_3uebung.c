#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0



int main(void) {

	
	int n = 10, k = 3;
	long binomi = 1;

	int i = 1, j = n;
	do {
		binomi = binomi * j / i;
		j--;
		i++;
	} while (i <= k);


	/*
	for (int i = 1; i <= k; j--, i++) {
		binomi = binomi * j / i;
	}
	*/


	printf("Binomi: %d", binomi);
	return EXIT_SUCCESS;
}


/*

Schreiben Sie folgende while-Schleife als for-Schleife und als do-while-
Schleife.

int n = 10, k = 3;
long binomi = 1;
int i = 1, j = n;
while( i <= k)
binomi = binomi * j--/i++;
*/