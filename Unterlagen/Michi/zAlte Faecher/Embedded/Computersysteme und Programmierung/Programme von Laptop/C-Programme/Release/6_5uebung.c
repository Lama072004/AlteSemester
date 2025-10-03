#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main(void) {
	int fibonacciIterations = 30 - 1;
	int k = 0, i = 1, last = 0;
	printf("%d, \n", k);
	for (int j = 1; j <= fibonacciIterations; j++) {
		i += last;
		last = k;
		k = i;
		printf("%d, ", i);
	}
}

/*Schreiben Sie ein C-Programm, das die ersten 30 Fibonacci-Zahlen berechnet
und anzeigt. Die ersten beiden Fibonacci-Zahlen sind 0 und 1. Jede weitere
Fibonacci-Zahl ist die Summe der beiden Vorgänger. Das ergibt die
Zahlenfolge 0, 1, 1, 2, 3, 5, 8, 13, 21, ....*/