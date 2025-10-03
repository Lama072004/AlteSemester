
// FormatierteAusgabe.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <iomanip>

void listeAusgeben(const char* n[], float m, float p[], double me[]);
void bestAufgeben(double b[], const char* n[]);
const int anzahl = 10;
using namespace std;

int main()
{
	float mwst = 16.0;
	float preise[] = { 0.3,0.15,5.0,7.6,8.89,15.0,17.0,4.0,23.45,12.0 };
	const char* artikel[] = { "Kabel","Knickschutz","Farbband",
	"Adapter","Disketten","Nullmodem","Maus","Tastatur", "Toner","Gehauese" };
	double bestMenge[10];
	for (int i = 0; i < 10; i++)
		bestMenge[i] = 0.0;


	while (true) {
		int menu;

		cout << "Menue:\n1: Daten anzeigen\n2: Bestellung eingeben\n0: Ende" << endl;
		cin >> menu;
		if (menu == 0)
			return 0;
		else if (menu == 1)
			listeAusgeben(artikel,mwst,preise,bestMenge );
		else if (menu == 2)
			bestAufgeben(bestMenge, artikel);
		else
			cout << "Bitte gueltigen Befehl eingeben!";




		//system("PAUSE");

	}
	return 0;

}

void bestAufgeben(double b[] , const char * n []) {
	for (int i = 0; i < anzahl; i++)
	{
		cout << "Wie viel wollen Sie von " << n[i] << " Bestellen?" << endl;
		cin >> b[i];
	}


}


void listeAusgeben(const char * n[], float m, float p[], double be[]) {

	
	cout.width(42);
	cout << "PREISLISTE\nARTIKEL\t\tNETTO\t\tBRUTTO\t\tBESTMENGE\t\tNETTOGESAMTKOSTEN" << endl;

	cout.precision(2);

	for (int i = 0; i < anzahl; i++)
	{
		cout.fill('.');
		cout.setf(ios::fixed);

		cout << setiosflags(ios::left)
			<< setiosflags(ios::internal)
			<< setw(11)
			<< n[i]
			<< resetiosflags(ios::left)
			<< setfill(' ')
			<< setw(10) << p[i]
			<< setw(17) << p[i] + m
			<< setw(20) << be[i]
			<< setw(28) << be [i] * p[i]
			<< endl << endl;

	}
}

// Programm ausführen: STRG+F5 oder Menüeintrag "Debuggen" > "Starten ohne Debuggen starten"
// Programm debuggen: F5 oder "Debuggen" > Menü "Debuggen starten"

// Tipps für den Einstieg: 
//   1. Verwenden Sie das Projektmappen-Explorer-Fenster zum Hinzufügen/Verwalten von Dateien.
//   2. Verwenden Sie das Team Explorer-Fenster zum Herstellen einer Verbindung mit der Quellcodeverwaltung.
//   3. Verwenden Sie das Ausgabefenster, um die Buildausgabe und andere Nachrichten anzuzeigen.
//   4. Verwenden Sie das Fenster "Fehlerliste", um Fehler anzuzeigen.
//   5. Wechseln Sie zu "Projekt" > "Neues Element hinzufügen", um neue Codedateien zu erstellen, bzw. zu "Projekt" > "Vorhandenes Element hinzufügen", um dem Projekt vorhandene Codedateien hinzuzufügen.
//   6. Um dieses Projekt später erneut zu öffnen, wechseln Sie zu "Datei" > "Öffnen" > "Projekt", und wählen Sie die SLN-Datei aus.
