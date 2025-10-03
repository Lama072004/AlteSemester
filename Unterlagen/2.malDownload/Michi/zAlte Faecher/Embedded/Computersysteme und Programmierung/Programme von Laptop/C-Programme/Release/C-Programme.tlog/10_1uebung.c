#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

double fahr2celsius(double);
double celsius2fahr(double);
void eingabeFehler();

int main(void) {
	
	printf("Was wollen Sie umrechnen?\n"
		"1: Grad Celsius zu Fahrenheit\n"
		"2: Fahrenheit zu Grad Celsius\n"
	);

	int auswahl;
	if (scanf("%d", &auswahl) != 1) {
		eingabeFehler();
	};
	if (auswahl != 1 && auswahl != 2) eingabeFehler();

	double wert;
	printf("Geben Sie den umzurechnenden Wert ein:\n");
	if (scanf("%lf", &wert) != 1) {
		eingabeFehler();
	};

	if (auswahl == 1) {
		printf("Wert in Fahrenheit: %.1lf", celsius2fahr(wert));
		return EXIT_SUCCESS;
	}
	else if (auswahl == 2) {
		printf("Wert in Grad Celsius: %.1lf", fahr2celsius(wert));
		return EXIT_SUCCESS;
	}

}

void eingabeFehler() {
	printf("Fehler bei der Eingabe!");
	exit(EXIT_FAILURE);
};


/*
* 
* Celsius = 5/9 * (Fahrenheit – 32)
Fahrenheit = 9/5 * Celsius + 32
a) Die Funktion fahr2celsius() liefert zu einer Temperatur in Grad Fahrenheit
den entsprechenden Wert in Grad Celsius.
b) Die Funktion celsius2fahr() liefert zu einer Temperatur in Grad Celsius
den entsprechenden Wert in Grad Fahrenheit.

Beide Funktionen erhalten als Argument einen double-Wert und liefern das
Ergebnis als double-Wert. Zwischen Grad Fahrenheit und Grad Celsius gelten
folgende Beziehungen:
Beispielsweise sind 20° Celsius 68° Fahrenheit. Testen Sie die Funktionen
mit einem Programm, das sich in einer separaten Quelldatei befindet. Das
Programm liest vom Anwender jeweils eine Temperatur in Grad Fahrenheit
und Grad Celsius ein und zeigt die umgerechneten Temperaturen mit einer
Stelle nach dem Dezimalpunkt an.
*/