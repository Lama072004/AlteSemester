#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>

double endKapital(double, double, int);

int main(void) {
	printf("Geben Sie die drei Werte ein, monatliche Rate, Zinssatz in Prozent, Laufzeit in Jahren\n");

	double rate, zinssatz;
	int laufzeit;
	rewind(stdin);
	if (scanf("%lf %lf %d", &rate, &zinssatz, &laufzeit) != 3) return 1;
	if (zinssatz == 0.) return 1;

	printf("Endkapital: %.2lf", endKapital(rate, zinssatz / 100, laufzeit));
}

double endKapital(double rate, double zinssatz, int laufzeit) {
	
	return rate * (12. + 6.5 * zinssatz) * ((pow((1. + zinssatz), (double)laufzeit) - 1.) / zinssatz);
};

//Dabei sind : rate = monatliche Rate, i = jährlicher Zinssatz(z.B. 3 % = 0, 03)
//und n = Laufzeit in Jahren.