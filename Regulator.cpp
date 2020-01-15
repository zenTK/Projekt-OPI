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
#include <cmath>     // abs

using namespace std;

/*
 * AVTOR: Dominik Božnik
*/

/* REGULATOR 
 * Regulator.cpp je program, ki omogoča reguliranje temperature, vlažnosti in osvetljenosti v prostoru.
 * Na začetku uporabnik vnese želene ambientalne lastnosti, ki se vpišejo v tekstovno datoteko.
 * Program omogoča tri načine delovanja: Ročni, Avtomatski in Avtomatski 2.
 * V ročnem načinu uporabnik vnese dejansko temperaturo v prostoru. Program omogoča prepoznavo in pretvorbo merske enote
 * z enoto želene temperature. Izračuna tudi razliko do želene temperature ter izvede ukaz za regulacijo.
 * V avtomatskem načinu si računalnik izmisli dejanske lastnosti glede na intervalu podanem v datoteki.
 * Izvede 100 meritev vsake 3 sekunde. Na koncu še izračuna povprečno vrednost dejanskih ambientalnih lastnosti ter
 * povprečno odstopanje od želenih vrednosti.
 * V avtomatskem 2 simulator naredi isto kot pri avtomatskem načinu, vendar omogoča uporabniku izbiro
 * pri številu meritev in časovnem razmiku med posamezno meritvijo.
 * 
 * Možen je tudi zagon v testnem načinu.
 * Testni ročni način omogoča posamičen zagon ukaza za regulacij(npr. samo za temperaturo)
 * Testni avtomatski način pa omogoča izbiro "seed-a", kar pomeni, da je možna ponovljivost simulacij.
*/

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
int povpVrednostTemp = 0;
int povpVrednostVlaz = 0;
int povpVrednostOsv = 0;
int stPonovitev = 0;
int stPonovitevTestni = 0;
int casovniRazmik;
int casovniRazmikTestni = 0;
int seed;
int seedTestni = 0;
int razlikaTemp;
int razlikaVlaz;
int razlikaOsv;
int sumTemp;
int sumVlaz;
int sumOsv;
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

void nepravilenVnos() // kliče se ob vsakem neveljavem vnosu uporabnika
{
    cout << "\nVnesli ste nepravilen vnos. Ponovno vnesite vrednost. \n";
}

