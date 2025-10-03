#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
	srand((unsigned int)time(NULL));
	{ 
		int i;
		for (i = 0; i < 3; i++) {
			int a = ((rand() % 90) + 10) + ((rand() % 90) + 10);
			printf("%d: Ergebnis: %d\n", i + 1, a);
			}
	}

}




/*Schreiben Sie ein C-Programm, das zunächst den Zufallsgenerator wie in der
vorhergehenden Aufgabe initialisiert und dann drei einfache Additionsaufgaben mit
Zufallszahlen zwischen 10 und 99 stellt.
Zusatzfrage: Erzeugt das Programm bei einem erneuten Aufruf dieselben
Additionsaufgaben?
Hinweis: Die Modulo-Division % liefert den Rest einer ganzzahligen Division. 
Zum Beispiel ergibt 18%5 den Wert 3. In welchem Bereich liegt dann
das Ergebnis des Ausdrucks z%90+10 für eine beliebige positive Ganzzahl z?*/