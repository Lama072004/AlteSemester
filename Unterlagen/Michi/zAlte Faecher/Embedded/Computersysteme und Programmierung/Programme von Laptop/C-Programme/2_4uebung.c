#include <stdio.h>


int main(void) {
	double zahl1 = { 1.0034f }, zahl2 = { 4.0022f };

	printf("Zahl 1 : %f\nZahl 2: %f\n", zahl1, zahl2);
	printf("Summe: %f\n", zahl1 + zahl2);
	printf("Differenz: %f\n", zahl1 - zahl2);
	printf("Produkt: %f\n", zahl1 * zahl2);
	printf("Quotient: %f\n", zahl1 / zahl2);
}

/*
Schreiben Sie ein C - Programm, das zwei Variablen für 
Gleitpunktzahlen initialisiert und ihre Werte am Bildschirm 
anzeigt.Anschließend berechnet das
Programm die Summe, die Differenz, das Produkt und den 
Quotienten beider Zahlen und zeigt die Ergebnisse an.

*/