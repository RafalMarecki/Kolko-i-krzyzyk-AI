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
    int licznikX=0, licznikO=0;
    for (int w=0; w<this->ROZM; w++) // Sprawdza wiersze
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
        licznikO=0; licznikX=0;
    }  licznikO=0; licznikX=0; // Reset liczników

    for (int k=0; k<this->ROZM; k++) // Sprawdza kolumny
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
        licznikO=0; licznikX=0;
    } licznikO=0; licznikX=0; // Reset liczników

    for (int skos=0; skos<this->ROZM; skos++) // Sprawdza na ukos (\)
    {
        if (this->POLE[skos][skos]=='X')
        {
            licznikO = 0;
            licznikX++;
            if (licznikX >= this->ILE_WYGRYWA)
                return 'X';
       }
        else if (this->POLE[skos][skos]=='O')
        {
            licznikX = 0;
            licznikO++;
            if (licznikO >= this->ILE_WYGRYWA)
                return 'O';
        }
        else if (this->POLE[skos][skos]==' ')
        {
            licznikO=0;
            licznikX=0;
        }   
    } licznikO=0; licznikX=0; // Reset liczników

    for (int k=this->ROZM-1, w=0; k>=0 && w<this->ROZM; k--, w++) // Sprawdza na ukos (/)
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
    } licznikO=0; licznikX=0; // Reset liczników

    // int iteracje1=0, iteracje2=0; bool koniec=false; 
    // while (koniec == false) // Pętla sprawdzania (\)
    // {
    //     if (this->ROZM - this->ILE_WYGRYWA - iteracje1 >= 0) // (\) Tutaj sprawdzam prawy górny róg planszy, wraz ze środkową przekątną (lecę od góry)
    //     {
    //         for (int k=this->ROZM - this->ILE_WYGRYWA - iteracje1, w=0; k<this->ROZM && w<this->ROZM; k++, w++)
    //         {
    //             if (this->POLE[w][k]=='X')
    //             {
    //                 licznikO = 0;
    //                 licznikX++;
    //                 if (licznikX >= this->ILE_WYGRYWA)
    //                     return 'X';
    //             }
    //             else if (this->POLE[w][k]=='O')
    //             {
    //                 licznikX = 0;
    //                 licznikO++;
    //                 if (licznikO >= this->ILE_WYGRYWA)
    //                     return 'O';
    //             }
    //             else if (this->POLE[w][k]==' ')
    //             {
    //                 licznikO=0;
    //                 licznikX=0;
    //             }   
    //         }
    //         licznikO=0; licznikX=0;
    //         iteracje1++;
    //     }
    //     else
    //     {
    //         if (this->ROZM - this->ILE_WYGRYWA - iteracje2 > 0) // (\) Tutaj sprawdzam lewy dolny róg bez środkowej przekątnej (lecę od dołu)
    //         {
    //            for (int w=this->ROZM - this->ILE_WYGRYWA - iteracje2, k=0; k<this->ROZM && w<this->ROZM; k++, w++)
    //             {
    //                 if (this->POLE[w][k]=='X')
    //                 {
    //                     licznikO = 0;
    //                     licznikX++;
    //                     if (licznikX >= this->ILE_WYGRYWA)
    //                         return 'X';
    //                 }
    //                 else if (this->POLE[w][k]=='O')
    //                 {
    //                     licznikX = 0;
    //                     licznikO++;
    //                     if (licznikO >= this->ILE_WYGRYWA)
    //                         return 'O';
    //                 }
    //                 else if (this->POLE[w][k]==' ')
    //                 {
    //                     licznikO=0;
    //                     licznikX=0;
    //                 }   
    //             }
    //             licznikO=0; licznikX=0;
    //             iteracje2++; 
    //         }
    //         else
    //             koniec = true;
    //     }
    // } licznikO=0; licznikX=0; // Reset liczników
    // iteracje1=0; iteracje2=0; koniec = false; 
    
    // while (koniec == false) // Pętla sprawdzania (/)
    // {
    //     if (this->ROZM - (this->ROZM - this->ILE_WYGRYWA + 1) + iteracje1 <= this->ROZM-1) // (/) Tutaj sprawdzam lewy górny róg planszy, wraz ze środkową przekątną (lecę od góry)
    //     {
    //         for (int k=this->ROZM - (this->ROZM - this->ILE_WYGRYWA + 1) + iteracje1, w=0; k>=0 && w<this->ROZM; k--, w++)
    //         {
    //             if (this->POLE[w][k]=='X')
    //             {
    //                 licznikO = 0;
    //                 licznikX++;
    //                 if (licznikX >= this->ILE_WYGRYWA)
    //                     return 'X';
    //             }
    //             else if (this->POLE[w][k]=='O')
    //             {
    //                 licznikX = 0;
    //                 licznikO++;
    //                 if (licznikO >= this->ILE_WYGRYWA)
    //                     return 'O';
    //             }
    //             else if (this->POLE[w][k]==' ')
    //             {
    //                 licznikO=0;
    //                 licznikX=0;
    //             }   
    //         } 
    //         licznikO=0; licznikX=0;  
    //         iteracje1++;
    //     }
    //     else
    //     {
    //         if (this->ROZM - this->ILE_WYGRYWA - iteracje2 > 0) // (/)Tutaj sprawdzam prawy dolny róg bez środkowej przekątnej (lecę od dołu)
    //         {
    //            for (int w=this->ROZM - this->ILE_WYGRYWA - iteracje2, k=this->ROZM-1; k<=0 && w<this->ROZM; k--, w++)
    //             {
    //                 if (this->POLE[w][k]=='X')
    //                 {
    //                     licznikO = 0;
    //                     licznikX++;
    //                     if (licznikX >= this->ILE_WYGRYWA)
    //                         return 'X';
    //                 }
    //                 else if (this->POLE[w][k]=='O')
    //                 {
    //                     licznikX = 0;
    //                     licznikO++;
    //                     if (licznikO >= this->ILE_WYGRYWA)
    //                         return 'O';
    //                 }
    //                 else if (this->POLE[w][k]==' ')
    //                 {
    //                     licznikO=0;
    //                     licznikX=0;
    //                 }   
    //             }
    //             licznikO=0; licznikX=0;
    //             iteracje2++; 
    //         }
    //         else
    //             koniec = true;
    //     }
    // }

    return ' ';
}

