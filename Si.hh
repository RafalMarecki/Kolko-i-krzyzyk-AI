#ifndef SI_HH
#define SI_HH

using namespace std;

class Si
{
    private:
    char XO = 'X';
    int WIERSZ = 0;
    int KOLUMNA = 0;

    public:
    Si (); // Konstruktor domyślny
    Si (int w, int k); // Konstruktor parametryczny
    void set_pozycja (int w, int k);
    int get_wiersz ();
    int get_kolumna ();
};

#endif