void prekinitevSimulacije() // vprasa za prekinitev simulacije ali za nadaljevanje
{
    prelom();
    cout << "Zelite nadaljevati s simulacijo?\n";
    cout << "Za nadaljevanje simulacije pritisnite 1 \nZa prekinitev simulacije pritisnite 2\n";
    cin >> nadaljevanjeSim;

    while (cin.fail() || nadaljevanjeSim != 1 && nadaljevanjeSim != 2) // zanka, ki se ponavlja ob neveljavnem vnosu uporabnika
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        nepravilenVnos();
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

void enotaZelenaTemp() // glede na vneseno zeleno temperaturo doda enoto
{
    if (zelenaTemp <= 40 && zelenaTemp >= 10) // med 10 in 40 so stopinje celzija
    {
        cout << c;
    }
    else if (zelenaTemp > 40 && zelenaTemp <= 110) // med 41 in 110 so fahrenheiti
    {
        cout << f;
    }
    else if (zelenaTemp >= 283 && zelenaTemp <= 313) // med 283 in 313 so kelvini
    {
        cout << k;
    }
}

void enotaTrenutnaTemp() // glede na vneseno trenutno temperaturo pretvori v enoto, ki se sklada s enoto zelene temperature
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

void vnesiZeleneLastnosti() // vnos zelene temperature
{
    cout << "Vnesi zeleno: ";
    cout << "\nTemperaturo[C, K in F]: ";
    cin >> zelenaTemp;
    enotaZelenaTemp();

    while (niStevilo) // zanka za preverjanje veljavnosti vnosa uporabnika (napisana malo drugače, kot primer zgoraj in ostali primeri)
    {
        if (cin.fail()) // 
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            nepravilenVnos();
            cout << "Izberi temparaturo med 10 C in 40C, 41F in 110F ali 283 K in 313K\n";
            cout << "Temperatura: ";
            cin >> zelenaTemp;
            enotaZelenaTemp();
        }
        else if ((zelenaTemp < 10) || ((zelenaTemp > 110) && (zelenaTemp < 283)) || (zelenaTemp > 313)) // če želena temperatura ni v danih mejah javi nepravilen vnos
        {
            nepravilenVnos();
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

    while (cin.fail() || (zelenaVlaz > 100) || (zelenaVlaz < 1)) // če vlaznost ni med 1 in 100 javi kot nepravilen vnos (ali pa je vnesen neveljaven znak(npr. string))
    {
        nepravilenVnos();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Vnesi stopnjo vlaznosti med 0 in 100: \n";
        cout << "Vlaznost: ";
        cin >> zelenaVlaz;
    }
}

void vnesiTrenutneLastnosti() // vnos dejanskih ambientalnih lastnosti
{
    cout << "Vnesi trenutne lastnosti\n";
    cout << "Temperatura[C, K in F]: "; // simbol za stopinje ne dela v cmd-ju
    cin >> trenutnaTemp;

    while ((trenutnaTemp < 10) || ((trenutnaTemp > 90) && (trenutnaTemp < 283)) || (trenutnaTemp > 313) || cin.fail())
    {
        nepravilenVnos();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Izberi temparaturo med 10 C in 40C, 41F in 110F ali 293K in 313K\n";
        cout << "Temperatura: ";
        cin >> trenutnaTemp;
    }

    enotaTrenutnaTemp();

    cout << endl;
    cout << "Vlaznost[%]: ";
    cin >> trenutnaVlaz;
    cout << "[%]" << endl;

    while (cin.fail() || trenutnaVlaz < 0 || trenutnaVlaz > 100)
    {
        nepravilenVnos();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Vnesi stopnjo vlaznosti med 0 in 100: \n";
        cout << "Vlaznost: ";
        cin >> trenutnaVlaz;
    }

    cout << "Osvetljenost[lx]: ";
    cin >> trenutnaOsv;
    cout << "[lx]" << endl;

    while (cin.fail() || trenutnaOsv <= 10 || trenutnaOsv > 10000)
    {
        nepravilenVnos();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Vnesi moc osvetljenosti vecjo ali enako 10 in manjso od 10000 \n\n";
        cout << "Osvetljenost[lx]: ";
        cin >> trenutnaOsv;
    }
}

void glavniMeni() // izpis menija v glavnem načinu
{
    cout << "GLAVNI MENI" << endl;
    cout << "===========" << endl;
    cout << "1.) Rocni nacin\n"
         << "2.) Avtomatski nacin\n"
         << "3.) Avtomatski nacin 2\n"
         << "4.) Pomoc\n"
         << "0.) Izhod" << endl;
}

void glavniMeniTestniNacin() // izpis menija v testnem načinu
{
    cout << "Kateri rezim zelis testirati?" << endl;
    cout << "====================" << endl;
    cout << "1.) Rocni nacin\n"
         << "2.) Avtomatski nacin\n";
}

void meniTestniRocni() // izpis menija v testnem ročnem načinu
{
    cout << "Katero lastnost zelis testirat?\n";
    cout << "===============================\n";
    cout << "1.) Temperaturo\n"
         << "2.) Vlaznost\n"
         << "3.) Osvetljenost\n";
}

void datoteka() // pisanje in branje lastnosti v glavno datoteko
{
    //pisanje
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

    // branje
    ifstream mojaDatIn;
    mojaDatIn.open(imeDat.c_str());
    if (mojaDatIn.is_open())
    {
        cout << "Ambientalne lastnosti bodo prilagojene na: \nTemperatura: " << zelenaTemp;
        enotaZelenaTemp();
        cout << "\nVlaznost: " << zelenaVlaz << "[%]";
        cout << "\nOsvetljenost: " << zelenaOsv << "[lx]\n";

        while (line_no != 5 && getline(mojaDatIn, sLine)) // branje 5 linije v datoteki
        {
            ++line_no;
        }

        if (line_no == 5) // pridobivanje spodnje in zgornje meje intervala temparature iz datoteke
        {
            // poišče kje v datoteki v 5 liniji je prvi "[" in od tam prebere dvomestno število
            int index = sLine.find_first_of("[");
            stevilo1 = sLine.substr(index + 1, 2);
            tempSpodnjaMeja = stoi(stevilo1);

            // poišče kje v datoteki v 5 linije je prva "," in od tam prebere dvomestno število
            int index1 = sLine.find_first_of(",");
            stevilo2 = sLine.substr(index1 + 1, 2);
            tempZgornjaMeja = stoi(stevilo2);
        }
        else
        {
            cout << "...";
        }

        while (line_no != 6 && getline(mojaDatIn, sLine)) // branje 6 linije v datoteki
        {
            ++line_no;
        }

        if (line_no == 6)
        {
            // poišče kje v datoteki v 6 liniji je prvi "[" in od tam prebere dvomestno število
            int index2 = sLine.find_first_of("[");
            stevilo3 = sLine.substr(index2 + 1, 2);
            vlazSpodnjaMeja = stoi(stevilo3);

            // poišče kje v datoteki v 6 linije je prva "," in od tam prebere dvomestno število
            int index3 = sLine.find_first_of(",");
            stevilo4 = sLine.substr(index3 + 1, 2);
            vlazZgornjaMeja = stoi(stevilo4);
        }
        else
        {
            cout << "...";
        }
        while (line_no != 7 && getline(mojaDatIn, sLine)) // branje 7 linije v datoteki
        {
            ++line_no;
        }

        if (line_no == 7)
        {
            // poišče kje v datoteki v 7 liniji je prvi "[" in od tam prebere dvomestno število
            int index4 = sLine.find_first_of("[");
            stevilo5 = sLine.substr(index4 + 1, 2);
            osvSpodnjaMeja = stoi(stevilo5);

            // poišče kje v datoteki v 7 linije je prva "," in od tam prebere petmestno število
            int index5 = sLine.find_first_of(",");
            stevilo6 = sLine.substr(index5 + 1, 5); 
            osvZgornjaMeja = stoi(stevilo6);
        }
        else
        {
            cout << "...";
        }

        mojaDatIn.close();
    }
    else
    {
        cout << "Napaka pri branju";
    }
}

void vnesiTrenutnoTemp() // vnos trenutne temerature za testni nacin
{
    cout << "Vnesi trenutno temperaturo:\n";
    cout << "\tTemperatura[C, K in F]: \n";
    cin >> trenutnaTemp;
    enotaTrenutnaTemp();
    while ((cin.fail() || trenutnaTemp < 10) || ((trenutnaTemp > 110) && (trenutnaTemp < 283)) || (trenutnaTemp > 313))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        nepravilenVnos();
        cout << "Izberi temparaturo med 10 C in 30C, 31F in 90F ali 283 K in 303K\n";
        cout << "Temperatura: ";
        cin >> trenutnaTemp;
        enotaTrenutnaTemp();
    }
}

void ukazZaRegulacijoTemp() // ukaz za regulacijo temerature za testni nacin
{
    if ((zelenaTemp - trenutnaTemp) > 0)
    {
        // izpis za vklop grelca
        cout << "*****************************\n";
        cout << "**\t\t\t   **\n**----->VKLOP GRELCA<------**\n**\t\t\t   **\n";
        cout << "*****************************\n\n";
    }
    else if ((zelenaTemp - trenutnaTemp) < 0)
    {
        // izpis za izklop grelca
        cout << "*****************************\n";
        cout << "**\t\t\t   **\n**----->IZKLOP GRELCA<-----**\n**\t\t\t   **\n";
        cout << "*****************************\n\n";
    }
    else
    {
        // izpis za optimalno temperaturo
        cout << "*****************************\n";
        cout << "**\t\t\t   **\n**TEMPERATURA JE OPTIMALNA **\n**\t\t\t   **\n";
        cout << "*****************************\n";
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

void vnesiTrenutnoVlaznost() // vnos trenutne vlaznosti za testni nacin
{
    cout << "\nVnesi trenutno vlaznost\n";
    cout << "Vlaznost[%]:\n";
    cin >> trenutnaVlaz;
    while (cin.fail() || trenutnaVlaz < 0 || trenutnaVlaz > 100)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        nepravilenVnos();
        cout << "Vnesi stopnjo vlaznosti med 0 in 100: \n";
        cout << "Vlaznost: ";
        cin >> trenutnaVlaz;
    }
}

void ukazZaRegulacijoVlaz() // ukaz za regulacijo trenutne vlaznosti za testni nacin
{
    if ((zelenaVlaz - trenutnaVlaz) > 0)
    {
        // izpis za vklop grelca
        cout << "*****************************\n";
        cout << "**\t\t\t   **\n**---->VKLOP VLAZILCA<-----**\n**\t\t\t   **\n";
        cout << "*****************************\n\n";
    }
    else if ((zelenaVlaz - trenutnaVlaz) < 0)
    {
        // izpis za izklop grelca
        cout << "*****************************\n";
        cout << "**\t\t\t   **\n**---->IZKLOP VLAZILCA<----**\n**\t\t\t   **\n";
        cout << "*****************************\n\n";
    }
    else
    {
        // izpis za optimalno vlažnost
        cout << "*****************************\n";
        cout << "**\t\t\t   **\n**->VLAZNOST JE OPTIMALNA<-**\n**\t\t\t   **\n";
        cout << "*****************************\n";
    }
}

void vnesiTrenutnoOsv() // vnos trenutne osvetljenosti za testni nacin
{
    cout << "Vnesi trenutno osvetljenost:\n";
    cout << "\tOsvetljenost[lx]: \n";
    cin >> trenutnaOsv;

    while (cin.fail() || trenutnaOsv <= 10 || trenutnaOsv > 10000)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        nepravilenVnos();
        cout << "Vnesi moc osvetljenosti vecjo ali enako 10 in manjso od 10000 \n";
        cout << "Osvetljenost[lx]: ";
        cin >> trenutnaOsv;
    }
}

void ukazZaRegulacijoOsv() // ukaz za regulacijo trenutne vlaznosti za testni nacin
{

    if (trenutnaOsv >= 8000)
    {
        // izpis za izklop luči in zatemnitev rolet
        cout << "*****************************\n";
        cout << "**\tIZKLOP LUCI        **\n**\t     IN\t\t   **\n**    ZATEMNITEV ROLET     **\n";
        cout << "*****************************\n\n";
    }
    else if ((trenutnaOsv > 500) && (trenutnaOsv < 8000))
    {
        // izpis za izklop luči
        cout << "*****************************\n";
        cout << "**\t\t\t   **\n**------>IZKLOP LUCI<------**\n**\t\t\t   **\n";
        cout << "*****************************\n\n";
    }
    else if ((trenutnaOsv > 100) && (trenutnaOsv < 500))
    {
        // izpis za vklop luči
        cout << "*****************************\n";
        cout << "**\t\t\t   **\n**------>PRIZIG LUCI<------**\n**\t\t\t   **\n";
        cout << "*****************************\n\n";
    }
    else if ((trenutnaOsv >= 10) && (trenutnaOsv <= 100))
    {
        // izpis za prizig luci in odprtje rolet
        cout << "*****************************\n";
        cout << "**\tPRIZIG LUCI        **\n**\t     IN\t\t   **\n**     ODPRTJE ROLET       **\n";
        cout << "*****************************\n\n";
    }
    else if (trenutnaOsv == 500)
    {
        // izpis za optimalno osvetljitev
        cout << "*****************************\n";
        cout << "**\t\t\t   **\n**OSVETLJENOST JE OPTIMALNA**\n**\t\t\t   **\n";
        cout << "*****************************\n";
    }
}

void razlikaDoZeleneLastnosti() // racunanje odstopanja med zeleno in dejansko temperaturo (Avtomatski način)
{
    razlikaTemp = zelenaTemp - trenutnaTemp;
    cout << "Odstopanje do zelene temperature: " << abs(razlikaTemp); // absolutna vrednost odstopanja (želena temperatura - trenutna temperatura)
    enotaZelenaTemp();

    razlikaVlaz = zelenaVlaz - trenutnaVlaz;
    cout << "\nOdstopanje do zelene vlaznosti: " << abs(razlikaVlaz) << "[%]" << endl; // absolutna vrednost odstopanja (želena vlažnost - trenutna vlažnost)

    razlikaOsv = zelenaOsv - trenutnaOsv;
    cout << "Odstopanje do zelene osvetljenosti: " << abs(razlikaOsv) << "[lx]" // absolutna vrednost odstopanja (želena osvetljenost - trenutna osvetljenost)
         << "\n\n";
}

void avtomatskiNacin() // Avtomatski nacin
{
    srand(time(NULL)); // naključen seed

    for (int i = 0; i < 100; i++)
    {

        int intervalTemp = tempZgornjaMeja - tempSpodnjaMeja + 1;
        int intervalVlaz = vlazZgornjaMeja - vlazSpodnjaMeja + 1;
        int intervalOsv = osvZgornjaMeja - osvSpodnjaMeja + 1;

        // naključno število podano na intervalu v datoteki za:
        trenutnaTemp = rand() % intervalTemp + tempSpodnjaMeja; // temperaturo (10 do 40)
        trenutnaVlaz = rand() % intervalVlaz + vlazSpodnjaMeja; // vlažnost (30 do 60)
        trenutnaOsv = rand() % intervalOsv + osvSpodnjaMeja; // osvetljenost (10 do 10000)

        cout << "Zelena temperatura: " << zelenaTemp;
        enotaZelenaTemp();
        cout << endl;
        cout << "Zelena vlaznost: " << zelenaVlaz << endl;
        cout << "Zelena osvetljenost: " << zelenaOsv << endl;
        cout << endl;
        cout << "Trenutna temperatura: ";
        enotaTrenutnaTemp();
        cout << "Trenutna vlaznost: " << trenutnaVlaz << endl;
        cout << "Trenutna osvetljenost: " << trenutnaOsv << "\n\n";

        razlikaDoZeleneLastnosti();

        // vsak loop sešteva RAZLIKE vrednosti ambientalnih lastnosti (glej linijo 575)
        sumTemp += razlikaTemp;
        sumVlaz += razlikaVlaz;
        sumOsv += razlikaOsv;

    
        ukazZaRegulacijoTemp();
        ukazZaRegulacijoVlaz();
        ukazZaRegulacijoOsv();
        prelom();

        //  vsak loop sešteva trenutne vrednosti lastnosti 
        povpVrednostTemp += trenutnaTemp;
        povpVrednostVlaz += trenutnaVlaz;
        povpVrednostOsv += trenutnaOsv;
        // Sleep(3000); // ponovitev zanke vsake 3 sekunde (odkomentiraj, če želiš po eno simluacijo na 3 sekunde)
    }

    // seštete vrednosti deli z 100 (št. ponovitev), da dobi povprečne vrednosti lastnosti
    povpVrednostTemp = povpVrednostTemp / 100; 
    povpVrednostVlaz = povpVrednostVlaz / 100;
    povpVrednostOsv = povpVrednostOsv / 100;

    // sesštete razlike lastnosti deli z 100 (št. ponovitev), da dobi povprečne vrednosti lastnosti
    sumTemp = sumTemp / 100;
    sumVlaz = sumVlaz / 100;
    sumOsv = sumOsv / 100;


    // IZPIS
    cout << "Povprecna vrednost dejanske temperature: ";
    cout << povpVrednostTemp;
    enotaZelenaTemp();
    povpVrednostTemp = 0; // reset na 0, da se v ponovnem zagonu funkcije ne sestevajo še stare vrednosti

    cout << "\nPovprecna vrednost dejanske vlaznosti: ";
    cout << povpVrednostVlaz << "[%]" << endl;
    povpVrednostVlaz = 0;

    cout << "Povprecna vrednost dejanske osvetljenosti: ";
    cout << povpVrednostOsv << "[lx]" << endl;
    povpVrednostOsv = 0;

    cout << "\nPovprecno odstopanje od zelene temperature: ";
    cout << abs(sumTemp);
    enotaZelenaTemp();
    sumTemp = 0;

    cout << "\nPovprecno odstopanje od zelene vlaznosti: ";
    cout << abs(sumVlaz) << "[%]" << endl;
    sumVlaz = 0;

    cout << "Povprecno odstopanje od zelene osvetljenosti: ";
    cout << abs(sumOsv) << "[lx]";
    sumOsv = 0;
}

void avtomatskiNacin2() // Avtomatski nacin 2
{
    // Vnos koliko ponovitev simuliranja želi uporabnik (med 1 in 5000)
    cout << "Koliko ponovitev naj naredi simulator? " << endl; 
    cin >> stPonovitev;
    while (cin.fail() || stPonovitev < 1 || stPonovitev > 5000)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        nepravilenVnos();
        cout << "Izberi stevilo ponovetev med 1 in 5000: \n\n";
        cin >> stPonovitev;
    }

    // Vnos koliko naj bo časovni razmik med ponovitvami v milisekundah (več kot 1ms)
    cout << "Koliko naj bo casovni razmik(milisekunde) med ponovitvami? " << endl;
    cin >> casovniRazmik;
    while (cin.fail() || casovniRazmik < 1)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        nepravilenVnos();
        cout << "Izberi casovni razmik daljsi kot 1 milisekundo: \n\n";
        cin >> casovniRazmik;
    }

    srand(time(NULL)); // naključen seed (vedno drugi rezultati)

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
        cout << "Trenutna osvetljenost: " << trenutnaOsv << "\n\n";

        razlikaDoZeleneLastnosti();

        sumTemp += razlikaTemp;
        sumVlaz += razlikaVlaz;
        sumOsv += razlikaOsv;

        ukazZaRegulacijoTemp();
        ukazZaRegulacijoVlaz();
        ukazZaRegulacijoOsv();
        prelom();
        povpVrednostTemp += trenutnaTemp;
        povpVrednostVlaz += trenutnaVlaz;
        povpVrednostOsv += trenutnaOsv;
        Sleep(casovniRazmik); // ponovitev zanke vsakih x sekund
    }
    povpVrednostTemp = povpVrednostTemp / stPonovitev;
    povpVrednostVlaz = povpVrednostVlaz / stPonovitev;
    povpVrednostOsv = povpVrednostOsv / stPonovitev;
    sumTemp = sumTemp / stPonovitev;
    sumVlaz = sumVlaz / stPonovitev;
    sumOsv = sumOsv / stPonovitev;

    cout << "Povprecna vrednost dejanske temperature: ";
    cout << povpVrednostTemp;
    enotaZelenaTemp();
    povpVrednostTemp = 0; // reset na 0, da se v ponovnem zagonu funkcije ne sestevajo še stare vrednosti

    cout << "\nPovprecna vrednost dejanske vlaznosti: ";
    cout << povpVrednostVlaz << "[%]" << endl;
    povpVrednostVlaz = 0;

    cout << "Povprecna vrednost dejanske osvetljenosti: ";
    cout << povpVrednostOsv << "[lx]" << endl;
    povpVrednostOsv = 0;

    cout << "\nPovprecno odstopanje od zelene temperature: ";
    cout << abs(sumTemp);
    enotaZelenaTemp();
    sumTemp = 0;

    cout << "\nPovprecno odstopanje od zelene vlaznosti: ";
    cout << abs(sumVlaz) << "[%]" << endl;
    sumVlaz = 0;

    cout << "Povprecno odstopanje od zelene osvetljenosti: ";
    cout << abs(sumOsv) << "[lx]";
    sumOsv = 0;
}

