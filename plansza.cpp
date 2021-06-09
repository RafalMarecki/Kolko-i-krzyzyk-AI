#include "plansza.hh"
#include <iostream>
#include <cstdio>
#include <conio.h>

using namespace std;

Plansza::Plansza (int rozmiar, int ilosc_wygrywajacych)
{
    this->ROZM = rozmiar;
    this->ILE_WYGRYWA = ilosc_wygrywajacych;
    this->POLE = new char *[ROZM];
    for (int i=0; i<ROZM; i++)
        this->POLE[i] = new char [ROZM];
    
    for (int w=0; w<ROZM; w++)
    {
        for (int k=0; k<ROZM; k++)
        {
            this->POLE[w][k] = ' ';
        }
    }
}

char* Plansza::operator [] (int i) 
{
  return this->POLE[i];
}

void Plansza::rysuj ()
{
    for (int w=0; w<this->ROZM; w++)
    {
        cout << " ";
        for (int k=0; k<this->ROZM; k++)
        {
            cout << std::noskipws << this->POLE[w][k]; 
            if (k != this->ROZM -1)
                cout << " | ";
        }
        cout << endl;

        if (w < this->ROZM-1)
        {
            for (int k=0; k < this->ROZM; k++)
            {
                if (k != this->ROZM -1)
                    cout << "---|";
                else
                    cout << "---" << endl;
            }
        }
    }
}

bool Plansza::ruch (char XO, int wiersz, int kolumna)
{
    if (this->POLE[wiersz-1][kolumna-1] != 'X' && this->POLE[wiersz-1][kolumna-1] != 'O')
    {
        this->POLE [wiersz-1][kolumna-1] = XO;
        return true;
    }
    else
    {
        cout << "BLAD! POLE JEST ZAJETE, SPROBUJ JESZCZE RAZ!" << endl;
        return false;
    }
}

bool Plansza::czy_remis ()
{
    for (int w=0; w<this->ROZM; w++)
    {
        for (int k=0; k<this->ROZM; k++)
        {
            if (this->POLE[w][k]==' ')
                return false;
        }
    }
    return true;
}