int Plansza::minmax (/*int wiersz, int kolumna, */bool kolejSI, int ilosc_rekurencji)
{
    int score, licznik = 0;

    // Sprawdzam czy wygrana
    char XO, wygrany = this->sprawdz_czy_wygrana();

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
                    najlepszy_score = max (this->minmax(false, ilosc_rekurencji + 1), najlepszy_score); 
                    this->POLE[w][k] = ' ';
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
                    najlepszy_score = min (this->minmax(true, ilosc_rekurencji + 1), najlepszy_score); 
                    this->POLE[w][k] = ' ';
                }
            }
        }
        return najlepszy_score;
    }
}

void Plansza::najlepszy_ruch (Si & komputer)
{
    int najlepszy_score = -INT16_MAX; 
    int wiersz = 0, kolumna = 0;
    for (int w=0; w<this->ROZM; w++)
    {
        for (int k=0; k<this->ROZM; k++)
        {
            if (this->POLE[w][k] == ' ')
            {
                this->POLE[w][k] = 'O';  // zaczyna ai   
                int score = this->minmax(false, 0); // chyba false albo kurwa true???
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
    int wiersz, kolumna, pomoc = 0, ilosc_rekurencji = 0;
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
                this->najlepszy_ruch(komputer);
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

// bool Plansza::czy_wygrana (char XO, int wiersz, int kolumna)
// {
//     // Zmienne pomocnicze
//     int licznik = 0;
//     bool jeden_koniec = false, dwa_koniec = false;
//     // Sprawdzamy w prawo i w lewo po wierszu (---)
//     for (int kl=kolumna-2, kp=kolumna; jeden_koniec==false || dwa_koniec==false; kl--, kp++) 
//     {
//         if (kl < 0)                                      // Z lewej strony koniec planszy
//             jeden_koniec=true;
//         else
//         {
//             if (this->POLE[wiersz-1][kl]==XO)            // Z lewej strony jest pożądany znak X/O
//                 licznik++;
//             else                                         // Z lewej strony nie ma już pożądanego znaku
//                 jeden_koniec=true; 
//         }

//         if (kp >= this->ROZM)                            // Z prawej strony koniec planszy
//             dwa_koniec=true;
//         else
//         {
//             if (this->POLE[wiersz-1][kp]==XO)            // Z prawej strony jest pożądany znak X/O
//                 licznik++; 
//             else                                         // Z prawej strony nie ma pożądenego znaku
//                 dwa_koniec=true; 
//         }
//         if (licznik == this->ILE_WYGRYWA-1)              // CZY WYGRANA?!
//             return true;
//     }  
//     licznik = 0; jeden_koniec=false; dwa_koniec=false;   // Wracanie do stanu początkowego zmiennych pomocniczych

//     // Sprawdzamy w górę i w dół po kolumnie (|)
//     for (int wg=wiersz-2, wd=wiersz; jeden_koniec==false || dwa_koniec==false; wg--, wd++) 
//     {                                     
//         if (wg < 0)                                      // Z górnej strony koniec planszy
//             jeden_koniec=true;
//         else
//         {
//             if (this->POLE[wg][kolumna-1]==XO)           // Z górnej strony jest pożądany znak X/O
//                 licznik++;
//             else                                         // Z górnej strony nie ma już pożądanego znaku
//                 jeden_koniec=true; 
//         }

//         if (wd >= this->ROZM)                            // Z dolnej strony koniec planszy
//             dwa_koniec=true;
//         else
//         {
//             if (this->POLE[wd][kolumna-1]==XO)           // Z dolnej strony jest pożądany znak X/O
//                 licznik++;
//             else                                         // Z dolnej strony nie ma pożądenego znaku
//                 dwa_koniec=true; 
//         }
//         if (licznik == this->ILE_WYGRYWA-1)              // CZY WYGRANA?!
//             return true;
//     }  
//     licznik = 0; jeden_koniec=false; dwa_koniec=false;   // Wracanie do stanu początkowego zmiennych pomocniczych

//     // Sprawdzamy lewy górny i prawy dolny na ukos (\) 
//     for (int lew_gor_w=wiersz-2, lew_gor_k=kolumna-2, pr_dol_w=wiersz, pr_dol_k=kolumna; jeden_koniec==false || dwa_koniec==false; lew_gor_k--, lew_gor_w--, pr_dol_w++, pr_dol_k++) 
//     {
//         if (lew_gor_w<0 || lew_gor_k<0)                  // Z lewej górnej strony koniec planszy
//             jeden_koniec=true;
//         else
//         {
//             if (this->POLE[lew_gor_w][lew_gor_k]==XO)    // Z lewej górnej strony jest pożądany znak X/O
//                 licznik++;
//             else                                         // Z lewej górnej strony nie ma już pożądanego znaku
//                 jeden_koniec=true; 
//         }

//         if (pr_dol_w>=this->ROZM || pr_dol_k>=this->ROZM)// Z prawej dolnej strony koniec planszy
//             dwa_koniec=true;
//         else
//         {
//             if (this->POLE[pr_dol_w][pr_dol_k]==XO)      // Z prawej dolnej strony jest pożądany znak X/O
//                 licznik++;
//             else                                         // Z prawej dolnej strony nie ma pożądenego znaku
//                 dwa_koniec=true; 
//         }

//         if (licznik == this->ILE_WYGRYWA-1)              // CZY WYGRANA?!
//             return true;
//     }  
//     licznik = 0; jeden_koniec=false; dwa_koniec=false;   // Wracanie do stanu początkowego zmiennych pomocniczych

//     // Sprawdzamy lewy dolny i prawy górny na ukos (/) 
//     for (int lew_dol_w=wiersz, lew_dol_k=kolumna-2, pr_gor_w=wiersz-2, pr_gor_k=kolumna; jeden_koniec==false || dwa_koniec==false; lew_dol_w++, lew_dol_k--, pr_gor_w--, pr_gor_k++) 
//     {
//         if (lew_dol_w>=this->ROZM || lew_dol_k<0)        // Z lewej dolnej strony koniec planszy
//             jeden_koniec=true;
//         else
//         {
//             if (this->POLE[lew_dol_w][lew_dol_k]==XO)    // Z lewej dolnej strony jest pożądany znak X/O
//                 licznik++;
//             else                                         // Z lewej dolnej strony nie ma już pożądanego znaku
//                 jeden_koniec=true; 
//         }

//         if (pr_gor_w<0 || pr_gor_k>=this->ROZM)          // Z prawej górnej strony koniec planszy
//             dwa_koniec=true;
//         else
//         {
//             if (this->POLE[pr_gor_w][pr_gor_k]==XO)      // Z prawej górnej strony jest pożądany znak X/O
//                 licznik++;
//             else                                         // Z prawej górnej strony nie ma pożądenego znaku
//                 dwa_koniec=true; 
//         }

//         if (licznik == this->ILE_WYGRYWA-1)              // CZY WYGRANA?!
//             return true;
//     }  

//     return false;                                        // Jeśli w żadnej z pętli for nie ma wygranej, to zwracamy, brak wygranej (false)
// }

// void Plansza::gra (Si & komputer, bool kontraSi)
// {
//     char XO = 'O'; // Zaczyna O
//     bool dobry_ruch = true, wygrana = false, remis = false, kolejSi;
//     int wiersz, kolumna, pomoc = 0, ilosc_rekurencji = 0;

//     if (kontraSi == false) // GRACZ VS GRACZ =============================================================================
//     {
//         while (wygrana == false && remis == false) // Petla gry
//         {
//             this->rysuj(); // Rysowanie planszy

//             do
//             {
//                 cout << "Kolej: " << XO <<endl; 
//                 cout << "Podaj nr. wiersza i kolumny:\n";
//                 cout << "Wiersz: "; cin >> wiersz; // Wpisywanie wiersza
//                 while (wiersz > this->ROZM)
//                 {
//                     cout << "Blad! Wiersz musi byc mniejszy niz " << this->ROZM+1 <<".\nPodaj nr. wiersza: "; cin >> wiersz;
//                 }
//                 cout << "Kolumna: "; cin >> kolumna; // Wpisywanie kolumny
//                 while (kolumna > this->ROZM)
//                 {
//                     cout << "Kolumna musi byc mniejsza niz " << this->ROZM+1 <<".\nPodaj nr. kolumny: "; cin >> wiersz;
//                 }
//                 dobry_ruch = this->ruch(XO, wiersz, kolumna);
//             } while (dobry_ruch == false);

//             system("cls");                      // Czyszczenie ekranu
//             wygrana = this->czy_wygrana (XO, wiersz, kolumna);          // Sprawdzam czy wygrana
//             remis = this->czy_remis();          // Sprawdzam czy remis

//             if (wygrana == false && remis == false)         // Jeśli nie ma wygranej, ani remisu to zmiana gracza
//             {
//                 if (XO == 'X') 
//                     XO = 'O';
//                 else
//                 if (XO == 'O')
//                     XO = 'X';
//             }
//             else
//             {   
//                 if (wygrana == true) // Jeśli wygrana
//                 {
//                     this->rysuj();
//                     cout << "Koniec gry, wygral gracz: " << XO << endl;
//                 }
//                 if (remis == true) // Jeśli remis
//                 {
//                     this->rysuj();
//                     cout << "Koniec gry, REMIS!" << endl;
//                 }
//             }
//         }
//     }
//     else if (kontraSi == true) // GRACZ VS Si ===============================================================================
//     {
//         kolejSi = true; // Zaczyna komputer "O"

//         while (wygrana == false && remis == false) // Pętla gry
//         {
//             this->rysuj(); // Rysowanie planszy

//             if (kolejSi==true)
//                 XO = 'O';
//             else    
//                 XO = 'X';

//             if (kolejSi == false) // KOLEJ GRACZA 
//             {
//                 do
//                 {
//                     cout << "Kolej: " << XO <<endl; 
//                     cout << "Podaj nr. wiersza i kolumny:\n";
//                     cout << "Wiersz: "; cin >> wiersz; // Wpisywanie wiersza
//                     while (wiersz > this->ROZM)
//                     {
//                         cout << "Blad! Wiersz musi byc mniejszy niz " << this->ROZM+1 <<".\nPodaj nr. wiersza: "; cin >> wiersz;
//                     }
//                     cout << "Kolumna: "; cin >> kolumna; // Wpisywanie kolumny
//                     while (kolumna > this->ROZM)
//                     {
//                         cout << "Kolumna musi byc mniejsza niz " << this->ROZM+1 <<".\nPodaj nr. kolumny: "; cin >> wiersz;
//                     }
//                     dobry_ruch = this->ruch(XO, wiersz, kolumna);
//                 } while (dobry_ruch == false);

//                 // system("cls"); // Czyszczenie ekranu
//                 wygrana = this->czy_wygrana (XO, wiersz, kolumna); // Sprawdzam czy wygrana
//                 remis = this->czy_remis(); // Sprawdzam czy remis
 
//                 if (wygrana == true) // Jeśli wygrana
//                 {
//                     this->rysuj();
//                     cout << "Koniec gry, wygral gracz: " << XO << endl;
//                 }
//                 else if (remis == true) // Jeśli remis
//                 {
//                     this->rysuj();
//                     cout << "Koniec gry, REMIS!" << endl;
//                 }

//                 kolejSi = true; // Zmiana gracza
//             }

//             else // KOLEJ KOMPUTERA 
//             {
//                 this->najlepszy_ruch(komputer);
//                 wiersz = komputer.get_wiersz()+1; kolumna = komputer.get_kolumna()+1;
//                 this->ruch(XO, wiersz, kolumna);

//                 // system("cls"); // Czyszczenie ekranu
//                 wygrana = this->czy_wygrana (XO, wiersz, kolumna); // Sprawdzam czy wygrana
//                 remis = this->czy_remis(); // Sprawdzam czy remis
 
//                 if (wygrana == true) // Jeśli wygrana
//                 {
//                     this->rysuj();
//                     cout << "Koniec gry, wygral gracz: " << XO << endl;
//                 }
//                 else if (remis == true) // Jeśli remis
//                 {
//                     this->rysuj();
//                     cout << "Koniec gry, REMIS!" << endl;
//                 }

//                 kolejSi = false; // Zmiana gracza
//             }
//         }
//     }
// }
