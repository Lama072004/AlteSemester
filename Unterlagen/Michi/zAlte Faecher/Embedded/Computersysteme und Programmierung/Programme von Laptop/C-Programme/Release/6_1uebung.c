#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

int fakul(int);

int main(void) {
	printf("Insert number to calculate faculty: ");
	int input;
	if (scanf("%d", &input) != 1) {
		printf("Wrong input. Enter integer number!");
		return EXIT_FAILURE;
	}

	printf("Faculty is: %d",fakul(input));
	return EXIT_SUCCESS;

}


int fakul(int a) {
	if (a == 0) return 1;
	return a * fakul(a - 1);
};

/*
Schreiben Sie ein C-Programm, das vom Anwender eine positive ganze Zahl
einliest und die Fakult‰t dieser Zahl berechnet und ausgibt. Die Fakult‰t n!
einer Zahl n ist das Produkt der ersten n ganzen Zahlen, also
Zum Beispiel ist 4! gleich 24. Auﬂerdem ist 0! als 1 definiert.

n! = 1 * 2 * ... * (n-1) * n

Falls keine ganze Zahl eingegeben wird (z.B. ein Buchstabe) oder die Zahl
negativ ist, soll das Programm mit einer Fehlermeldung enden.
*/