void avtomatskiTestniNacin() // Avtomatski testni nacin
{
    cout << "Izberi seed za ponovljivost simulacij: " << endl;
    cin >> seedTestni;
    while (cin.fail() || seedTestni < 1)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        nepravilenVnos();
        cout << "Izberi seed vecji kot 1: \n";
        cin >> seed;
    }
    srand(seed); // generiral bo vedno iste ambientalne lastnosti za izbran seed (npr. vedno isti rezultati za seed 1, seed 2, seed 3 itd.)

    cout << "Koliko ponovitev naj naredi simulator? " << endl;
    cin >> stPonovitevTestni;
    while (cin.fail() || stPonovitevTestni < 1 || stPonovitevTestni > 5000)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        nepravilenVnos();
        cout << "Izberi stevilo ponovetev med 1 in 5000: \n\n";
        cin >> stPonovitevTestni;
    }
    cout << "Koliko naj bo casovni razmik(milisekunde) med ponovitvami? " << endl;
    cin >> casovniRazmikTestni;
    while (cin.fail() || casovniRazmikTestni < 1)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        nepravilenVnos();
        cout << "Izberi casovni razmik daljsi kot 1 milisekundo: \n\n";
        cin >> casovniRazmikTestni;
    }

    for (int i = 0; i < stPonovitevTestni; i++)
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
        cout << "Trenutna osvetljenost: " << trenutnaOsv << "\n\n";

        razlikaDoZeleneLastnosti();

        sumTemp += razlikaTemp;
        sumVlaz += razlikaVlaz;
        sumOsv += razlikaOsv;

        ukazZaRegulacijoTemp();
        ukazZaRegulacijoVlaz();
        ukazZaRegulacijoOsv();
        prelom();
        povpVrednostTemp += trenutnaTemp;
        povpVrednostVlaz += trenutnaVlaz;
        povpVrednostOsv += trenutnaOsv;
        Sleep(casovniRazmikTestni); // ponovitev zanke vsake 3 sekunde
    }
    povpVrednostTemp = povpVrednostTemp / stPonovitevTestni;
    povpVrednostVlaz = povpVrednostVlaz / stPonovitevTestni;
    povpVrednostOsv = povpVrednostOsv / stPonovitevTestni;
    sumTemp = sumTemp / stPonovitevTestni;
    sumVlaz = sumVlaz / stPonovitevTestni;
    sumOsv = sumOsv / stPonovitevTestni;

    cout << "Povprecna vrednost dejanske temperature: ";
    cout << povpVrednostTemp;
    enotaZelenaTemp();
    povpVrednostTemp = 0; // reset na 0, da se v ponovnem zagonu funkcije ne sestevajo še stare vrednosti

    cout << "\nPovprecna vrednost dejanske vlaznosti: ";
    cout << povpVrednostVlaz << "[%]" << endl;
    povpVrednostVlaz = 0;

    cout << "Povprecna vrednost dejanske osvetljenosti: ";
    cout << povpVrednostOsv << "[lx]" << endl;
    povpVrednostOsv = 0;

    cout << "\nPovprecno odstopanje od zelene temperature: ";
    cout << abs(sumTemp);
    enotaZelenaTemp();
    sumTemp = 0;

    cout << "\nPovprecno odstopanje od zelene vlaznosti: ";
    cout << abs(sumVlaz) << "[%]" << endl;
    sumVlaz = 0;

    cout << "Povprecno odstopanje od zelene osvetljenosti: ";
    cout << abs(sumOsv) << "[lx]";
    sumOsv = 0;
}

