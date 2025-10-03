#include <stdio.h>

void converge(int n, int* step, int* max);

int main() {
	//N größte Startzahl, stepMin Minimale Schrittanzahl, max größte erreichte Zahl
	int n = 0, stepMin = 0, max = 0;
	
	printf("Please enter highest start number:\n");
	scanf_s("%d", &n);

	printf("Please enter minimal step number:\n");
	scanf_s("%d", &stepMin);

	int i;
	for (i = 0; i < n + 1; i++) {
		converge(i, &stepMin, &max);
	};
	printf("Biggest number was: %d", max);

	return 0;
}



void converge(int n, int* step, int* max) {
	int stepCounter = 0;
	int k = n;

	while (k > 1) {
		if (k % 2 == 0) {
			k /= 2;
		}
		else {
			k = k * 3 + 1;
		}
		if (k > * max) {
			*max = k;
		}
		stepCounter++;
	};

	if (stepCounter >= *step)
		printf("Number: %d was reached!\n", n);
};