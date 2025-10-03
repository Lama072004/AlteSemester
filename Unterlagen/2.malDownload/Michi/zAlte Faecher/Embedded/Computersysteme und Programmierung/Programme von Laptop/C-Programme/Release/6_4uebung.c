#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void) {

	printf("Geben Sie die Zeichen in einer Zeile ein:\n");

	for (int i = 1; ; i++) {
		char ch = getchar();
		if (ch == '\n')break;
		if (i == 1) {
			printf("%15s%15s%15s%15s\n", "Zeichen", "Dezimal", "hexdez", "oktal");
			printf(	"--------------------------------------------------------\n");
		}
		printf("%2d.%13c%15d%#15x%#15o\n", i, ch, ch, ch, ch);
	}
	return 0;


}


/*
Schreiben Sie ein C-Programm, das eine Zeile Text zeichenweise einliest und
die Zeichencodes der einzelnen Zeichen dezimal, hexadezimal und oktal
anzeigt.
Ein Beispielablauf:

Geben Sie die Zeichen in einer Zeile ein:
ok!
Zeichen dezimal hexadezimal oktal
----------------------------------------
1. o 111 6F 157
2. k 107 6B 153
3. ! 33 21 41

Hinweis: Verwenden Sie eine Variable vom Typ unsigned char, wenn Sie
mit scanf() ein einzelnes Zeichen einlesen. Dann werden auch Zeichencodes
größer als 127 nicht als negative Zahlen interpretiert.
*/