char Plansza::sprawdz_czy_wygrana()
{
    int licznikX=0, licznikO=0; // Liczniki X i O
    int iteracje1=0, iteracje2=0; bool koniec=false; // Zmienne pomocnicze do sprawdzania skosów
    for (int w=0; w<this->ROZM; w++) // (---) Sprawdza wiersze 
    {
        for (int k=0; k<this->ROZM; k++)
        {
            if (this->POLE[w][k]=='X')
            {
                licznikO = 0;
                licznikX++;
                if (licznikX >= this->ILE_WYGRYWA)
                    return 'X';
            }
            else if (this->POLE[w][k]=='O')
            {
                licznikX = 0;
                licznikO++;
                if (licznikO >= this->ILE_WYGRYWA)
                    return 'O';
            }
            else if (this->POLE[w][k]==' ')
            {
                licznikO=0;
                licznikX=0;
            }
        }
        licznikO=0; licznikX=0; // Reset liczników
    } 

    for (int k=0; k<this->ROZM; k++) // ( | ) Sprawdza kolumny
    {
        for (int w=0; w<this->ROZM; w++)
        {
            if (this->POLE[w][k]=='X')
            {
                licznikO = 0;
                licznikX++;
                if (licznikX >= this->ILE_WYGRYWA)
                    return 'X';
            }
            else if (this->POLE[w][k]=='O')
            {
                licznikX = 0;
                licznikO++;
                if (licznikO >= this->ILE_WYGRYWA)
                    return 'O';
            }
            else if (this->POLE[w][k]==' ')
            {
                licznikO=0;
                licznikX=0;
            }
        }
        licznikO=0; licznikX=0; // Reset liczników
    } 

    while (koniec == false) // Pętla sprawdzania (\)
    {
        if (this->ROZM - this->ILE_WYGRYWA - iteracje1 >= 0) // (\) Tutaj sprawdzam prawy górny róg planszy, wraz ze środkową przekątną (lecę od góry)
        {
            for (int k=this->ROZM - this->ILE_WYGRYWA - iteracje1, w=0; k<this->ROZM && w<this->ROZM; k++, w++)
            {
                if (this->POLE[w][k]=='X')
                {
                    licznikO = 0;
                    licznikX++;
                    if (licznikX >= this->ILE_WYGRYWA)
                        return 'X';
                }
                else if (this->POLE[w][k]=='O')
                {
                    licznikX = 0;
                    licznikO++;
                    if (licznikO >= this->ILE_WYGRYWA)
                        return 'O';
                }
                else if (this->POLE[w][k]==' ')
                {
                    licznikO=0;
                    licznikX=0;
                }   
            }
            licznikO=0; licznikX=0; // Reset liczników
            iteracje1++; // Przechodzi na kolumnę mniejszą o 1
        }
        else
        {
            if (this->ROZM - this->ILE_WYGRYWA - iteracje2 > 0) // (\) Tutaj sprawdzam lewy dolny róg bez środkowej przekątnej (lecę od dołu) 
            {
               for (int w=this->ROZM - this->ILE_WYGRYWA - iteracje2, k=0; k<this->ROZM && w<this->ROZM; k++, w++)
                {
                    if (this->POLE[w][k]=='X')
                    {
                        licznikO = 0;
                        licznikX++;
                        if (licznikX >= this->ILE_WYGRYWA)
                            return 'X';
                    }
                    else if (this->POLE[w][k]=='O')
                    {
                        licznikX = 0;
                        licznikO++;
                        if (licznikO >= this->ILE_WYGRYWA)
                            return 'O';
                    }
                    else if (this->POLE[w][k]==' ')
                    {
                        licznikO=0;
                        licznikX=0;
                    }   
                }
                licznikO=0; licznikX=0; // Reset liczników
                iteracje2++; // Przechodzi na wiersz mniejszy o 1
            }
            else
                koniec = true;
        }
    } 
    iteracje1=0; iteracje2=0; koniec = false; 
    
    while (koniec == false) // Pętla sprawdzania (/)
    {
        if (this->ILE_WYGRYWA - 1 + iteracje1 < this->ROZM) // (/) Tutaj sprawdzam lewy górny róg planszy, wraz ze środkową przekątną (lecę od góry) 
        {
            for (int k=this->ILE_WYGRYWA - 1 + iteracje1, w=0; k>=0 && w<this->ROZM; k--, w++)
            {
                if (this->POLE[w][k]=='X')
                {
                    licznikO = 0;
                    licznikX++;
                    if (licznikX >= this->ILE_WYGRYWA)
                        return 'X';
                }
                else if (this->POLE[w][k]=='O')
                {
                    licznikX = 0;
                    licznikO++;
                    if (licznikO >= this->ILE_WYGRYWA)
                        return 'O';
                }
                else if (this->POLE[w][k]==' ')
                {
                    licznikO=0;
                    licznikX=0;
                }   
            } 
            licznikO=0; licznikX=0; // Reset liczników
            iteracje1++;
        }
        else
        {
            if (this->ROZM - this->ILE_WYGRYWA - iteracje2 > 0) // (/)Tutaj sprawdzam prawy dolny róg bez środkowej przekątnej (lecę od dołu) 
            {
               for (int w=this->ROZM - this->ILE_WYGRYWA - iteracje2, k=this->ROZM-1; k>=0 && w<this->ROZM; k--, w++)
                {
                    if (this->POLE[w][k]=='X')
                    {
                        licznikO = 0;
                        licznikX++;
                        if (licznikX >= this->ILE_WYGRYWA)
                            return 'X';
                    }
                    else if (this->POLE[w][k]=='O')
                    {
                        licznikX = 0;
                        licznikO++;
                        if (licznikO >= this->ILE_WYGRYWA)
                            return 'O';
                    }
                    else if (this->POLE[w][k]==' ')
                    {
                        licznikO=0;
                        licznikX=0;
                    }   
                }
                licznikO=0; licznikX=0; // Reset liczników
                iteracje2++; 
            }
            else
                koniec = true;
        }
    } 
    
    return ' '; // Jeśli w żadną stronę nie ma wygranej, to zwraca puste pole (BRAK WYGRANEJ)
}