void datotekaPomoc()
{ // branje iz datoteke Pomoc
    prelom();
    prelom();
    string line;
    ifstream pomoc("Pomoc.txt");

    if (pomoc.is_open())
    {
        while (getline(pomoc, line))
        {
            cout << line << "\n";
        }
        pomoc.close();
    }
    else
        cout << "Napaka pri odpiranju datoteke 'Pomoc'";
}

int main(int argc, char *argv[]) // MAIN
{
    cout << "Regulator, verzija 2.0\n";
    prelom();
    // Vnos imena datoteke (manj kot 16 znakov)
    cout << "Vnesite ime datoteke v katero bodo shranjene lastnosti: \n";
    cin >> imeDat;
    while (cin.fail() || imeDat.size() < 1 || imeDat.size() > 16)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        nepravilenVnos();
        cout << "Ime datoteke je lahko dolgo med 1 in 16 znaki: \n";
        cout << "Vnesite ime datoteke: \n";
        cin >> imeDat;
    }
    imeDat += ".txt";

    vnesiZeleneLastnosti();
    prelom();
    datoteka();
    prelom();

    // če je program klican z enim argumentom (tistim, ki je bil compilan), potem se odpre standardni način
    if (argc == 1)
    {

        while (dela)
        {
            glavniMeni();
            cin >> izbiraNacina;

            while (cin.fail() || izbiraNacina != 0 && izbiraNacina != 1 && izbiraNacina != 2 && izbiraNacina != 3 && izbiraNacina != 4)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                nepravilenVnos();
                glavniMeni();
                cin >> izbiraNacina;
            }
            // Ročni način
            if (izbiraNacina == 1)
            {
                vnesiTrenutneLastnosti();
                prelom();
                razlikaDoZeleneLastnosti();
                ukazZaRegulacijoTemp();
                ukazZaRegulacijoVlaz();
                ukazZaRegulacijoOsv();
                trenutnaTemp == 0;
                trenutnaVlaz == 0;
                trenutnaOsv == 0;
            }
            // Avtomatski način
            else if (izbiraNacina == 2)
            {
                avtomatskiNacin();
            }
            // Avtomatski način 2
            else if (izbiraNacina == 3)
            {
                avtomatskiNacin2();
            }
            // Pomoč
            else if (izbiraNacina == 4)
            {
                datotekaPomoc();
            }
            // Izhod
            else if (izbiraNacina == 0)
            {
                return 0;
            }
            prekinitevSimulacije();
        }

        return 0;
    }

    else if ((argc == 2) && (strcmp(argv[1], "-t") == 0)) // če je klican z dvema argumentoma in je drugi argument -t (npr. regulator -t), potem se zažene testni nacin
    {
        cout << "\t\nPOZDRAVLJEN/A V TESTNEM NACINU\n";
        while (dela)
        {
            // Glavni meni
            glavniMeniTestniNacin();
            cin >> izbiraNacinaTestni;

            while (cin.fail() || izbiraNacinaTestni != 1 && izbiraNacinaTestni != 2)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                nepravilenVnos();
                glavniMeniTestniNacin();
                cin >> izbiraNacinaTestni;
            }
            // Testni ročni način
            if (izbiraNacinaTestni == 1)
            {
                meniTestniRocni();
                cin >> izbiraTestniRocni;
                while (cin.fail() || izbiraTestniRocni != 1 && izbiraTestniRocni != 2 && izbiraTestniRocni != 3)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    nepravilenVnos();
                    meniTestniRocni();
                    cin >> izbiraTestniRocni;
                }
                // Testiranje temperature
                if (izbiraTestniRocni == 1)
                {
                    vnesiTrenutnoTemp();
                    ukazZaRegulacijoTemp();
                    trenutnaTemp = 0;
                }
                // Testiranje vlažnosti
                else if (izbiraTestniRocni == 2)
                {
                    vnesiTrenutnoVlaznost();
                    ukazZaRegulacijoVlaz();
                    trenutnaVlaz = 0;
                }
                // Testiranje osvetljenosti
                else if (izbiraTestniRocni == 3)
                {
                    vnesiTrenutnoOsv();
                    ukazZaRegulacijoOsv();
                    trenutnaOsv = 0;
                }
                prekinitevSimulacije();
            }
            // Testiranje avtomatskega načina
            else if (izbiraNacinaTestni == 2)
            {
                avtomatskiTestniNacin();
                prekinitevSimulacije();
            }
        }
        return 0;
    }
    else
    {
        cout << "...";
        return 0;
    }
}