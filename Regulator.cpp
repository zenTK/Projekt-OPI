#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cstring>
#include <cmath>
#include <limits>

using namespace std;

int zelenaTemp;		 // zelena Temparatura
int zelenaVlaz;		 // zelena vlaznost
int zelenaOsv = 500; // zelena osvetljenost
int trenutnaTemp;
int trenutnaVlaz;
int trenutnaOsv;
int izbiraNacina;
int izbiraNacinaTestni;
int izbiraTestniRocni;
int nadaljevanjeSim;
string c = "[C]";
string f = "[F]";
string k = "[K]";
bool dela = true;
bool niStevilo = true;

void prelom()
{
	cout << "----------------------------------------------------------------------------------- \n";
}

void prekinitevSimulacije()
{
	prelom();
	cout << "Zelite nadaljevati s simulacijo?\n";
	cout << "Za nadaljevanje simulacije pritisnite 1 \nZa prekinitev simulacije pritisnite 2\n";
	cin >> nadaljevanjeSim;

	while (nadaljevanjeSim != 1 && nadaljevanjeSim != 2)
	{
		cout << "Za nadaljevanje simulacije pritisnite 1 \nZa prekinitev simulacije pritisnite 2\n";
		cin >> nadaljevanjeSim;
	}

	if (nadaljevanjeSim == 1)
	{
		dela = true;
		prelom();
	}
	else if (nadaljevanjeSim == 2)
	{
		dela = false;
	}
}

void enotaZelenaTemp()
{
	if (zelenaTemp <= 30 && zelenaTemp >= 10)
	{
		cout << c;
	}
	else if (zelenaTemp > 30 && zelenaTemp <= 90)
	{
		cout << f;
	}
	else if (zelenaTemp >= 283 && zelenaTemp <= 303)
	{
		cout << k;
	}
}

void enotaTrenutnaTemp()
{

	if ((zelenaTemp <= 30 && zelenaTemp >= 10) && (trenutnaTemp >= 10 && trenutnaTemp <= 30))
	{ // Celzij
		trenutnaTemp = trenutnaTemp;
		cout << trenutnaTemp << c << endl;
	}
	else if ((zelenaTemp <= 30 && zelenaTemp >= 10) && !(trenutnaTemp >= 10 && trenutnaTemp <= 30) && (trenutnaTemp >= 283 && trenutnaTemp <= 303))
	{ // Kelvin v Celzij
		trenutnaTemp = trenutnaTemp - 273.13;
		cout << trenutnaTemp << c << endl;
	}
	else if ((zelenaTemp <= 30 && zelenaTemp >= 10) && !(trenutnaTemp >= 10 && trenutnaTemp <= 30) && (trenutnaTemp > 30 && trenutnaTemp <= 90))
	{ // Fahrenheit v Celzij
		trenutnaTemp = (trenutnaTemp - 32) / 1.8;
		cout << trenutnaTemp << c << endl;
	}
	else if ((zelenaTemp > 30 && zelenaTemp <= 90) && (trenutnaTemp > 30 && trenutnaTemp <= 90))
	{ // Fahrenheit
		trenutnaTemp = trenutnaTemp;
		cout << trenutnaTemp << f << endl;
	}
	else if ((zelenaTemp > 30 && zelenaTemp <= 90) && !(trenutnaTemp > 30 && trenutnaTemp <= 90) && (trenutnaTemp >= 283 && trenutnaTemp <= 303))
	{ // Kelvin v Fahrenheit
		trenutnaTemp = trenutnaTemp * 1.8 - 459.67;
		cout << trenutnaTemp << f << endl;
	}
	else if ((zelenaTemp > 30 && zelenaTemp <= 90) && !(trenutnaTemp > 30 && trenutnaTemp <= 90) && (trenutnaTemp >= 10 && trenutnaTemp <= 30))
	{ // Celzij v Fahrenheit
		trenutnaTemp = trenutnaTemp * 1.8 + 32;
		cout << trenutnaTemp << f << endl;
	}
	else if ((zelenaTemp >= 283 && zelenaTemp <= 303) && (trenutnaTemp >= 283 && trenutnaTemp <= 303))
	{ // Kelvin
		trenutnaTemp = trenutnaTemp;
		cout << trenutnaTemp << k << endl;
	}
	else if ((zelenaTemp >= 283 && zelenaTemp <= 303) && !(trenutnaTemp >= 283 && trenutnaTemp <= 303) && (trenutnaTemp >= 10 && trenutnaTemp <= 30))
	{ // Celzij v Kelvin
		trenutnaTemp = trenutnaTemp + 273.13;
		cout << trenutnaTemp << k << endl;
	}
	else if ((zelenaTemp >= 283 && zelenaTemp <= 303) && !(trenutnaTemp >= 283 && trenutnaTemp <= 303) && (trenutnaTemp > 30 && trenutnaTemp <= 90))
	{ // Fahrenheit v Kelvin
		trenutnaTemp = (trenutnaTemp + 459.67) * 5 / 9;
		cout << trenutnaTemp << k << endl;
	}
}

