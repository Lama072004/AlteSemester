#include <stdbool.h>

double median3(double, double, double);
void logStatus(void);
double geradenSteigung(double x1, double y1, double x2, double y2);
int ggt(int, int);
double geomReihe(double q, int n);
bool InitApplication();

/*
3.1 Wie lauten die Prototypen folgender Funktionen ?
a) Die Funktion median3() liefert den mittleren Wert von drei double - Werten, 
die als Argumente übergeben werden.
b) Die Funktion logStatus() schreibt die aktuelle Zeit und den Status des
Programms in eine Protokolldatei.Die Funktion hat keinen Parameter
und keinen Return - Wert.
c) Die Funktion geradensteigung() liefert die Steigung einer Geraden
durch zwei Punkte in der Ebene.Die Koordinaten der zwei Punkte x1, y1,
x2, y2 werden der Funktion als double - Werte übergeben.
d) Die Funktion ggt() bestimmt den größten gemeinsamen Teiler von zwei
ganzen Zahlen, die als Argumente übergeben werden.

e) Die Funktion geomReihe() liefert das n - te Element sn einer normierten
geometrischen Reihe, also den Wert q0 + q1 + ... + qn.Als Argument
erhält die Funktion die Gleitpunktzahl q und die ganze Zahl n.
f) Die Funktion InitApplication() initialisiert die Anwendung.Sie erhält
kein Argument und liefert true zurück, falls die Initialisierung erfolgreich
war, andernfalls false.Die Konstanten true und false sind vom Typ
bool, der zusammen mit den Konstanten in der Standard - Header - Datei
stdbool.h definiert ist

*/