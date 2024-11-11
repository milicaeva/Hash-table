#ifndef SM220361_HESTABELA_H
#define SM220361_HESTABELA_H

#include "AdresnaFunkcija.h"

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <iomanip>
#include <cmath>

using namespace std;

class HesTabela {
    struct Cvor{
        int kljuc;
        string rec;
        bool obrisan;

        Cvor() : kljuc(-1), rec(""), obrisan(false) {}
    };

    vector<Cvor> tabela;
    int brkljuceva, n, brPokZaUspeh,brPokZaNeuspeh, brNenadjenih;
    AdresnaFunkcija *adrFun;
    const bool adaptivna;

public:
    HesTabela(int velicina, AdresnaFunkcija* aF, bool adaptivna) : tabela(velicina), brkljuceva(0), n(velicina), adrFun(aF), brPokZaNeuspeh(0), brPokZaUspeh(0), brNenadjenih(0), adaptivna(adaptivna) {}
    string pronadji(int k);
    bool dodaj(int k, const string& rec);
    bool obrisi(int k);
    double prosekUspesna() const;
    double prosekNeuspesna() const;
    void isprazni();
    int dohvBrK() const;
    int dohvN() const;
    friend ostream &operator<<(ostream &os, const HesTabela &HT);
    double popunjenost() const;

private:
    void resetPN();
    void adaptiraj();
};

#endif