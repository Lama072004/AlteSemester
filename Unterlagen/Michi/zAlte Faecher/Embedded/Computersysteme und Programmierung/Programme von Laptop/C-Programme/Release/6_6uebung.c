#include <stdio.h>
#include <stdbool.h>
#define _CRT_SECURE_NO_WARNINGS

int main(void) {
	

	double first = 0., second = 1., buffer = 0., quotient, convergedActual = 0., convergedLast = 0.;
	bool headline = false;
	int cnt = 0;
	while (fabs(convergedActual - convergedLast) < 1e-6 || cnt < 8) {
		if (!headline) {
			printf("%20s%20s\n"
				"---------------------------------------------\n", 
				"Fibonaccizahl", "Quotient");
			headline = true;
		}
		
		second += buffer;
		buffer = first;
		first = second;

		printf("%20.8lf%20.8lf%20.8lf\n", first, buffer, convergedActual);

		convergedLast = convergedActual;
		if (buffer != 0)
			convergedActual = first / buffer;
		cnt++;
	}


}


/*Die Fibonacci-Zahlen (siehe Aufgabe 6.5) haben einige interessante Eigenschaften.
Dividiert man jede Fibonacci-Zahl durch ihren Vorgänger, so erhält
man die Folge der Fibonacci-Quotienten 1/1, 2/1, 3/2, 5/3, 8/5, ... .
Diese Zahlenfolge konvergiert gegen den Grenzwert (1+ )/2 = 1,618...
Schreiben Sie ein C-Programm, das diesen Grenzwert näherungsweise
bestimmt: Das Programm gibt die Fibonacci-Zahlen und ihre Quotienten aus
bis einschließlich der ersten Fibonacci-Zahl, deren Quotient sich vom Quotienten
des Vorgängers weniger als 0,00001 = E-6 unterscheidet.
Hinweis: Zur Berechnung der Quotienten ist es sinnvoll, die Fibonacci-Zahlen
in Variablen vom Typ double zu speichern. Der Absolutwert der Differenz
kann mit der Standardfunktion fabs() bestimmt werden.
Beispielausgabe*/