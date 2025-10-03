#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

int* findInt(int find, int* arrOfInt, int length) {
	for (int i = 0; i < length; i++, arrOfInt++) {
		if (*arrOfInt == find) return arrOfInt;
	}
	return NULL;
}

void fehlerEnde(const char* errorMsg) {
	printf("Fehler bei %s. Programm wird beendet.", errorMsg);
	exit(EXIT_FAILURE);
}

static int werte[] = { 1,2,2,3,4,5,5,6,7,8,8,8,9,5,3,5,2,5,6,7,4,3,2,5,6,6,7,3,2,1,1,2,3,4 };

int main(void) {
	int wert, *gefundenAn = NULL;

	while (1) {
		printf("Es gibt %d Werte\nWerte sind:\n", _countof(werte));
		for (int i = 0; i < _countof(werte); i++) printf("%d ", werte[i]);

		printf("\nGesuchter Wert: ");
		rewind(stdin);
		if (scanf_s("%d", &wert) != 1 || wert < 0) fehlerEnde("der Eingabe");

		{
			int j = 0; //Zählvariable Werte gefunden, wird nach for Schleife benötigtS
			for (int i = 0; i < _countof(werte); i++) {
				gefundenAn = findInt(wert, werte + i, _countof(werte) - i);
				if (gefundenAn != NULL) {
					printf("Wert: %d gefunden an Position: %d\n", wert, gefundenAn - werte);
					i = gefundenAn - werte;
					j++;
				}
				else if(j == 0){
					printf("\nWert %d nicht gefunden!\n", wert);
					break;
				}

			}
			if (j != 0) printf("Es wurden %d Werte gefunden\n", j);
		}

	}


}


/*Definieren Sie die Funktion find_int(), die in einem beliebigen Vektor mit
int-Elementen einen bestimmten Wert sucht. Sie liefert einen Zeiger auf das
erste gefundene Element oder den Null-Zeiger, falls der Wert nicht vorhanden
ist. Als Argumente erhält die Funktion den gesuchten Wert, den Vektor
und seine Länge.
Testen Sie die Funktion, indem Sie zunächst die Elemente eines int-Vektors
anzeigen, in dem Werte auch mehrfach vorkommen. Anschließend wird in
einer Schleife vom Anwender jeweils eine ganze Zahl eingelesen und durch
wiederholten Aufruf von find_int() alle Positionen der Zahl im Vektor
angezeigt. Das Programm soll durch eine ungültige Eingabe, z.B. einen
Buchstaben, beendet werden*/