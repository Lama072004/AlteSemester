#include <stdio.h>
#include <math.h>

double power(double x, int y) {
	//x die zu Potenzierende Zahl, y Potenz
	if (y == 0) return 1;
	return x * power(x, y - 1);
}

int main(void) {
	double zahl = 330.377;
	int potenz = 7;
	printf("eigene: %lf\nmath:   %lf", power(zahl, potenz), pow(zahl, potenz));
}



/*Schreiben Sie eine rekursive Funktion power(), die die Potenz xn für eine
Gleitpunktzahl x und eine nicht negative Ganzzahl n berechnet und zurückgibt.
Die Werte x und n werden als Argumente übergeben.
Es gilt: x0 = 1 und xn = x * xn-1 für n > 0.
Vergleichen Sie das Ergebnis, das Ihre Lösung liefert, mit dem Ergebnis der
Standardfunktion pow().*/