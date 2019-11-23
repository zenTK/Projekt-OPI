#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cstring>

using namespace std;

int zelenaTemp; // želena Temparatura
int zelenaVlaz; // želena vlaznost
int zelenaOsv; // želena osvetljenost
int trenutnaTemp;
int trenutnaVlaz;
int trenutnaOsv;
int izbiraNacina;

void prelom() {
	cout << "----------------------------------------------------------------------------------- \n";
}


void vnesiZeleneLastnosti() {
	cout << "Vnesi zeleno: ";
	cout << "\nTemperaturo: ";
	cin >> zelenaTemp;
	cout << "\nVlaznost: ";
	cin >> zelenaVlaz;
	cout << "\nOsvetljenost :";
	cin >> zelenaOsv;
}

void vnesiTrenutneLastnosti() {
	cout << "Vnesi trenutne lastnosti\n";
	cout << "\tTemperatura[C, K in F]: "; // simbol za stopinje ne dela v cmd-ju
	cin >> trenutnaTemp;
	cout << endl;
	cout << "\tVlaznost[%]: ";
	cin >> trenutnaVlaz;
	cout << endl;
	cout << "\tOsvetljenost[lx]: ";
	cin >> trenutnaOsv;
	cout << endl;
}

void glavniMeni() {
	cout << "GLAVNI MENI" << endl;
	cout << "===========" << endl;
	cout << "1.) Rocni nacin\n" << "2.) Avtomatski nacin\n" << "3.) Avtomatski nacin 2\n" << "4.) Pomoc\n" << "0.) Izhod" << endl;
}


int main(int argc, char* argv[])
{
	cout << "Regulator, verzija 0.1\n";
	prelom();
	vnesiZeleneLastnosti();
	prelom();

	ofstream mojaDatOut;
	mojaDatOut.open("Zeljene_ambientalne_lastnosti.txt");
	if (mojaDatOut.is_open()) {
		mojaDatOut << "TEMPERATURA: " << zelenaTemp << " °C, K, °F\nVLAZNOST: " << zelenaVlaz << " %\nOSVETLJENOST: " << zelenaOsv << " lx\n";
		mojaDatOut << "\nINTERVAL TEMPERATURE: °C\nSTOPNJA VLAZNOSTI: %\nINTERVAL OSVETLJENOSTI: lx";
		mojaDatOut.close();
	}
	else {
		cout << "Napaka pri odpiranju";
		return 0;
	}

	ifstream mojaDatIn;
	mojaDatIn.open("Zeljene_ambientalne_lastnosti.txt");
	if (mojaDatIn.is_open()) {
		cout << "Ambientalne lastnosti bodo prilagojene na: \nTemperatura: " << zelenaTemp << "\nVlaznost: " << zelenaVlaz << "\nOsvetljenost: " << zelenaOsv << "\n";
		mojaDatIn.close();
	}
	else
	{
		cout << "Napaka pri branju";
		return 0;
	}

	prelom();

	if (argc == 1) {
		glavniMeni();
		cin >> izbiraNacina;

		while (izbiraNacina != 0 && izbiraNacina != 1 && izbiraNacina != 2 && izbiraNacina != 3) {
			glavniMeni();
			cin >> izbiraNacina;
		}

		if (izbiraNacina == 1) {
			vnesiTrenutneLastnosti();
		}
		else if (izbiraNacina == 2) {
			cout << "2222";
		}
		else if (izbiraNacina == 3) {
			cout << "3333";
		}
		else if (izbiraNacina == 0) {
			return 0;
		}




		return 0;

	}
	else if ((argc == 2) && (strcmp(argv[1], "-t") == 0)) {


		return 0;
	}
	else {
		cout << "TBD...";
	}
}