

#include <stdbool.h>

#include <stdio.h>
#include <stdlib.h> // Prototyp von srand(), rand()
#include <time.h> // Prototyp von time()
// Initialisierung des Zufallsgenerators:
#define InitRandom srand((unsigned int)time(NULL))
// Eine ganze Zufallszahl zwischen n und m:
#define Random(m,n) (rand()%((n)+1-(m)) + (m))


int* lotto();
void pushBack(int*, int, int);



//Lottozahlen 6 aus 45
int* lotto(){
	static bool initDone;
	if (!initDone) { InitRandom; initDone = true; };
	static int lottoZahlen[7];

	for (int i = 0; i < _countof(lottoZahlen); i++) lottoZahlen[i] = 0; //Array auf Null setzen/löschen muss bei jedem Aufruf passieren

	for (int j = 0; j < 6; j++) {
		int neueZahl = Random(1, 45);
		for (int i = 0; i < 6; i++) {
			if (lottoZahlen[i] > neueZahl || lottoZahlen[i] == 0) {
				if (lottoZahlen[i] > neueZahl) pushBack(lottoZahlen, i, 6);  //pushback wenn Neue Zahl größer als aktuelle, ansonsten setze sie bei i
				lottoZahlen[i] = neueZahl;
				break;
			}
		}
	}
	
	lottoZahlen[6] = Random(1, 45); //Zusatzzahl setzen, unabhängig von den anderen Zahlen

	return lottoZahlen;
}


//push Vector von Adresse "position" eins nach vor. Maximale Länge in "length"
void pushBack(int* v, int position, int length) {
	for (int i = length - 1; i > position; i--) {
		*(v + i) = *(v + i - 1);
	}
}

int main(void) {
	for (int i = 0; i < 5; i++) {
		int* zahlen = lotto();
		printf("\nLottozahlen: ");
		for (int j = 0; j < 7; j++)printf("%2d ", zahlen[j]);

	}
		

}


/*Erstellen Sie eine Funktion lotto() ohne Parameter, die mit jedem Aufruf 6
zufällige Lottozahlen (»6 aus 49«) und eine Zusatzzahl liefert (vgl. auch Aufgabe
9.7). Zur Erzeugung der Zufallszahlen können Sie die Makros Init-
Random und Random aus der Lösung zu Aufgabe 7.3 verwenden. Die Funktion
lotto() soll folgende Anforderungen erfüllen:
 Nur beim ersten Aufruf wird zu Beginn der Zufallsgenerator initialisiert.
 Die Funktion gibt einen Zeiger auf einen statischen Vektor mit 7 int-Elementen
zurück, der die 6 Lottozahlen und eine Zusatzzahl enthält.
 Die ersten 6 Lottozahlen sind aufsteigend sortiert. Eine neue Zufallszahl,
die nicht schon im Vektor vorhanden ist, soll direkt an der richtigen Stelle
im Vektor eingefügt werden.
Testen Sie die Funktion, indem Sie die Funktion dreimal aufrufen und
jeweils das Ergebnis der Lottoziehung anzeigen.*/