int Plansza::minmax (bool kolejSI, int ilosc_rekurencji, int alpha, int beta)
{
    int score, licznik = 0;
    char XO;
    // Sprawdzam czy wygrana
    char wygrany = this->sprawdz_czy_wygrana();

    if (kolejSI==true) // KOLEJNOSC (zaczyna SI)
        XO = 'O'; // Si to O MAXYMIZER
    else    
        XO = 'X'; // Gracz to X MINIMIZER

    // Zwraca wartosc ujemną gdy gracz, a dodatnią gdy Si
    if (wygrany == 'X' || wygrany == 'O') 
    {
        if (wygrany == 'O')
            return (100 - ilosc_rekurencji);
        else if (wygrany == 'X')
            return (-100 + ilosc_rekurencji);  
    }

    // Zwraca 0 gry remis
    if (this->czy_remis() == true) 
        return 0;

    if (kolejSI == true) // Maxymizer
    {
        int najlepszy_score = -INT16_MAX;
        for (int w=0; w<this->ROZM; w++)
        {
            for (int k=0; k<this->ROZM; k++)
            {
                if (this->POLE[w][k] == ' ')
                {
                    this->POLE[w][k] = XO;
                    najlepszy_score = max (this->minmax(false, ilosc_rekurencji + 1, alpha, beta), najlepszy_score); 
                    this->POLE[w][k] = ' ';
                    // Alpha-Beta pruning
                    alpha = max (najlepszy_score, alpha);
                    if (alpha >= beta)
                        return najlepszy_score;
                }
            }
        }
        return najlepszy_score;
    }
    else // Minimizer
    {
        int najlepszy_score = INT16_MAX;
        for (int w=0; w<this->ROZM; w++)
        {
            for (int k=0; k<this->ROZM; k++)
            {
                if (this->POLE[w][k] == ' ')
                {
                    this->POLE[w][k] = XO;
                    najlepszy_score = min (this->minmax(true, ilosc_rekurencji + 1, alpha, beta), najlepszy_score); 
                    this->POLE[w][k] = ' ';
                    // Alpha-Beta pruning
                    beta = min (najlepszy_score, beta);
                    if (alpha >= beta)
                        return najlepszy_score;
                }
            }
        }
        return najlepszy_score;
    }
}

void Plansza::najlepszy_ruch (Si & komputer, int alpha, int beta)
{
    int najlepszy_score = -INT16_MAX; 
    int wiersz = 0, kolumna = 0;
    for (int w=0; w<this->ROZM; w++)
    {
        for (int k=0; k<this->ROZM; k++)
        {
            if (this->POLE[w][k] == ' ')
            {
                this->POLE[w][k] = 'O';  // Zczyna ai, czyli Max
                int score = this->minmax(false, 0, alpha, beta); // Teraz wchodzimy do minmax i sprawdzamy ruch Min
                this->POLE[w][k] = ' ';
                if (score > najlepszy_score)
                {
                    najlepszy_score = score;
                    wiersz = w;
                    kolumna = k;
                }
            }
        }
    }
    komputer.set_pozycja(wiersz, kolumna);
}

