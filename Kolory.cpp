// Kolory.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <string>  
#include <fstream>
#include <vector>
#include <cstring>
#include <cassert>
#include <locale.h>

using namespace std;

class Gracz {
public:
    string imie;
    int kasa = 0;
    int portfel = 0; //kasa z wygranych rund

    Gracz operator+(const Gracz& pieniadze) const {
        Gracz gracz = *this;
        gracz.kasa += pieniadze.kasa;
        gracz.portfel += pieniadze.portfel;
        return gracz;

    }

    Gracz operator-(const Gracz& pieniadze) const {
        Gracz gracz = *this;
        gracz.kasa -= pieniadze.kasa;
        gracz.portfel -= pieniadze.portfel;
        return gracz;
    }

    Gracz operator>(const Gracz& gracz1, const Gracz& gracz2) {
        return gracz1.portfel > gracz2.portfel;
    }

    Gracz operator==(const Gracz& gracz1, const Gracz& gracz2) {           //porównanie pól wartości obu graczy
        return (gracz1.imie == gracz2.imie && gracz1.kasa == gracz2.kasa && gracz1.portfel == gracz2.portfel);
    }

};

class Gra {
private:
    vector<string> hasla;
    string haslo;
    int n;
    int maska[100], suma = 0, zgadl = 0, sa_spolgloski = 0, kwota = 0;
    char wybor;
    int kolejka = 0;
    int Kolo[16] = { -1, 0, 100, 200, 100, 200, 100, 200, 500, 500, 1000, 1000, 1500, 2000, 3000, 5000 };

    char operator[](int indeksHasla) {
        return haslo[indeksHasla];
    }


public:
    Gra() {
        wczytajHasla();
        wylosujHaslo();
        dodajGraczy();
    }

    void wczytajHasla() {
        ifstream strum;
        strum.open("dane.txt");

        while (!strum.eof()) {
            string s;
            getline(strum, s);
            hasla.push_back(s);
        }
        strum.close();
    }

    void wylosujHaslo() {
        int j = rand() % hasla.size();
        haslo = hasla[j];
        n = haslo.size();

        for (int i = 0; i < n; i++) {
            if (haslo[i] == ' ')
                maska[i] = 0;
            else
                maska[i] = 1;
        }
    }

    void dodajGraczy() {
        gracze[0].imie = "Bryanusz";
        gracze[1].imie = "Jessica ";
        gracze[2].imie = "Nepomucen";
    }

    int jestSamogloska(char c) {
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y' ||
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' || c == 'Y')
            return 1;
        else
            return 0;
    }

    char wczytajZnak() {
        string letter;
        cin >> letter;

        while (letter.length() != 1) {
            cout << endl << "Type a single letter and press <enter>: ";
            cin >> letter;
        }

        for (auto& c : letter) // & zapamietuje modyfikacje w petli & - referencja
            c = toupper(c);

        return letter[0];
    }

    char wczytajWybor() {
        char wybor;
        wybor = wczytajZnak();

        while (wybor != '1' && wybor != '2') {
            cout << endl << "Wybierz [1-2]: ";
            cin >> wybor;
        }

        return wybor;
    }

    void textPlayers() {
        int i;
        cout << "\n";
        for (i = 0; i < 3; i++) {
            if (i == kolejka) {
                cout << "\033[1;34m";
            }
            cout << gracze[i].imie << "\t" << gracze[i].kasa << "\n";
            cout << "\033[0m";
        }
        cout << "\n";
    }
}

int main() {
    Gra gra;

    cout << "Gra w 'Kolo Fortuny'\n";
    gra.textPlayers();

    while (gra.zgadl == 0) {
        if (gra.kolejka == 3)
            gra.kolejka = 0;

        cout << "Gracz: " << gra.gracze[gra.kolejka].imie << "\n";
        cout << "Kasa: " << gra.gracze[gra.kolejka].kasa << "\n";
        cout << "Portfel: " << gra.gracze[gra.kolejka].portfel << "\n";

        cout << "1. Obroc kolkiem\n";
        cout << "2. Zgadnij haslo\n";

        gra.wybor = gra.WczytajWybor();
        switch (gra.wybor) {
        case '2':
            cout << "Podaj haslo" << endl;
            getline(cin >> ws, proba);  // wczytanie z klawiatury string z uwzgl. whitespa
            for (auto& c : proba)  // & zapamietuje modyfikacje w petli & - referencja
                c = toupper(c);
            if (haslo == proba) {
                cout << endl << " !!!!!!!!!! =======   WYGRANA ========== !!!!!!!!!!!!!" << endl;
                gracze[kolejka].portfel += gracze[kolejka].kasa;
                break;
            }
            else
            {
                kolejka = (kolejka + 1) % 3;
                suma = 1;
                cout << endl << " !!!!!!!!!! =======   ZLE ========== !!!!!!!!!!!!!" << endl;
                cout << endl << "=================================================" << endl;
                continue;
                break;
        case '1':
            gra.zgadnijHaslo();
            break;
            }

            if (gra.sa_spolgloski == 0)
                gra.kolejka = (gra.kolejka + 1) % 3;

            if (gra.zgadl == 1) {
                for (int i = 0; i < 3; i++) {
                    if (gra.gracze[i].portfel > gra.suma) {
                        gra.suma = gra.gracze[i].portfel;
                        cout << "\nGratulacje, wygral gracz " << gra.gracze[i].imie << " z kasa: " << gra.gracze[i].kasa + gra.gracze[i].portfel << "!\n";
                    }
                }
            }
        }

        return 0;
    }
}

