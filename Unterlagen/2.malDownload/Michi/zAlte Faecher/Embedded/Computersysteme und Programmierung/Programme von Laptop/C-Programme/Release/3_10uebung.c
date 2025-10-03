#include <stdio.h>

static const double pi = 3.1415927;

int main(void) {

	double winkel, hoehe, schattenlaenge;

	printf("Bitte geben Sie die Schattenlaenge ein: ");
	scanf_s("%lf", &schattenlaenge);
	printf("\nBitte geben Sie den Winkel ein: ");
	scanf_s("%lf", &winkel);

	if (winkel >= 90.0f) {
		printf("Winkel zu gross! Programm beendet!");
		return 1;
	}
	hoehe = schattenlaenge * tan(winkel * pi/180);

	printf("Der Turm hat die hoehe: %.3lfm", hoehe);

	return 0;
}


/*Die Höhe eines Turmes, der auf einer waagerechten Ebene steht, kann aus
der Länge des Schattens und dem Winkel, den die Sonne zur Ebene bildet,
berechnet werden. Es gilt:
Turmhöhe = Schattenlänge * Tangens( Winkel)

Schreiben Sie ein C-Programm, das vom Anwender des Programms die
Länge des Schattens in Metern und den Winkel in Grad einliest und dann die
Höhe des Turms ausgibt.

Hinweise: scanf("%lf", &var);

1. In eine Variable var vom Typ double kann durch folgende Anweisung
eine Zahl von der Tastatur eingelesen werden:
2. Den Tangens eines Winkels berechnet die Standardfunktion tan(), die
den Winkel im Bogenmaß als Argument erhält. Um einen Winkel von
Grad ins Bogenmaß umzurechnen, wird er mit (pi/180) multipliziert,
wobei pi = 3.1415927.

*/