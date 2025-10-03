#include <stdio.h>
#include <math.h>

void dritteUndFuenftePotenz(double f);

int main(void) {
	float zahl = { 4.0f };
	dritteUndFuenftePotenz(zahl);
}


void dritteUndFuenftePotenz(double f) {
	printf(
		"Zahl selbst       :%8.5f\n"
		"Dritte Potenz     :%8.5f\n"
		"Fuenft Potenz     :%8.5f\n",
		f, pow(f, 3.f), pow(f, 5.f));
}


/*Schreiben Sie ein C-Programm, das zunächst eine Variable für Gleitpunktzahlen mit 
einem Wert Ihrer Wahl initialisiert. Anschließend gibt das Programm die Zahl selbst 
sowie die dritte und fünfte Potenz der Zahl am
Bildschirm aus. Die Potenzen sollen mit der Standardfunktion pow() berechnet werden. */