#include <iostream>
#include <cstdio>
#include "Si.hh"

using namespace std;

Si::Si ()
{
    this->WIERSZ = 0;
    this->KOLUMNA = 0;
}

Si::Si (int w, int k)
{
    this->WIERSZ = w;
    this->KOLUMNA = k;
}

void Si::set_pozycja (int w, int k)
{
    this->WIERSZ = w;
    this->KOLUMNA = k;
}

int Si::get_wiersz ()
{
    return this->WIERSZ;
}

int Si::get_kolumna ()
{
    return this->KOLUMNA;
}
