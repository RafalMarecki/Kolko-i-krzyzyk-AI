#include "plansza.hh"
#include <iostream>
#include <stdio.h>

using namespace std;

/*|======================================================================================================|*/
/*|                KOMPILACJA KOMENDĄ: g++ plansza.hh plansza.cpp Si.hh Si.cpp main.cpp                  |*/
/*|======================================================================================================|*/


int main ()
{
    int rozmiar=0, ilosc_wygrywajacych=0, pomoc=0;
    Si komputer;
    bool kontraSi;
    cout<<"============================= Witam w kolko i krzyzyk! =============================\n Wiersze numerujemy od lewa do prawa, kolumny zas od gory do dolu, zaczynajac od 1.\n Zarowno minimalny rozmiar planszy, jak i minimalna ilosc wygrywajacych pol to 2.\n";
    do // Wpisywanie rozmiaru planszy
    {
        cout<<"\n Wpisz rozmiar planszy: "; cin>>rozmiar;
        if (rozmiar < 2)
            cout<<"\n Blad! Minimalny rozmiar planszy to 2!\n";
    } while (rozmiar < 2);

    do // Wpisywanie ilosci wygrywajacych pol
    {
        cout<<" Wpisz ilosc wygrywajacych pol: "; cin>>ilosc_wygrywajacych;
        if (ilosc_wygrywajacych < 2)
            cout<<"\n Blad! Minimalna ilosc pol wygrywajacych to 3!\n";
    } while (ilosc_wygrywajacych < 2);

    do // 1 - kontra Si; 2 - kontra gracz  
    {
        cout<<" Wpisz 1, aby grac kontra Si, lub 2 aby zagrac ze znajomym: "; cin>>pomoc;
        if (pomoc != 1 && pomoc != 2)
            cout<<"\n Blad! Wpisz 1 lub 2.\n";
        else
        {
            if (pomoc==1)
                kontraSi = true;
            if (pomoc==2)
                kontraSi = false;
        }
    } while (pomoc != 1 && pomoc != 2);

    Plansza PXO (rozmiar, ilosc_wygrywajacych);
    PXO.gra (komputer, kontraSi);
    cout << "\n Kliknij dowolny klawisz na klawiaturze, aby zamknac...\n";
    getchar();
}