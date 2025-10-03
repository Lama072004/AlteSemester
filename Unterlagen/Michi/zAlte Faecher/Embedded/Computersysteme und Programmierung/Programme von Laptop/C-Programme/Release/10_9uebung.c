#include <stdio.h>

#define ram 4097

double binmoinalkoeffizient(double n, double k) {
	//k Elemente aus n
	if (n < 0 || k < 0 || k > n) return -1;
	if (k == 0) return 1;
	double anzahl = (n - k + 1) / k;
	return anzahl * binmoinalkoeffizient(n, k-1);
}

int main(void) {
	double n = 49., k = 6.;
	printf("%.0lf aus %.0lf:\n%.0lf", k, n, binmoinalkoeffizient(n, k));
}



/*
Für zwei natürliche Zahlen n und k gibt der Binomialkoeffizient
(gesprochen: »n über k«) die Anzahl Möglichkeiten an, k Elemente aus n auszuwählen.
Beispielsweise gibt es »49 über 6« verschiedene Tipps beim Lotto
6 aus 49. Für die Binomialkoeffizienten gilt:
= 1 und =


Definieren und testen Sie die Funktion binomialkoeffizient() mit zwei
Parametern für n und k, die mit den angegebenen Formeln rekursiv den
Binomialkoeffizienten n über k berechnet. Sind n oder k negativ oder ist k
größer als n, soll die Funktion -1 zurückgeben.
Hinweise:
1. Die Binomialkoeffizienten sind zwar ganzzahlig, können aber sehr groß
werden. Daher soll die Funktion das Ergebnis als double-Wert zurückgeben.
2. Die Berechnung kann immer auf den Fall k <= n/2 zurückgeführt werden,
da gilt: = .
*/