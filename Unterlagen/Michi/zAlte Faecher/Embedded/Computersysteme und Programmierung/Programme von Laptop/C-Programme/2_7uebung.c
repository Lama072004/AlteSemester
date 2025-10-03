#include <stdio.h>
#include <float.h>
/*
Die Header-Datei float.h definiert die Konstanten, die die Wertebereiche
und Genauigkeiten der Gleitpunkttypen beschreiben. Für den Typ float
sind das die Konstanten FLT_MAX, FLT_MIN und FLT_DIG. Sie stellen den
größten Wert, den kleinsten positiven Wert und die Genauigkeit dar. Die entsprechenden 
Konstanten für den Typ double sind DBL_MAX, DBL_MIN und
DBL_DIG. Schreiben Sie ein C-Programm, das den Wert dieser Konstanten
anzeigt.
Hinweis: Zeigen Sie den größten und kleinsten Wert in exponentieller
Schreibweise an. Verwenden Sie dazu das Formatelement %E. 
*/

int main(void) {

	printf("Float Max         :%E\n", FLT_MAX);
	printf("Float Min         :%E\n", FLT_MIN);
	printf("Float Genauigkeit :%E\n", FLT_DIG);
	printf("Double Max        :%E\n", DBL_MAX);
	printf("Double Min        :%E\n", DBL_MIN);
	printf("Double Genauigkeit:%E\n", DBL_DIG);

}