void vnesiZeleneLastnosti()
{
	cout << "Vnesi zeleno: ";
	cout << "\nTemperaturo[C, K in F]: ";
	cin >> zelenaTemp;
	enotaZelenaTemp();

	while (niStevilo)
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Izberi temparaturo med 10 C in 30C, 31F in 90F ali 283 K in 303K\n";
			cout << "Temperatura: ";
			cin >> zelenaTemp;
			enotaZelenaTemp();
		}
		else if ((zelenaTemp < 10) || ((zelenaTemp > 90) && (zelenaTemp < 283)) || (zelenaTemp > 303))
		{
			cout << "Izberi temparaturo med 10 C in 30C, 31F in 90F ali 283 K in 303K\n";
			cout << "Temperatura: ";
			cin >> zelenaTemp;
			enotaZelenaTemp();
		}
		else
		{
			niStevilo = false;
		}
	}

	cout << "\nVlaznost[%]: ";
	cin >> zelenaVlaz;
	cout << "[%]\n";

	while(cin.fail() || (zelenaVlaz > 100) || (zelenaVlaz < 0))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Vnesi stopnjo vlaznosti med 0 in 100: \n";
		cout << "Vlaznost: ";
		cin >> zelenaVlaz;
	}

	/*while(!(zelenaVlaz <= 10) && (zelenaVlaz >= 0))
	{
		cout << "Vnesi stopnjo vlaznosti med 0 in 100: \n";
		cout << "Vlaznost: ";
		cin >> zelenaVlaz;
	}
	*/
}

void vnesiTrenutneLastnosti()
{
	cout << "Vnesi trenutne lastnosti\n";
	cout << "\tTemperatura[C, K in F]: "; // simbol za stopinje ne dela v cmd-ju
	cin >> trenutnaTemp;
	enotaTrenutnaTemp();

	while ((trenutnaTemp < 10) || ((trenutnaTemp > 90) && (trenutnaTemp < 283)) || (trenutnaTemp > 303))
	{
		cout << "Izberi temparaturo med 10 C in 30C, 31F in 90F ali 283 K in 303K\n";
		cout << "Temperatura: ";
		cin >> trenutnaTemp;
		enotaTrenutnaTemp();
	}

	cout << endl;
	cout << "\tVlaznost[%]: ";
	cin >> trenutnaVlaz;
	cout << endl;
	cout << "\tOsvetljenost[lx]: ";
	cin >> trenutnaOsv;
	cout << endl;
}

void glavniMeni()
{
	cout << "GLAVNI MENI" << endl;
	cout << "===========" << endl;
	cout << "1.) Rocni nacin\n"
		 << "2.) Avtomatski nacin\n"
		 << "3.) Avtomatski nacin 2\n"
		 << "4.) Pomoc\n"
		 << "0.) Izhod" << endl;
}

void glavniMeniTestniNacin()
{
	cout << "Kateri rezim zelis testirati?" << endl;
	cout << "====================" << endl;
	cout << "1.) Rocni nacin\n"
		 << "2.) Avtomatski nacin\n"
		 << "3.) Avtomatski nacin 2\n";
}

void meniTestniRocni()
{
	cout << "Katero lastnost zelis testirat?\n";
	cout << "===============================\n";
	cout << "1.) Temperaturo\n"
		 << "2.) Vlaznost\n"
		 << "3.) Osvetljenost\n";
}

