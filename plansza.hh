#ifndef PLANSZA_HH
#define PLANSZA_HH
#include "Si.hh"

using namespace std;

class Plansza
{
    private:
    char **POLE;
    int ILE_WYGRYWA = 3;
    int ROZM = 0;

    public:
    Plansza (int rozmiar, int ilosc_wygrywajacych);
    char* operator [] (int i);
    void rysuj ();
    bool ruch (char XO, int wiersz, int kolumna);
    void gra (Si & komputer, bool kontraSi);
    bool czy_remis ();
    // bool czy_wygrana (char XO, int wiersz, int kolumna);
    char sprawdz_czy_wygrana ();
    // int minmax (int wiersz, int kolumna, bool czySI, int ilosc_rekurencji);
    int minmax (bool czySI, int ilosc_rekurencji, int alpha, int beta);
    void najlepszy_ruch (Si & komputer, int alpha, int beta);
};

#endif