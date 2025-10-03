#include <stdio.h>

#define DEBUG

void converge(int n, int* step, int* max);

void converge(int n, int* step, int* max) {
	int stepCounter = 0;
	int k = n;
#ifdef DEBUG
	//printf("n: %i\n", );
#endif // DEBUG

	while (k > 1) {
		if (k % 2 == 0) {
			k /= 2;
		}
		else {
			k = k * 3 + 1;
		}
		stepCounter++;
		if (k > * max)
			*max = k;
	};

	if (stepCounter > * step)
		printf("Number: %d was reached!\n", n);
};



int main() {
	//N größte Startzahl, stepMin Minimale Schrittanzahl, max größte erreichte Zahl
	int n = 16, stepMin = 0, max = 0;

	printf("Please enter highest start number:\n");
	scanf_s("%d", &n);

	printf("Please enter minimal step number:\n");
	scanf_s("%d", &stepMin);
	//scanf_s("%d", &stepMin);

#ifdef DEBUG
	printf("\nn: %d\nstepMin: %d\n", n, stepMin);
#endif // DEBUG

	int i;
	for (i = 0; i < n + 1; i++) {
		converge(i, &stepMin, &max);
	};

	printf("Biggest number was: %i", max);

	return 0;
}