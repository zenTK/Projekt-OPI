#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cstring>
#include <cmath>

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
string c = "[C]";
string f = "[F]";
string k = "[K]";


void prelom() {
	cout << "----------------------------------------------------------------------------------- \n";
}

void enotaZelenaTemp() {
	if (zelenaTemp <= 30 && zelenaTemp >= 10) {
		cout << c;
	}
	else if (zelenaTemp > 30 && zelenaTemp <= 90) {
		cout << f;
	}
	else if (zelenaTemp >= 283 && zelenaTemp <= 303) {
		cout << k;
	}
}

void enotaTrenutnaTemp() {

	if ((zelenaTemp <= 30 && zelenaTemp >= 10) && (trenutnaTemp >= 10 && trenutnaTemp <= 30)) { // Celzij
	trenutnaTemp = trenutnaTemp;
	cout << trenutnaTemp << c;
	}
	else if ((zelenaTemp <= 30 && zelenaTemp >= 10) && !(trenutnaTemp >= 10 && trenutnaTemp <= 30) && (trenutnaTemp >= 283 && trenutnaTemp <= 303)) { // Kelvin v Celzij
		trenutnaTemp = trenutnaTemp - 273.13;
		cout << trenutnaTemp << c;
	}
	else if ((zelenaTemp <= 30 && zelenaTemp >= 10) && !(trenutnaTemp >= 10 && trenutnaTemp <= 30) && (trenutnaTemp > 30 && trenutnaTemp <= 90)) { // Fahrenheit v Celzij
		trenutnaTemp = (trenutnaTemp - 32) / 1.8;
		cout << trenutnaTemp << c;
	}
	else if ((zelenaTemp > 30 && zelenaTemp <= 90) && (trenutnaTemp > 30 && trenutnaTemp <= 90)) { // Fahrenheit
		trenutnaTemp = trenutnaTemp;
		cout << trenutnaTemp << f;
	}
	else if ((zelenaTemp > 30 && zelenaTemp <= 90) && !(trenutnaTemp > 30 && trenutnaTemp <= 90) && (trenutnaTemp >= 283 && trenutnaTemp <= 303)) { // Kelvin v Fahrenheit
		trenutnaTemp = trenutnaTemp * 1.8 - 459.67;
		cout << trenutnaTemp << f;
	}
	else if ((zelenaTemp > 30 && zelenaTemp <= 90) && !(trenutnaTemp > 30 && trenutnaTemp <= 90) && (trenutnaTemp >= 10 && trenutnaTemp <= 30)) { // Celzij v Fahrenheit
		trenutnaTemp = trenutnaTemp * 1.8 + 32;
		cout << trenutnaTemp << f;
	}
	else if ((zelenaTemp >= 283 && zelenaTemp <= 303) && (trenutnaTemp >= 283 && trenutnaTemp <= 303)) { // Kelvin
		trenutnaTemp = trenutnaTemp;
		cout << trenutnaTemp << k;
	}
	else if ((zelenaTemp >= 283 && zelenaTemp <= 303) && !(trenutnaTemp >= 283 && trenutnaTemp <= 303) && (trenutnaTemp >= 10 && trenutnaTemp <= 30)) { // Celzij v Kelvin
		trenutnaTemp = trenutnaTemp + 273.13;
		cout << trenutnaTemp << k;
	}
	else if ((zelenaTemp >= 283 && zelenaTemp <= 303) && !(trenutnaTemp >= 283 && trenutnaTemp <= 303) && (trenutnaTemp > 30 && trenutnaTemp <= 90)) { // Fahrenheit v Kelvin
		trenutnaTemp = (trenutnaTemp + 459.67) * 5 / 9;
		cout << trenutnaTemp << k;
	}
}

void vnesiZeleneLastnosti() {
	cout << "Vnesi zeleno: ";
	cout << "\nTemperaturo[C, K in F]: ";
	cin >> zelenaTemp;
	enotaZelenaTemp();
	cout << "\nVlaznost[%]: ";
	cin >> zelenaVlaz;
	cout << "[%]";
	cout << "\nOsvetljenost[lx]:";
	cin >> zelenaOsv;
	cout << "[lx]\n";

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
	}
	else if (zelenaTemp >= 283 && zelenaTemp <= 303) {
		zelenaKelvin = zelenaTemp;
	}
}


void vnesiTrenutneLastnosti() {
	cout << "Vnesi trenutne lastnosti\n";
	cout << "\tTemperatura[C, K in F]: "; // simbol za stopinje ne dela v cmd-ju
	cin >> trenutnaTemp;
	enotaTrenutnaTemp();
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
		cin >> trenutnaTemp;
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

		mojaDatOut << "\nVLAZNOST[%]: " << zelenaVlaz << "[%]\nOSVETLJENOST[lx]: " << zelenaOsv << "[lx]\n";
		mojaDatOut << "\nINTERVAL TEMPERATURE: [10,40] [C]\nSTOPNJA VLAZNOSTI: [30,60] [%]\nINTERVAL OSVETLJENOSTI: [10,1000] [lx]";
		mojaDatOut.close();
	}
	else {
		cout << "Napaka pri odpiranju";
	}

	ifstream mojaDatIn;
	mojaDatIn.open("Zeljene_ambientalne_lastnosti.txt");
	if (mojaDatIn.is_open()) {
		cout << "Ambientalne lastnosti bodo prilagojene na: \nTemperatura: " << zelenaTemp;
		enotaZelenaTemp();
		cout << "\nVlaznost: " << zelenaVlaz << "[%]";
		cout << "\nOsvetljenost: " << zelenaOsv << "[lx]\n";
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