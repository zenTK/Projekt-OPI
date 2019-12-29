#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cstring>
#include <cmath>
#include <limits>
#include <array>
#include <numeric>
#include <stdlib.h>  // srand, rand
#include <time.h>    // time
#include <windows.h> // sleep

using namespace std;

int zelenaTemp;      // zelena Temparatura
int zelenaVlaz;      // zelena vlaznost
int zelenaOsv = 500; // zelena osvetljenost
int trenutnaTemp;
int trenutnaVlaz;
int trenutnaOsv;
int izbiraNacina;
int izbiraNacinaTestni;
int izbiraTestniRocni;
int nadaljevanjeSim;
int line_no = 0;
int tempSpodnjaMeja;
int tempZgornjaMeja;
int vlazSpodnjaMeja;
int vlazZgornjaMeja;
int osvSpodnjaMeja;
int osvZgornjaMeja;
int povpVrednost = 0;
int stPonovitev = 0;
int casovniRazmik;
int seed;
string c = "[C]";
string f = "[F]";
string k = "[K]";
string imeDat;
string sLine = "";
string stevilo1;
string stevilo2;
string stevilo3;
string stevilo4;
string stevilo5;
string stevilo6;
bool dela = true;
bool niStevilo = true;

void prelom()
{
    cout << "\n----------------------------------------------------------------------------------- \n";
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
    if (zelenaTemp <= 40 && zelenaTemp >= 10)
    {
        cout << c;
    }
    else if (zelenaTemp > 40 && zelenaTemp <= 110)
    {
        cout << f;
    }
    else if (zelenaTemp >= 283 && zelenaTemp <= 313)
    {
        cout << k;
    }
}

void enotaTrenutnaTemp()
{

    if ((zelenaTemp <= 40 && zelenaTemp >= 10) && (trenutnaTemp >= 10 && trenutnaTemp <= 40))
    { // Celzij
        trenutnaTemp = trenutnaTemp;
        cout << trenutnaTemp << c << endl;
    }
    else if ((zelenaTemp <= 40 && zelenaTemp >= 10) && !(trenutnaTemp >= 10 && trenutnaTemp <= 40) && (trenutnaTemp >= 283 && trenutnaTemp <= 313))
    { // Kelvin v Celzij
        trenutnaTemp = trenutnaTemp - 273.13;
        cout << trenutnaTemp << c << endl;
    }
    else if ((zelenaTemp <= 40 && zelenaTemp >= 10) && !(trenutnaTemp >= 10 && trenutnaTemp <= 40) && (trenutnaTemp > 40 && trenutnaTemp <= 110))
    { // Fahrenheit v Celzij
        trenutnaTemp = (trenutnaTemp - 32) / 1.8;
        cout << trenutnaTemp << c << endl;
    }
    else if ((zelenaTemp > 40 && zelenaTemp <= 110) && (trenutnaTemp > 40 && trenutnaTemp <= 110))
    { // Fahrenheit
        trenutnaTemp = trenutnaTemp;
        cout << trenutnaTemp << f << endl;
    }
    else if ((zelenaTemp > 40 && zelenaTemp <= 110) && !(trenutnaTemp > 40 && trenutnaTemp <= 90) && (trenutnaTemp >= 283 && trenutnaTemp <= 313))
    { // Kelvin v Fahrenheit
        trenutnaTemp = trenutnaTemp * 1.8 - 459.67;
        cout << trenutnaTemp << f << endl;
    }
    else if ((zelenaTemp > 40 && zelenaTemp <= 110) && !(trenutnaTemp > 40 && trenutnaTemp <= 110) && (trenutnaTemp >= 10 && trenutnaTemp <= 40))
    { // Celzij v Fahrenheit
        trenutnaTemp = trenutnaTemp * 1.8 + 32;
        cout << trenutnaTemp << f << endl;
    }
    else if ((zelenaTemp >= 283 && zelenaTemp <= 313) && (trenutnaTemp >= 283 && trenutnaTemp <= 313))
    { // Kelvin
        trenutnaTemp = trenutnaTemp;
        cout << trenutnaTemp << k << endl;
    }
    else if ((zelenaTemp >= 283 && zelenaTemp <= 313) && !(trenutnaTemp >= 283 && trenutnaTemp <= 313) && (trenutnaTemp >= 10 && trenutnaTemp <= 40))
    { // Celzij v Kelvin
        trenutnaTemp = trenutnaTemp + 273.13;
        cout << trenutnaTemp << k << endl;
    }
    else if ((zelenaTemp >= 283 && zelenaTemp <= 313) && !(trenutnaTemp >= 283 && trenutnaTemp <= 313) && (trenutnaTemp > 40 && trenutnaTemp <= 110))
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
            cout << "Izberi temparaturo med 10 C in 40C, 41F in 110F ali 283 K in 313K\n";
            cout << "Temperatura: ";
            cin >> zelenaTemp;
            enotaZelenaTemp();
        }
        else if ((zelenaTemp < 10) || ((zelenaTemp > 110) && (zelenaTemp < 283)) || (zelenaTemp > 313))
        {
            cout << "Izberi temparaturo med 10 C in 40C, 41F in 110F ali 283 K in 313K\n";
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

    while (cin.fail() || (zelenaVlaz > 100) || (zelenaVlaz < 0))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Vnesi stopnjo vlaznosti med 0 in 100: \n";
        cout << "Vlaznost: ";
        cin >> zelenaVlaz;
    }
}

