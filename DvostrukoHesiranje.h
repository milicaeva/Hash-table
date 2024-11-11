#ifndef SM220361_DVOSTRUKOHESIRANJE_H
#define SM220361_DVOSTRUKOHESIRANJE_H

#include "AdresnaFunkcija.h"

class DvostrukoHesiranje : public AdresnaFunkcija{
    int p,q;
public:
    DvostrukoHesiranje(int pp, int qq) : p(pp), q(qq) {}
    int dohvAdresu(int kljuc, int adr, int pok) const override { return (adr+pok*(q+(kljuc%p))); }
};

#endif
