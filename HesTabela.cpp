#include "HesTabela.h"

string HesTabela::pronadji(int k) {
    int adr=k%n, pok=0;
    while (pok<n){
        int ind=(adrFun->dohvAdresu(k,adr,pok))%n;
        if(tabela[ind].kljuc==-1 && !tabela[ind].obrisan) { break; }
        if(tabela[ind].kljuc==k) { return tabela[ind].rec; }
        pok++;
    }
    brPokZaNeuspeh+=(pok+1);
    brNenadjenih++;
    return "0";
}

bool HesTabela::dodaj(int k, const string& rec) {
    if(adaptivna && ((double)(brkljuceva+1)/n>=0.75 || prosekNeuspesna()>(double)n/2)) adaptiraj();
    if (k<0) return false;
    int adr=k%n, pok=0;
    while (pok<n){
        int ind=(adrFun->dohvAdresu(k,adr,pok))%n;
        if(tabela[ind].kljuc==-1 || tabela[ind].obrisan){
            tabela[ind].kljuc=k;
            tabela[ind].rec=rec;
            tabela[ind].obrisan=false;
            brkljuceva++;
            brPokZaUspeh+=(pok+1);
            return true;
        }
        else if(tabela[ind].kljuc==k) { return false; }
        pok++;
    }
    return false;
}

bool HesTabela::obrisi(int k) {
    int adr=k%n, pok=0;
    while (pok<n){
        int ind=(adrFun->dohvAdresu(k,adr,pok))%n;
        if(tabela[ind].kljuc==-1 && !tabela[ind].obrisan) { break; }
        if(tabela[ind].kljuc==k){
            tabela[ind].kljuc=-1;
            tabela[ind].rec="";
            tabela[ind].obrisan=true;
            brkljuceva--;
            brPokZaUspeh-=(pok+1);
            return true;
        }
        pok++;
    }
    return false;
}

double HesTabela::prosekUspesna() const {
    if(brkljuceva==0) return 0;
    return (double)brPokZaUspeh/brkljuceva;
}

double HesTabela::prosekNeuspesna() const {
    if(brNenadjenih==0) return 0;
    return (double)brPokZaNeuspeh/brNenadjenih;
}

void HesTabela::resetPN() { brNenadjenih=brPokZaNeuspeh=0; }

void HesTabela::isprazni() {
    for (int i=0; i<n; i++) {
        tabela[i].kljuc=-1;
        tabela[i].rec="";
        tabela[i].obrisan=true;
    }
    brkljuceva=brPokZaUspeh=0;
    resetPN();
}

int HesTabela::dohvBrK() const { return brkljuceva; }

int HesTabela::dohvN() const { return n; }

double HesTabela::popunjenost() const { return (double)brkljuceva/n; }

ostream &operator<<(ostream &os, const HesTabela &HT) {
    for (int i=0; i<HT.n; i++) {
        if (HT.tabela[i].kljuc==-1) {
            os << "EMPTY" << endl;
        }
        else {
            os << "Kjuc: " << HT.tabela[i].kljuc << ", Rec: " << HT.tabela[i].rec << endl;
        }
    }
    return os;
}

void HesTabela::adaptiraj() {
    vector<string> reci(brkljuceva);
    vector<int> kljucevi(brkljuceva);
    int j=0;
    for (int i=0; i<n; i++){
        if(tabela[i].kljuc!=-1){
            reci[j]=tabela[i].rec;
            kljucevi[j]=tabela[i].kljuc;
            j++;
        }
    }
    isprazni();
    n=::ceil(n*1.5);
    tabela.resize(n);
    for(int i=0; i<kljucevi.size(); i++){
        dodaj(kljucevi[i], reci[i]);
    }
}