void datoteka()
{
	ofstream mojaDatOut;
	mojaDatOut.open("Zeljene_ambientalne_lastnosti.txt");
	if (mojaDatOut.is_open())
	{
		mojaDatOut << "TEMPERATURA[C, F ali K]: " << zelenaTemp;
		if (zelenaTemp <= 30 && zelenaTemp >= 10)
		{
			mojaDatOut << "[C]";
		}
		else if (zelenaTemp > 30 && zelenaTemp <= 90)
		{
			mojaDatOut << "[F]";
		}
		else if (zelenaTemp >= 283 && zelenaTemp <= 303)
		{
			mojaDatOut << "[K]";
		}

		mojaDatOut << "\nVLAZNOST[%]: " << zelenaVlaz << "[%]\nOSVETLJENOST[lx]: " << zelenaOsv << "[lx]\n";
		mojaDatOut << "\nINTERVAL TEMPERATURE: [10,40] [C]\nSTOPNJA VLAZNOSTI: [30,60] [%]\nINTERVAL OSVETLJENOSTI: [10,1000] [lx]";
		mojaDatOut.close();
	}
	else
	{
		cout << "Napaka pri odpiranju";
	}

	ifstream mojaDatIn;
	mojaDatIn.open("Zeljene_ambientalne_lastnosti.txt");
	if (mojaDatIn.is_open())
	{
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
void vnesiTrenutnoTemp()
{
	cout << "Vnesi trenutno temperaturo:\n";
	cout << "\tTemperatura[C, K in F]: \n";
	cin >> trenutnaTemp;
	enotaTrenutnaTemp();
	while ((trenutnaTemp < 10) || ((trenutnaTemp > 90) && (trenutnaTemp < 283)) || (trenutnaTemp > 303))
	{
		cout << "Izberi temparaturo med 10 C in 30C, 31F in 90F ali 283 K in 303K\n";
		cout << "Temperatura: ";
		cin >> trenutnaTemp;
		enotaTrenutnaTemp();
	}
}

void ukazZaRegulacijoTemp()
{
	if ((zelenaTemp - trenutnaTemp) > 0)
	{
		cout << "Vklop grelca\n";
	}
	else if ((zelenaTemp - trenutnaTemp) < 0)
	{
		cout << "Izklop grelca\n";
	}
	else
	{
		cout << "Temperatura v prostoru je optimalna\n";
	}

	if ((trenutnaTemp - zelenaTemp) >= 10)
	{
		trenutnaVlaz = trenutnaVlaz * 1.05;
	}
}

void vnesiTrenutnoVlaznost()
{
	cout << "\nVnesi trenutno vlaznost\n";
	cout << "Vlaznost[%]:\n";
	cin >> trenutnaVlaz;
}
void ukazZaRegulacijoVlaz()
{
	if ((zelenaVlaz - trenutnaVlaz) > 0)
	{
		cout << "Vklop vlazilca\n";
	}
	else if ((zelenaVlaz - trenutnaVlaz) < 0)
	{
		cout << "Izklop vlazilca\n";
	}
	else
	{
		cout << "Vlaznost v prostoru je optimalna\n";
	}
}

void vnesiTrenutnoOsv()
{
	cout << "Vnesi trenutno osvetljenost:\n";
	cout << "\tOsvetljenost[lx]: \n";
	cin >> trenutnaOsv;

	while (trenutnaOsv < 10)
	{
		cout << "Vnesi vrednost vecjo ali enako 10, saj nisi v temi :)" << endl;
		cin >> trenutnaOsv;
	}
}

void ukazZaRegulacijoOsv()
{

	if (trenutnaOsv >= 8000)
	{
		cout << "Izklop luci in zatemnitev rolet" << endl;
	}
	else if ((trenutnaOsv > 500) && (trenutnaOsv < 8000))
	{
		cout << "Izklop luci" << endl;
	}
	else if ((trenutnaOsv > 100) && (trenutnaOsv < 500))
	{
		cout << "Prizig luci" << endl;
	}
	else if ((trenutnaOsv >= 10) && (trenutnaOsv <= 100))
	{
		cout << "Prizig luci in odprtje rolet" << endl;
	}
	else if (trenutnaOsv == 500)
	{
		cout << "Osvetljenost prostora je optimalna" << endl;
	}
}

int main(int argc, char *argv[]) // MAIN
{
	cout << "Regulator, verzija 0.1\n";
	prelom();
	vnesiZeleneLastnosti();
	prelom();
	datoteka();
	prelom();

	if (argc == 1)
	{

		while (dela)
		{
			glavniMeni();
			cin >> izbiraNacina;

			while (izbiraNacina != 0 && izbiraNacina != 1 && izbiraNacina != 2 && izbiraNacina != 3)
			{
				glavniMeni();
				cin >> izbiraNacina;
			}

			if (izbiraNacina == 1)
			{
				vnesiTrenutneLastnosti();
				ukazZaRegulacijoTemp();
				ukazZaRegulacijoVlaz();
				ukazZaRegulacijoOsv();
			}
			else if (izbiraNacina == 2)
			{
				cout << "2222";
			}
			else if (izbiraNacina == 3)
			{
				cout << "3333";
			}
			else if (izbiraNacina == 0)
			{
				return 0;
			}
			prekinitevSimulacije();
		}

		return 0;
	}
	else if ((argc == 2) && (strcmp(argv[1], "-t") == 0))
	{
		cout << "\t\nPOZDRAVLJEN/A V TESTNEM NACINU\n";
		while (dela)
		{
			glavniMeniTestniNacin();
			cin >> izbiraNacinaTestni;
			while (izbiraNacinaTestni != 1 && izbiraNacinaTestni != 2 && izbiraNacinaTestni != 3)
			{
				glavniMeniTestniNacin();
				cin >> izbiraNacinaTestni;
			}
			if (izbiraNacinaTestni == 1)
			{
				meniTestniRocni();
				cin >> izbiraTestniRocni;
				while (izbiraTestniRocni != 1 && izbiraTestniRocni != 2 && izbiraTestniRocni != 3)
				{
					meniTestniRocni();
					cin >> izbiraTestniRocni;
				}
				if (izbiraTestniRocni == 1)
				{
					vnesiTrenutnoTemp();
					ukazZaRegulacijoTemp();
				}
				else if (izbiraTestniRocni == 2)
				{
					vnesiTrenutnoVlaznost();
					ukazZaRegulacijoVlaz();
				}
				else if (izbiraTestniRocni == 3)
				{
					vnesiTrenutnoOsv();
					ukazZaRegulacijoOsv();
				}
			}
			prekinitevSimulacije();
		}
		return 0;
	}
	else
	{
		cout << "TBD...";
	}
}