void Plansza::gra (Si & komputer, bool kontraSi)
{
    char XO = 'O'; // Zaczyna O
    bool dobry_ruch = true, remis = false, kolejSi;
    int wiersz, kolumna, pomoc = 0, ilosc_rekurencji = 0, alpha = -INT16_MAX, beta =INT16_MAX;
    char wygrana = ' ';

    if (kontraSi == false) // GRACZ VS GRACZ =============================================================================
    {
        while (wygrana == ' ' && remis == false) // Petla gry
        {
            this->rysuj(); // Rysowanie planszy

            do
            {
                cout << "Kolej: " << XO <<endl; 
                cout << "Podaj nr. wiersza i kolumny:\n";
                cout << "Wiersz: "; cin >> wiersz; // Wpisywanie wiersza
                while (wiersz > this->ROZM)
                {
                    cout << "Blad! Wiersz musi byc mniejszy niz " << this->ROZM+1 <<".\nPodaj nr. wiersza: "; cin >> wiersz;
                }
                cout << "Kolumna: "; cin >> kolumna; // Wpisywanie kolumny
                while (kolumna > this->ROZM)
                {
                    cout << "Kolumna musi byc mniejsza niz " << this->ROZM+1 <<".\nPodaj nr. kolumny: "; cin >> wiersz;
                }
                dobry_ruch = this->ruch(XO, wiersz, kolumna);
            } while (dobry_ruch == false);

            system("cls");                      // Czyszczenie ekranu
            wygrana = this->sprawdz_czy_wygrana();          // Sprawdzam czy wygrana
            remis = this->czy_remis();          // Sprawdzam czy remis

            if (wygrana == ' ' && remis == false)         // Jeśli nie ma wygranej, ani remisu to zmiana gracza
            {
                if (XO == 'X') 
                    XO = 'O';
                else
                if (XO == 'O')
                    XO = 'X';
            }
            else
            {   
                if (wygrana == 'X') // Jeśli wygrana X
                {
                    this->rysuj();
                    cout << "Koniec gry, wygral gracz: X" << endl;
                }
                else if (wygrana == 'O') // Jeśli wygrana O
                {
                    this->rysuj();
                    cout << "Koniec gry, wygral gracz: O" << endl;
                }
                else if (remis == true) // Jeśli remis
                {
                    this->rysuj();
                    cout << "Koniec gry, REMIS!" << endl;
                }
            }
        }
    }
    else if (kontraSi == true) // GRACZ VS Si ===============================================================================
    {
        kolejSi = true; // Zaczyna komputer "O"

        while (wygrana == ' ' && remis == false) // Pętla gry
        {
            this->rysuj(); // Rysowanie planszy

            if (kolejSi==true)
                XO = 'O';
            else    
                XO = 'X';

            if (kolejSi == false) // KOLEJ GRACZA 
            {
                do
                {
                    cout << "Kolej: " << XO <<endl; 
                    cout << "Podaj nr. wiersza i kolumny:\n";
                    cout << "Wiersz: "; cin >> wiersz; // Wpisywanie wiersza
                    while (wiersz > this->ROZM)
                    {
                        cout << "Blad! Wiersz musi byc mniejszy niz " << this->ROZM+1 <<".\nPodaj nr. wiersza: "; cin >> wiersz;
                    }
                    cout << "Kolumna: "; cin >> kolumna; // Wpisywanie kolumny
                    while (kolumna > this->ROZM)
                    {
                        cout << "Kolumna musi byc mniejsza niz " << this->ROZM+1 <<".\nPodaj nr. kolumny: "; cin >> wiersz;
                    }
                    dobry_ruch = this->ruch(XO, wiersz, kolumna);
                } while (dobry_ruch == false);

                // system("cls"); // Czyszczenie ekranu
                wygrana = this->sprawdz_czy_wygrana (); // Sprawdzam czy wygrana
                remis = this->czy_remis(); // Sprawdzam czy remis
 
                if (wygrana == 'X') // Jeśli wygrana X
                {
                    this->rysuj();
                    cout << "Koniec gry, wygral gracz: X" <<  endl;
                }
                else if (wygrana == 'O') // Jeśli wygrana O
                {
                    this->rysuj();
                    cout << "Koniec gry, wygral gracz: O" <<  endl;
                }
                else if (remis == true) // Jeśli remis
                {
                    this->rysuj();
                    cout << "Koniec gry, REMIS!" << endl;
                }

                kolejSi = true; // Zmiana gracza
            }

            else // KOLEJ KOMPUTERA 
            {
                this->najlepszy_ruch(komputer, alpha, beta);
                wiersz = komputer.get_wiersz()+1; kolumna = komputer.get_kolumna()+1;
                this->ruch(XO, wiersz, kolumna);

                // system("cls"); // Czyszczenie ekranu
                wygrana = this->sprawdz_czy_wygrana (); // Sprawdzam czy wygrana
                remis = this->czy_remis(); // Sprawdzam czy remis
 
                if (wygrana == 'X') // Jeśli wygrana X
                {
                    this->rysuj();
                    cout << "Koniec gry, wygral gracz: X" <<  endl;
                }
                else if (wygrana == 'O') // Jeśli wygrana O
                {
                    this->rysuj();
                    cout << "Koniec gry, wygral gracz: O" <<  endl;
                }
                else if (remis == true) // Jeśli remis
                {
                    this->rysuj();
                    cout << "Koniec gry, REMIS!" << endl;
                }

                kolejSi = false; // Zmiana gracza
            }
        }
    }
}
