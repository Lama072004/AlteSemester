// CPPBuchUebung1_9.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>

using namespace std;

int main()
{
    unsigned int unInt { 0 };
    unsigned long unLong{ 0 };
    unsigned long versuch{ 15 };
    int checkInt{ 0 };
    checkInt = ~checkInt;
    int kp{ checkInt >> 1 };

    cout << "Unsigned Integer: " << ~unInt << endl;
    cout << (versuch >> 2) << endl;
    cout << "Unsigend Long :   " << (~unLong<<4) << endl;
    cout << "Integer :         " << (checkInt >> 5) << endl;
    cout << kp << endl;
    return 0; 
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