void vnesiTrenutneLastnosti()
{
    cout << "Vnesi trenutne lastnosti\n";
    cout << "Temperatura[C, K in F]: "; // simbol za stopinje ne dela v cmd-ju
    cin >> trenutnaTemp;

    while ((trenutnaTemp < 10) || ((trenutnaTemp > 90) && (trenutnaTemp < 283)) || (trenutnaTemp > 313) || cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Izberi temparaturo med 10 C in 40C, 41F in 110F ali 293K in 313K\n";
        cout << "Temperatura: ";
        cin >> trenutnaTemp;
        enotaTrenutnaTemp();
    }

    enotaTrenutnaTemp();

    cout << endl;
    cout << "Vlaznost[%]: ";
    cin >> trenutnaVlaz;
    cout << endl;

    while (cin.fail() || trenutnaVlaz < 0 || trenutnaVlaz > 100)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Vnesi stopnjo vlaznosti med 0 in 100: \n";
        cout << "Vlaznost: ";
        cin >> trenutnaVlaz;
    }

    cout << "Osvetljenost[lx]: ";
    cin >> trenutnaOsv;
    cout << endl;

    while (cin.fail() || trenutnaOsv <= 10)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Vnesi moc osvetljenosti vecjo ali enako 10 \n";
        cout << "Osvetljenost: ";
        cin >> trenutnaOsv;
    }
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
    mojaDatOut.open(imeDat.c_str());
    if (mojaDatOut.is_open())
    {
        mojaDatOut << "TEMPERATURA[C, F ali K]: " << zelenaTemp;
        if (zelenaTemp <= 40 && zelenaTemp >= 10)
        {
            mojaDatOut << "[C]";
        }
        else if (zelenaTemp > 40 && zelenaTemp <= 110)
        {
            mojaDatOut << "[F]";
        }
        else if (zelenaTemp >= 283 && zelenaTemp <= 313)
        {
            mojaDatOut << "[K]";
        }

        mojaDatOut << "\nVLAZNOST[%]: " << zelenaVlaz << "[%]\nOSVETLJENOST[lx]: " << zelenaOsv << "[lx]\n";
        mojaDatOut << "\nINTERVAL TEMPERATURE: [10,40] [C]\nSTOPNJA VLAZNOSTI: [30,60] [%]\nINTERVAL OSVETLJENOSTI: [10,10000] [lx]";
        mojaDatOut.close();
    }
    else
    {
        cout << "Napaka pri odpiranju";
    }

    ifstream mojaDatIn;
    mojaDatIn.open(imeDat.c_str());
    if (mojaDatIn.is_open())
    {
        cout << "Ambientalne lastnosti bodo prilagojene na: \nTemperatura: " << zelenaTemp;
        enotaZelenaTemp();
        cout << "\nVlaznost: " << zelenaVlaz << "[%]";
        cout << "\nOsvetljenost: " << zelenaOsv << "[lx]\n";

        while (line_no != 5 && getline(mojaDatIn, sLine))
        {
            ++line_no;
        }

        if (line_no == 5) // pridobivanje spodnje in zgornje meje intervala temparature iz datoteke
        {
            int index = sLine.find_first_of("[");
            stevilo1 = sLine.substr(index + 1, 2);
            tempSpodnjaMeja = stoi(stevilo1);
            cout << tempSpodnjaMeja << endl;

            int index1 = sLine.find_first_of(",");
            stevilo2 = sLine.substr(index1 + 1, 2);
            tempZgornjaMeja = stoi(stevilo2);
            cout << tempZgornjaMeja << endl;
        }
        else
        {
            cout << "umri";
        }

        while (line_no != 6 && getline(mojaDatIn, sLine))
        {
            ++line_no;
        }

        if (line_no == 6)
        {
            int index2 = sLine.find_first_of("[");
            stevilo3 = sLine.substr(index2 + 1, 2);
            vlazSpodnjaMeja = stoi(stevilo3);
            cout << stevilo3 << endl;

            int index3 = sLine.find_first_of(",");
            stevilo4 = sLine.substr(index3 + 1, 2);
            vlazZgornjaMeja = stoi(stevilo4);
            cout << stevilo4 << endl;
        }
        else
        {
            cout << "umri";
        }
        while (line_no != 7 && getline(mojaDatIn, sLine))
        {
            ++line_no;
        }

        if (line_no == 7)
        {
            int index4 = sLine.find_first_of("[");
            stevilo5 = sLine.substr(index4 + 1, 2);
            osvSpodnjaMeja = stoi(stevilo5);
            cout << stevilo5 << endl;

            int index5 = sLine.find_first_of(",");
            stevilo6 = sLine.substr(index5 + 1, 5); // pri vseh še treba spremenit dolžino branja glede na dolžino stevila v datoteki
            osvZgornjaMeja = stoi(stevilo6);
            cout << stevilo6 << endl;
        }
        else
        {
            cout << "umri";
        }

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
    while ((trenutnaTemp < 10) || ((trenutnaTemp > 110) && (trenutnaTemp < 283)) || (trenutnaTemp > 313))
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
        trenutnaVlaz = trenutnaVlaz * 1.05; // če je razlika med dejansko in želeno temperaturo večja ali enaka 10, se vlaznost poveča za 5%
    }
    else if ((trenutnaTemp - zelenaTemp) <= -10)
    {
        trenutnaVlaz = trenutnaVlaz * 0.95; // če je razlika med dejansko in želeno temperaturo manjša ali enaka 10, se vlaznost zniža za 5%
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

void avtomatskiNacin()
{
    srand(time(NULL)); // naključen seed

    for (int i = 0; i < 4; i++)
    {

        int intervalTemp = tempZgornjaMeja - tempSpodnjaMeja + 1;
        int intervalVlaz = vlazZgornjaMeja - vlazSpodnjaMeja + 1;
        int intervalOsv = osvZgornjaMeja - osvSpodnjaMeja + 1;

        trenutnaTemp = rand() % intervalTemp + tempSpodnjaMeja;
        trenutnaVlaz = rand() % intervalVlaz + vlazSpodnjaMeja;
        trenutnaOsv = rand() % intervalOsv + osvSpodnjaMeja;

        cout << "Zelena temperatura: " << zelenaTemp;
        enotaZelenaTemp();
        cout << endl;
        cout << "Zelena vlaznost: " << zelenaVlaz << endl;
        cout << "Zelena osvetljenost: " << zelenaOsv << endl;
        cout << endl;

        cout << "Trenutna temperatura: ";
        enotaTrenutnaTemp();
        cout << "Trenutna vlaznost: " << trenutnaVlaz << endl;
        cout << "Trenutna osvetljenost: " << trenutnaOsv << endl;

        cout << endl;

        ukazZaRegulacijoTemp();
        ukazZaRegulacijoVlaz();
        ukazZaRegulacijoOsv();
        prelom();
        povpVrednost += trenutnaTemp;
        //  Sleep(3000); // ponovitev zanke vsake 3 sekunde
    }
    povpVrednost = povpVrednost / 4;
    cout << "Povprecna vrednost dejanske temperature: ";
    cout << povpVrednost;
    povpVrednost = 0; // reset na 0, da se v ponovnem zagonu funkcije ne sestevajo še stare vrednosti
}

void avtomatskiNacin2()
{
    cout << "Koliko ponovitev naj naredi simulator? " << endl;
    cin >> stPonovitev;
    cout << "Koliko naj bo casovni razmik(milisekunde) med ponovitvami? " << endl;
    cin >> casovniRazmik;

    srand(time(NULL)); // naključen seed

    for (int i = 0; i < stPonovitev; i++)
    {

        int intervalTemp = tempZgornjaMeja - tempSpodnjaMeja + 1;
        int intervalVlaz = vlazZgornjaMeja - vlazSpodnjaMeja + 1;
        int intervalOsv = osvZgornjaMeja - osvSpodnjaMeja + 1;

        trenutnaTemp = rand() % intervalTemp + tempSpodnjaMeja;
        trenutnaVlaz = rand() % intervalVlaz + vlazSpodnjaMeja;
        trenutnaOsv = rand() % intervalOsv + osvSpodnjaMeja;

        cout << "Zelena temperatura: " << zelenaTemp;
        enotaZelenaTemp();
        cout << endl;
        cout << "Zelena vlaznost: " << zelenaVlaz << endl;
        cout << "Zelena osvetljenost: " << zelenaOsv << endl;
        cout << endl;

        cout << "Trenutna temperatura: ";
        enotaTrenutnaTemp();
        cout << "Trenutna vlaznost: " << trenutnaVlaz << endl;
        cout << "Trenutna osvetljenost: " << trenutnaOsv << endl;

        cout << endl;

        ukazZaRegulacijoTemp();
        ukazZaRegulacijoVlaz();
        ukazZaRegulacijoOsv();
        prelom();
        povpVrednost += trenutnaTemp;
        Sleep(casovniRazmik); // ponovitev zanke vsakih x sekund
    }
    povpVrednost = povpVrednost / stPonovitev;
    cout << "Povprecna vrednost dejanske temperature: ";
    cout << povpVrednost;
    povpVrednost = 0; // reset na 0, da se v ponovnem zagonu funkcije ne sestevajo še stare vrednosti
}

void avtomatskiTestniNacin()
{
    cout << "Izberi seed za ponovljivost simulacij: " << endl;
    cin >> seed;
    srand(seed); // generiral bo vedno iste ambientalne lastnosti za izbran seed

    for (int i = 0; i < 4; i++)
    {

        int intervalTemp = tempZgornjaMeja - tempSpodnjaMeja + 1;
        int intervalVlaz = vlazZgornjaMeja - vlazSpodnjaMeja + 1;
        int intervalOsv = osvZgornjaMeja - osvSpodnjaMeja + 1;

        trenutnaTemp = rand() % intervalTemp + tempSpodnjaMeja;
        trenutnaVlaz = rand() % intervalVlaz + vlazSpodnjaMeja;
        trenutnaOsv = rand() % intervalOsv + osvSpodnjaMeja;

        cout << "Zelena temperatura: " << zelenaTemp;
        enotaZelenaTemp();
        cout << endl;
        cout << "Zelena vlaznost: " << zelenaVlaz << endl;
        cout << "Zelena osvetljenost: " << zelenaOsv << endl;
        cout << endl;

        cout << "Trenutna temperatura: ";
        enotaTrenutnaTemp();
        cout << "Trenutna vlaznost: " << trenutnaVlaz << endl;
        cout << "Trenutna osvetljenost: " << trenutnaOsv << endl;

        cout << endl;

        ukazZaRegulacijoTemp();
        ukazZaRegulacijoVlaz();
        ukazZaRegulacijoOsv();
        prelom();
        povpVrednost += trenutnaTemp;
        //  Sleep(3000); // ponovitev zanke vsake 3 sekunde
    }
    povpVrednost = povpVrednost / 4;
    cout << "Povprecna vrednost dejanske temperature: ";
    cout << povpVrednost;
    povpVrednost = 0; // reset na 0, da se v ponovnem zagonu funkcije ne sestevajo še stare vrednosti
}


int main(int argc, char *argv[]) // MAIN
{
    cout << "Regulator, verzija 0.1\n";
    prelom();
    cout << "Vnesite ime datoteke v katero bodo shranjene lastnosti: \n";
    cin >> imeDat;
    imeDat += ".txt";

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
                avtomatskiNacin();
            }
            else if (izbiraNacina == 3)
            {
                avtomatskiNacin2();
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
                prekinitevSimulacije();
            }
            else if (izbiraNacinaTestni == 2)
            {
                avtomatskiTestniNacin();
            }
            prekinitevSimulacije();
        }
    }
    return 0;
}