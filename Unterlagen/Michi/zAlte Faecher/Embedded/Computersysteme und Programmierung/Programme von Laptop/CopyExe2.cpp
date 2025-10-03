// CopyExe.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <fstream>
#include<iomanip>

using namespace std;

int main()
{
    int i = 1;
    char zeile[250], datei[59];
    cout << "Dateiname: " << flush;
    cin.get(datei, 50);
    ifstream eingabe(datei, ios::in | ios::binary);
    if (eingabe.good()) {
        eingabe.seekg(0L, ios::end);
        cout << "Datei: " << datei << "\t"
            << eingabe.tellg() << " Bytes" << endl;
        for (int j = 0; j < 80; j++)
            cout << "_";
        cout << endl;
        eingabe.seekg(0L, ios::beg);
        while (!eingabe.eof()) {
            eingabe.getline(zeile, 250);
            cout << setw(2) << i++
                << ": " << zeile << endl;


        }

    }
    else
        cout << "Dateifehler oder Datei nicht gefunden!" << endl;


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
