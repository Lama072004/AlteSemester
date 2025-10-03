#include <stdio.h>

int main(void) {
	double eingabe;

	printf("Geben Sie eine Gleitpunktzahl ein:\n");
	scanf_s("%lf", &eingabe);

	printf("%.2lf\n%.2e", eingabe, eingabe);

	return 0;
}



/*Schreiben Sie ein C - Programm, das vom Anwender eine Gleitpunktzahl einliest und die 
Zahl in Fixpunktdarstellung und in exponentieller Darstellung
mit zwei Ziffern hinter dem Dezimalpunkt ausgibt.
Beispielausgabe:
Verwenden Sie zum Einlesen statt scanf() die secure - Funktion scanf_s(),
sofern Ihr System diese unterstützt*/