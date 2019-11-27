#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cstring>

using namespace std;

int zelenaTemp; // �elena Temparatura
int zelenaVlaz; // �elena vlaznost
int zelenaOsv; // �elena osvetljenost
int trenutnaTemp;
int trenutnaVlaz;
int trenutnaOsv;
int izbiraNacina;
int zelenaCelzij;
int zelenaFahrenheit;
int zelenaKelvin;
int trenutnaCelzij;
int trenutnaFahrenheit;
int trenutnaKelvin;


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

	while ((zelenaTemp < 10) || ((zelenaTemp > 90) && (zelenaTemp < 283)) || (zelenaTemp > 303)) {
		cout << "Izberi temparaturo med 10 C in 30C, 31F in 90F ali 283 K in 303K\n";
		cout << "Temperatura: ";
		cin >> zelenaTemp;
	}

	if (zelenaTemp <= 30 && zelenaTemp >= 10) {
		zelenaCelzij = zelenaTemp;
	}
	else if (zelenaTemp > 30 && zelenaTemp <= 90) {
		zelenaFahrenheit = zelenaTemp;
		zelenaFahrenheit = zelenaFahrenheit * 1.8 + 32;
		cout << zelenaFahrenheit;
	}
	else if (zelenaTemp >= 283 && zelenaTemp <= 303) {
		zelenaKelvin = zelenaTemp;
	}
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

	while ((trenutnaTemp < 10) || ((trenutnaTemp > 90) && (trenutnaTemp < 283)) || (trenutnaTemp > 303)) {
		cout << "Izberi temparaturo med 10 C in 30C, 31F in 90F ali 283 K in 303K\n";
		cout << "Temperatura: ";
		cin >> zelenaTemp;
	}

	if (trenutnaTemp <= 30 && trenutnaTemp >= 10) {
		trenutnaCelzij = trenutnaTemp;
	}
	else if (trenutnaTemp > 30 && trenutnaTemp <= 90) {
		trenutnaFahrenheit = trenutnaTemp;
	}
	else if (trenutnaTemp >= 283 && trenutnaTemp <= 303) {
		trenutnaKelvin = trenutnaCelzij;
	}
}



void glavniMeni() {
	cout << "GLAVNI MENI" << endl;
	cout << "===========" << endl;
	cout << "1.) Rocni nacin\n" << "2.) Avtomatski nacin\n" << "3.) Avtomatski nacin 2\n" << "4.) Pomoc\n" << "0.) Izhod" << endl;
}

void datoteka() {
	ofstream mojaDatOut;
	mojaDatOut.open("Zeljene_ambientalne_lastnosti.txt");
	if (mojaDatOut.is_open()) {
		mojaDatOut << "TEMPERATURA[C, F ali K]: " << zelenaTemp;
		if (zelenaTemp <= 30 && zelenaTemp >= 10) {
			mojaDatOut << "[C]";
		}
		else if (zelenaTemp > 30 && zelenaTemp <= 90) {
			mojaDatOut << "[F]";
		}
		else if (zelenaTemp >= 283 && zelenaTemp <= 303) {
			mojaDatOut << "[K]";
		}

		mojaDatOut << "\nVLAZNOST[%]: " << zelenaVlaz << " %\nOSVETLJENOST[lx]: " << zelenaOsv << " lx\n";
		mojaDatOut << "\nINTERVAL TEMPERATURE: �C\nSTOPNJA VLAZNOSTI: %\nINTERVAL OSVETLJENOSTI: lx";
		mojaDatOut.close();
	}
	else {
		cout << "Napaka pri odpiranju";
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
	}
}

int main(int argc, char* argv[])
{
	cout << "Regulator, verzija 0.1\n";
	prelom();
	vnesiZeleneLastnosti();
	prelom();

	datoteka();

	/*ofstream mojaDatOut;
	mojaDatOut.open("Zeljene_ambientalne_lastnosti.txt");
	if (mojaDatOut.is_open()) {
		mojaDatOut << "TEMPERATURA: " << zelenaTemp << " �C, K, �F\nVLAZNOST: " << zelenaVlaz << " %\nOSVETLJENOST: " << zelenaOsv << " lx\n";
		mojaDatOut << "\nINTERVAL TEMPERATURE: �C\nSTOPNJA VLAZNOSTI: %\nINTERVAL OSVETLJENOSTI: lx";
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
	*/
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
		cout << "\t\nPOZDRAVLJEN/A V TESTNEM NACINU";


		return 0;
	}
	else {
		cout << "TBD...";
	}
}