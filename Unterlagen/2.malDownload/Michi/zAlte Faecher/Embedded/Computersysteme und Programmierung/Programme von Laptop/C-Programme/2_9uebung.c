#include <stdio.h>


int main(void) {
	float netto, mwst;
	float brutto = { 500.00f };
	float mwst_satz = { 0.19f };


	netto = brutto / (1 + mwst_satz);
	mwst = brutto - netto;


	printf("Nettogehalt        : %8.2f\n", netto);
	printf("Mehrwertsteuer     : %8.2f\n", mwst);
}

/*

In einem C - Programm ist zu einem Brutto - Betrag der zugehörige NettoBetrag 
und die enthaltene Mehrwertsteuer zu berechnen.
Definieren Sie die Variablen brutto, netto, mwst und mwst_satz, wobei Sie
die Variablen brutto und mwst_satz beispielsweise mit den Werten 500.00
und 0.19 initialisieren.Speichern Sie das Ergebnis in den Variablen netto
und mwst und zeigen Sie es am Bildschirm an.Es gilt die Formel :
*/