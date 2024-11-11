#include <fstream>

#include "HesTabela.h"
#include "DvostrukoHesiranje.h"

void dodajIzDatoteke(HesTabela* tabela){
    string datoteka;
    cout << "Unesi ime datoteke: " << endl;
    cin >> datoteka;
    ifstream fajl(datoteka);
    string rec;
    int kljuc;
    while (fajl >> rec >> kljuc) tabela->dodaj(kljuc,rec);
    cout << endl << "Reci su unete u hes tabelu!" << endl << endl;
    fajl.close();
}

void performanse(HesTabela* tabela,const vector<int> &kljucevi, const vector<string> &reci){
    int min=INT_MAX, maks=INT_MIN;
    for (int i=0; i<kljucevi.size(); i++){
        tabela->dodaj(kljucevi[i], reci[i]);
        if (kljucevi[i]>maks) maks=kljucevi[i];
        if (kljucevi[i]<min) min=kljucevi[i];
    }
    cout << endl << "Prosecan broj pristupa pri uspesnoj pretrazi: " << setprecision(3) << tabela->prosekUspesna() << endl << endl;
    for(int i=0; i<kljucevi.size()*10; i++){
        random_device rand;
        mt19937 gen(rand());
        uniform_int_distribution<int> opseg(min, maks);
        int broj = opseg(gen);
        tabela->pronadji(broj);
    }
    cout << "Prosecan broj pristupa pri neuspesnoj pretrazi: " << setprecision(3) << tabela->prosekNeuspesna() << endl << endl;
    tabela->isprazni();
}

int main() {
    int br,p,q,n;
    bool adaptivna=false;
    HesTabela *tabela=nullptr;
    DvostrukoHesiranje* DH=nullptr;
    while(true){
        cout<<"1. Formiraj praznu hes tabelu\n2. Ispisi hes tabelu\n3. Pronadji rec u hes tabeli\n4. Dodaj rec u hes tabelu\n5. Dodaj reci u hes tabelu iz datoteke\n6. Obrisi rec iz hes tabele\n7. Ispisi prosecan broj pristupa pri uspesnoj pretrazi\n8. Ispisi prosecan broj pristupa pri neuspesnoj pretrazi\n9. Ispisi performanse\n10. Isprazni hes tabelu\n0. Prekini izvrsavanje programa\n\nIzaberi:" << endl;
        cin >> br;
        cout << endl;
        if(br<0 || br>11) {
            cout << "Izabrao/la si opciju koja ne postoji!\nPokusaj ponovo!\n" << endl;
            continue;
        }
        if(br==0){
            delete tabela;
            delete DH;
            exit(0);
        }
        if(br==1) {
            if (tabela!=nullptr) delete tabela;
            string izbor;
            cout << "Unesi velicinu tabele: " << endl;
            cin >> n;
            cout << "Unesi parametre p i q (parametri adresne fukcije za dvostruko hesiranje): " << endl;
            cin >> p >> q;
            cout << "Da li zelis da tabela bude adaptivna? (da/ne): " << endl;
            cin >> izbor;
            if (izbor=="da") adaptivna=true;
            DH=new DvostrukoHesiranje(p,q);
            tabela=new HesTabela(n,DH,adaptivna);
            cout << endl;
        }
        if(br==2) {
            if(tabela!= nullptr){
                cout << *tabela << endl;
                cout << "Velicina tabele: " << tabela->dohvN() << endl;
                cout << "Broj kljuceva u tabeli: " << tabela->dohvBrK() << endl;
                cout << "Popunjenost: " << setprecision(3) << tabela->popunjenost()*100 << "%" << endl << endl;
            }
        }
        if(br==3) {
            int k;
            cout << "Unesi kljuc za pretragu: " << endl;
            cin >> k;
            string rec=tabela->pronadji(k);
            if (rec=="0") cout << "Nije pronadjena rec za zadati kljuc!" << endl << endl;
            else cout << "Pronadjena rec je " << rec << endl << endl;
        }
        if(br==4){
            string rec;
            int k;
            cout << "Unesi rec: " << endl;
            cin >> rec;
            cout << "Unesi kljuc: " << endl;
            cin >> k;
            bool dodat=tabela->dodaj(k,rec);
            if (dodat) cout << "Rec je dodata u hes tabelu!" << endl << endl;
            else cout << "Rec nije dodata u hes tabelu!" << endl << endl;
        }
        if(br==5) {
            dodajIzDatoteke(tabela);
        }
        if(br==6) {
            int k;
            cout << "Unesi kljuc za koji zelis da se obrise rec: " << endl;
            cin >> k;
            bool obrisan=tabela->obrisi(k);
            if (obrisan) cout << "Rec je obrisana iz hes tabele!" << endl << endl;
            else cout << "Rec se ne nalazi u hes tabeli!" << endl << endl;
        }
        if(br==7) {
            cout << "Prosecan broj pristupa pri uspesnoj pretrazi: " << setprecision(3) << tabela->prosekUspesna() << endl << endl;
        }
        if(br==8) {
            if(tabela->prosekNeuspesna()==0) cout << "Nema podataka za neuspesnu pretragu!" << endl;
            else cout << "Prosecan broj pristupa pri neuspesnoj pretrazi: " << setprecision(3) << tabela->prosekNeuspesna() << endl << endl;
        }
        if(br==9) {
            HesTabela *perfTab=new HesTabela(n,DH, adaptivna);
            int brK;
            cout << "Unesi broj reci koje zelis da dodas: " << endl;
            cin >> brK;
            vector<string> reci(brK);
            vector<int> kljucevi(brK);
            for (int i=0; i<brK; i++){
                cout << "Unesi rec: " << endl;
                cin >> reci[i];
                cout << "Unesi kljuc za unetu rec: " << endl;
                cin >> kljucevi[i];
            }
            performanse(perfTab,kljucevi,reci);
            delete perfTab;
        }
        if(br==10) {
            tabela->isprazni();
            cout << "Hes tabela je prazna!" << endl << endl;
        }
    }
    return 0;
}