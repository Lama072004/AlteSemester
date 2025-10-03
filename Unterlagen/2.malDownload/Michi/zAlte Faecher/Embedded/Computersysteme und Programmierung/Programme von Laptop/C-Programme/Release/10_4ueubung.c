#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

double a_mean(double, double);
double g_mean(double, double);
double h_mean(double, double);

int main(void) {
	printf("Geben Sie 2 Zahlen ein: \n");
	
	double x, y;
	rewind(stdin);
	if (scanf("%lf %lf", &x, &y) != 2) return 1;

	printf("Arithmethisches Mittel: %lf\n", a_mean(x, y));
	printf("Geometrisches Mittel: %lf\n", g_mean(x, y));
	printf("Harmonisches Mittel: %lf\n", h_mean(x, y));

	return 0;
}