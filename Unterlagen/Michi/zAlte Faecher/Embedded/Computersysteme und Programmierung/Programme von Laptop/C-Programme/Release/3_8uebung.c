#include <stdio.h>

void createLine(int);
void printExpAndLog(double);

int main(void) {
	printf("\tx\tlog(x)\t\texp(x)\n\n");
	createLine(50);
	double fa = 1.f;
	printExpAndLog(fa);
	fa = 10.f;
	printExpAndLog(fa);
	fa = 100.f;
	printExpAndLog(fa);
}

void printExpAndLog(double a) {
	printf("%10.6lf\t%lf\t%E\n", a, log(a), exp(a));
};

void createLine(int i) {
	for (; i > 0; i--) {
		printf("-");
	}
	printf("\n");
}