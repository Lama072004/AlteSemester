#include <math.h>

double a_mean(double x, double y) {
	return (x + y) / 2;
}

double g_mean(double x, double y) {
	return sqrt(x * y);
}

double h_mean(double x, double y) {
	return (2 * x * y) / (x + y);
}

/*Definieren Sie die drei Funktionen a_mean(), g_mean() und h_mean(), die
das arithmetische, geometrische und harmonische Mittel zweier positiver
Zahlen x und y berechnen. Für diese gilt:
Arithmetisches Mittel:
Geometrisches Mittel:
Harmonisches Mittel:
Jede Funktion besitzt zwei Parameter und gibt den entsprechenden Mittelwert
zurück. Testen Sie die Funktionen mit zwei Zahlen, die der Anwender
eingibt. Das Programm besteht aus zwei Quelldateien, wobei eine die Funktionen
für die Mittelwerte enthält und die andere die Funktion main().*/