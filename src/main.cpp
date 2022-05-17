#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "world.h"

using namespace std;

// Kyrios programma
int main(int argc, char ** argv)
{
	World w;
	bool done = false;

	srand( time(NULL) );
	w.initialize();
	while (!done)
	{
		// Epiloges toy xrhsth
		cout << "*(*(*( Epiloges prosomoiwshs )*)*)*" << endl;
		cout << "<Enter> Epomenos gyros" << endl;
		cout << "1. Plhrofories oxhmatos" << endl;
		cout << "2. Plhrofories edafoys" << endl;
		cout << "3. Statistika toy kosmoy" << endl;
		cout << "4. Eisagogh neoy oxhmatos" << endl;
		cout << "5. Epeksergasia theshs edafoys" << endl;
		cout << "6. Proklhsh blabhs se oxhma" << endl;
		cout << "7. Epidiorthosh oxhmatos me blabh" << endl;
		cout << "Q. Termatismos" << endl;
		cout << endl << "--> ";
		// Anagnosh epiloghs
		string line;
		getline(cin, line);
		// Ektelesh diaforwn leitoyrgiwn ston kosmo analoga me thn epilogh
		if (line == "")
			w.next_round();
		else if (line == "1")
			w.stoixeia_oxhmatos();
		else if (line == "2")
			w.stoixeia_edafoys();
		else if (line == "3")
			w.statistika();
		else if (line == "4")
			w.neo_oxhma();
		else if (line == "5")
			w.allagh_theshs();
		else if (line == "6")
			w.proklhsh_blabhs();
		else if (line == "7")
			w.diorthosh_blabhs();
		else if (line == "Q" || line == "q")
			done = true;
		else cout << "Agnwsth epilogh!" << endl;
		// Elegxos an o kosmos exei dialythei
		if (w.status() == World::FAILURE) {
			cout << "Ola ta oxhmata xalasan!" << endl;
			done = true;
		}
		// Elegxos an kataferame na gemisoyme th bash
		if (w.status() == World::SUCCESS) {
			cout << "H bash gemise me fortio!" << endl;
			done = true;
		}
	}
}
