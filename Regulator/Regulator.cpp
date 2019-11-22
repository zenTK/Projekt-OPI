// Regulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cstring>

using namespace std;

int temperatura;
int vlaznost;
int osvetljenost;
int izbiraNacina;

void prelom() {
	cout << "----------------------------------------------------------------------------------- \n";
}


void vnesiVrednosti() {
	cout << "Vnesi zeljeno: ";
	cout << "\nTemperaturo: ";
	cin >> temperatura;
	cout << "\nVlaznost: ";
	cin >> vlaznost;
	cout << "\nOsvetljenost :";
	cin >> osvetljenost;
}


int main(int argc, char* argv[])
{
	vnesiVrednosti();
	prelom();

	ofstream mojaDatOut;
	mojaDatOut.open("Zeljene_ambientalne_lastnosti.txt");
	if (mojaDatOut.is_open()) {
		mojaDatOut << "TEMPERATURA: " << temperatura << " °C, K, °F\nVLAZNOST: " << vlaznost << " %\nOSVETLJENOST: " << osvetljenost << " lx\n";
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
		cout << "Ambientalne lastnosti bodo prilagojene na: \nTemperatura: " << temperatura << "\nVlaznost: " << vlaznost << "\nOsvetljenost: " << osvetljenost << "\n";
		mojaDatIn.close();
	}
	else
	{
		cout << "Napaka pri branju";
		return 0;
	}
	
	prelom();

	if (argc == 1) {
		cout << "Izberi nacin 1, 2 ali 3: \n";
		cout << "Izbira: ";
		cin >> izbiraNacina;

		while (izbiraNacina != 1 && izbiraNacina != 2 && izbiraNacina != 3) {
				cout << "Izberi nacin 1, 2 ali 3: \n";
				cout << "Izbira: ";
				cin >> izbiraNacina;
		}

		if (izbiraNacina == 1) {
			cout << "1111";
		}
		else if (izbiraNacina == 2) {
			cout << "2222";
		}
		else if (izbiraNacina == 3) {
			cout << "3333";
		}




		return 0;
	
	}
	else if ((argc == 2) && (strcmp(argv[1], "-t") == 0)) {
		

		return 0;
	}
	else {
		cout << "kukli";
	}
}
	





	

	

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
