#include <stdio.h>
#include <math.h>


double annuitaet(double kreditsumme, double zinssatz, int laufzeit);

int main(void) {
	printf("%lf", annuitaet(1000.0f, 1.5f, 20));
}

double annuitaet(double kreditsumme, double zinssatz, int laufzeit) {
	double zaehler = pow((1.0f + zinssatz), (double)laufzeit) * zinssatz;
	double nenner = pow((1.0f + zinssatz), (double)laufzeit) - 1.0f;
	return (kreditsumme * zaehler) / nenner;
};

