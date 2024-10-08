#include <iostream>
#include <stack>
#include <queue>
#include <fstream>
using namespace std;

struct Elem
{
    long long int CA_ID;
    long long int CA_B_ID;
    long long int CA_C_ID;
    string CA_NAME;
    int CA_TAX_ST;
    double CA_BAL;
    Elem( long long int CA_ID, long long int CA_B_ID, long long int CA_C_ID, string CA_NAME, int CA_TAX_ST, double CA_BAL ):
    CA_ID(CA_ID),CA_B_ID(CA_B_ID),CA_C_ID(CA_C_ID),CA_NAME(CA_NAME),CA_TAX_ST(CA_TAX_ST),CA_BAL(CA_BAL)
    {};
};

struct Cvor
{
    int m;
    int zauzeto;
    Cvor* cvorovi[10];
    Elem* zapisi[9];

    Cvor(int n) :m(n),zauzeto(0)
    {

        for (int i = 0; i < m; i++)
        {
            cvorovi[i] = nullptr;
        }

        for (int i = 0; i < m-1; i++)
        {
            zapisi[i] = nullptr;
        }
    }
    ~Cvor()
    {
        if (cvorovi[0]!= nullptr) {
            for (int i = 0; i < zauzeto; ++i) {
                if (zapisi[i] != nullptr) { delete zapisi[i]; }
            }
       }
    }
};

bool list(Cvor* cvor)
{
    if (cvor->cvorovi[0]== nullptr)return true;
    else return false;

}
struct zapis_za_funkciju
{
    Elem* zapis;
    Cvor* ubacivac;
    Cvor* koren;
};

zapis_za_funkciju B_NODE_INSERT(Cvor* koren,Elem* zapis,stack<Cvor*> pomocni,Cvor* trenutni,Cvor* ubacivac)
{

    zapis_za_funkciju povratak;
    Cvor* otac=pomocni.top();
    Cvor* novi = new Cvor(trenutni->m);
    Elem* temporary[trenutni->m];
    Cvor* privremeni[trenutni->m+1];
    for (int i = 0; i <trenutni->m-1 ; ++i)
    {
        temporary[i]=trenutni->zapisi[i];
    }
    for (int i = 0; i <trenutni->m ; ++i) {
        privremeni[i]=trenutni->cvorovi[i];
    }
    if (temporary[trenutni->zauzeto-1]->CA_ID>zapis->CA_ID)
    {
        for (int i = 0; i < trenutni->zauzeto - 1; ++i) {
            if (trenutni->zapisi[i]->CA_ID > zapis->CA_ID) {
                for (int j = trenutni->m - 1; j > i; --j) {
                    temporary[j] = temporary[j - 1];
                }
                temporary[i] = zapis;
                for (int j = trenutni->m; j > i; --j) {
                    privremeni[j] = privremeni[j - 1];
                }
                privremeni[i+1]=ubacivac;
                temporary[i] = zapis;
                break;
            }
        }
    }
    else{temporary[trenutni->m-1]=zapis;privremeni[trenutni->m]=ubacivac;}
    int indeks=trenutni->m/2;
    if (trenutni->m % 2==0)indeks--;
    trenutni->zauzeto=indeks;
    Elem* ubaciti=temporary[indeks];

    for (int i = 0; i < indeks+1 ; ++i) {
        trenutni->cvorovi[i] = privremeni[i];
    }

    for (int i = trenutni->m; i >indeks ; --i) {
        trenutni->cvorovi[i]=nullptr;
    }
    novi->zauzeto=trenutni->m-indeks-1;

    for (int i = 0; i < trenutni->m-indeks ; ++i) {
        novi->cvorovi[i]=privremeni[indeks+1+i];
    }

    for (int i = 0; i < indeks; ++i) {
        trenutni->zapisi[i] = temporary[i];
    }
    for (int i = indeks; i < trenutni->m - 1; ++i) {
        trenutni->zapisi[i] = nullptr;
    }
    for (int i = 0; i < trenutni->m - indeks; ++i) {
        novi->zapisi[i] = temporary[i + 1+ indeks];
    }
    if (koren==trenutni)
    {
        otac=new Cvor(trenutni->m);
        otac->zauzeto=1;
        otac->zapisi[0]=ubaciti;
        otac->cvorovi[0]=trenutni;
        otac->cvorovi[1]=novi;
        povratak.zapis=nullptr;
        povratak.ubacivac=nullptr;

        povratak.koren=otac;
        return povratak;
    }
    else if (otac->zauzeto+1<otac->m)
    {
        for (int i = 0; i < otac->zauzeto ; ++i)
        {
            if ( otac->zapisi[i]->CA_ID>ubaciti->CA_ID)
            {
                for (int j = otac->zauzeto; j >i ; --j)
                {
                    otac->zapisi[j]=otac->zapisi[j-1];
                    otac->cvorovi[j+1]=otac->cvorovi[j];
                }
                otac->cvorovi[i+1]=novi;
                otac->zapisi[i]=ubaciti;
                break;
            }
        }
        if (otac->zapisi[otac->zauzeto-1]->CA_ID<ubaciti->CA_ID){otac->zapisi[otac->zauzeto]=ubaciti;
            otac->zauzeto++;
            otac->cvorovi[otac->zauzeto]=novi;}
        povratak.zapis=nullptr;
        povratak.ubacivac=nullptr;
        povratak.koren=koren;
        return povratak;
    }
    else
    {
        povratak.zapis=ubaciti;
        povratak.ubacivac=novi;
        povratak.koren=koren;
        return povratak;
    }
}

Cvor* INSERT_NODE(Cvor* koren,Elem* zapis)
{
    Cvor* trenutni=koren;
    stack <Cvor*> pomocni;
    pomocni.push(nullptr);
    if (koren->zauzeto==0){koren->zauzeto++;koren->zapisi[0]=zapis;}
    else {
        while (true) {
            if (list(trenutni))break;
            pomocni.push(trenutni);
            int provera = 0;
            for (int i = 0; i < trenutni->zauzeto; ++i) {
                if (zapis->CA_ID <= trenutni->zapisi[i]->CA_ID) {
                    trenutni = trenutni->cvorovi[i];
                    provera = 1;
                    break;
                }
            }
            if (provera == 0) {
                trenutni = trenutni->cvorovi[trenutni->zauzeto];
            }
        }
        int provera = 1;
        for (int i = 0; i < trenutni->zauzeto; ++i) {
            if (trenutni->zapisi[i]->CA_ID == zapis->CA_ID) {
                cout << "Greska zapis sa primarnim kljucem " << zapis->CA_ID << " vec postoji!" << endl;
                provera = 0;
                break;
            }
        }
        if (provera == 1) {
            if (trenutni->zauzeto < (trenutni->m) - 1) {
                if (trenutni->zapisi[trenutni->zauzeto - 1]->CA_ID < zapis->CA_ID) {
                    trenutni->zapisi[trenutni->zauzeto] = zapis;
                    trenutni->zauzeto++;
                    Cvor *otac = pomocni.top();
                    pomocni.pop();
                    if (otac != nullptr) {
                        for (int i = 0; i < otac->m; ++i) {
                            if (otac->cvorovi[i] == trenutni && i < otac->zauzeto) {
                                otac->zapisi[i] = zapis;
                            }
                        }
                    }


                } else {
                    for (int i = 0; i < trenutni->zauzeto; ++i) {
                        if (trenutni->zapisi[i]->CA_ID > zapis->CA_ID) {
                            for (int j = trenutni->zauzeto - 1; j >= i; --j) {
                                trenutni->zapisi[j+1] = trenutni->zapisi[j];
                            }
                            trenutni->zapisi[i] = zapis;
                            trenutni->zauzeto++;
                            trenutni->cvorovi[trenutni->zauzeto] = trenutni->cvorovi[trenutni->zauzeto - 1];
                            trenutni->cvorovi[trenutni->zauzeto - 1] = nullptr;
                            break;
                        }

                    }
                }
            } else {
                // Prelamanje lista pocetak
                Cvor *novi = new Cvor(trenutni->m);
                Cvor *desni = trenutni->cvorovi[(trenutni->m) - 1];
                Cvor *otac = pomocni.top();

                pomocni.pop();
                Elem *temporary[trenutni->m];
                for (int i = 0; i < trenutni->m - 1; ++i) {
                    temporary[i] = trenutni->zapisi[i];
                }
                if (temporary[trenutni->zauzeto-1]->CA_ID>zapis->CA_ID)
                {
                    for (int i = 0; i < trenutni->zauzeto - 1; ++i) {
                        if (trenutni->zapisi[i]->CA_ID > zapis->CA_ID) {
                            for (int j = trenutni->m - 1; j > i; --j) {
                                temporary[j] = temporary[j - 1];
                            }
                            temporary[i] = zapis;
                            break;
                        }
                    }
                }
                else{temporary[trenutni->m-1]=zapis;}


                int indeks = trenutni->m;
                if (indeks % 2 == 1) { indeks = (trenutni->m / 2) + 1; }
                else { indeks = (trenutni->m / 2); }
                trenutni->cvorovi[trenutni->m - 1] = nullptr;
                trenutni->cvorovi[indeks] = novi;
                novi->cvorovi[trenutni->m - indeks] = desni;
                for (int i = 0; i < indeks; ++i) {
                    trenutni->zapisi[i] = temporary[i];
                }
                for (int i = indeks; i < trenutni->m - 1; ++i) {
                    trenutni->zapisi[i] = nullptr;
                }
                for (int i = 0; i < trenutni->m - indeks; ++i) {
                    novi->zapisi[i] = temporary[i + indeks];
                }
                for (int i = indeks; i < trenutni->m - 1; ++i) {
                    novi->zapisi[i] = nullptr;
                }
                trenutni->zauzeto = indeks;
                novi->zauzeto = trenutni->m - indeks;
                if (trenutni == koren) {
                    otac = new Cvor(trenutni->m);
                    koren = otac;
                    otac->zauzeto = 1;
                    otac->zapisi[0] = trenutni->zapisi[indeks - 1];
                    otac->cvorovi[0] = trenutni;
                    otac->cvorovi[1] = novi;
                } else if (otac->zauzeto + 1 >= otac->m) {
                    Elem *zapis = trenutni->zapisi[indeks - 1];
                    while (true) {
                        zapis_za_funkciju t = B_NODE_INSERT(koren, zapis, pomocni, otac, novi);
                        zapis = t.zapis;
                        novi = t.ubacivac;
                        koren = t.koren;
                        if (zapis == nullptr)break;
                        otac = pomocni.top();
                        pomocni.pop();
                    }
                } else {
                    Elem *ubaciti = trenutni->zapisi[indeks - 1];
                    for (int i = 0; i < otac->zauzeto; ++i) {
                        if (otac->zapisi[i]->CA_ID > ubaciti->CA_ID) {
                            for (int j = otac->zauzeto; j > i; --j) {
                                otac->zapisi[j] = otac->zapisi[j - 1];
                                otac->cvorovi[j + 1] = otac->cvorovi[j];
                            }
                            otac->cvorovi[i + 1] = novi;
                            otac->zapisi[i] = ubaciti;
                            break;
                        }
                    }
                    if (otac->zapisi[otac->zauzeto-1]->CA_ID<ubaciti->CA_ID){otac->zapisi[otac->zauzeto]=ubaciti;
                        otac->cvorovi[otac->zauzeto+1]=novi;}
                    otac->zauzeto++;
                }


            }

        }

    }
    if (!pomocni.empty()) {
        pomocni.pop();
    }
    return koren;
}

void ispis_zapis(Elem* zapis)
{
    cout << zapis->CA_ID << "|" << zapis->CA_B_ID << "|" << zapis->CA_C_ID << "|" <<
    zapis->CA_NAME << "|" << zapis->CA_TAX_ST << "|" << zapis->CA_BAL << endl;
}

zapis_za_funkciju B_DELETE_NODE(Cvor* koren,stack <Cvor*> pomocni,Cvor* trenutni,long long int primarni_kljuc,int limit,Elem* zamena)
{
    if (trenutni==koren)
    {
        if (trenutni->zauzeto==0)
        {
            koren=trenutni->cvorovi[0];
            delete trenutni;
            zapis_za_funkciju p;
            p.koren=koren;
            p.ubacivac=nullptr;
            p.zapis= nullptr;
            return p;
        }
        else
        {
            koren=trenutni;
            zapis_za_funkciju p;
            p.koren=koren;
            p.ubacivac=nullptr;
            p.zapis= nullptr;
            return p;
        }
    }
    else
    {
        Cvor* sledbenik= nullptr;
        Cvor* otac = pomocni.top();
        Cvor* prethodnik= nullptr;

        for (int i = 0; i < otac->zauzeto+1; ++i) {
            if (otac->cvorovi[i] == trenutni && i>0) {
                prethodnik = otac->cvorovi[i-1];
                break;
            }
        }
        for (int i = 0; i < otac->zauzeto; ++i) {
            if (otac->cvorovi[i]== trenutni) {
                sledbenik = otac->cvorovi[i+1];
                break;
            }
        }
        pomocni.pop();

        if (sledbenik!= nullptr && sledbenik->zauzeto-1>=limit)
        {
            //PRELIVANJE B SLEDBENIK
            int indeks = 0;
            for (int i = 0; i <otac->zauzeto+1; ++i) {
                if (otac->cvorovi[i]==trenutni)
                {
                    indeks=i;
                    break;
                }
            }
            trenutni->zauzeto++;
            trenutni->zapisi[trenutni->zauzeto-1]=otac->zapisi[indeks];
            trenutni->cvorovi[trenutni->zauzeto]=sledbenik->cvorovi[0];

            otac->zapisi[indeks]=sledbenik->zapisi[0];
            for (int i = 0; i <sledbenik->zauzeto-1 ; ++i) {
                sledbenik->zapisi[i]=sledbenik->zapisi[i+1];
                sledbenik->cvorovi[i]=sledbenik->cvorovi[i+1];
            }
            sledbenik->zauzeto--;
            sledbenik->cvorovi[sledbenik->zauzeto]=sledbenik->cvorovi[sledbenik->zauzeto+1];
            sledbenik->cvorovi[sledbenik->zauzeto+1]= nullptr;
            zapis_za_funkciju p;
            p.zapis= nullptr;
            p.ubacivac= nullptr;
            p.koren=koren;
            return p;

        }
        else if (prethodnik!= nullptr && prethodnik->zauzeto-1>=limit)
        {


            //PRELIVANJE B PRETHODNIK
            int indeks = 0;
            for (int i = 0; i <otac->zauzeto+1; ++i) {
                if (otac->cvorovi[i]==trenutni)
                {
                    indeks=i-1;
                    break;
                }
            }
            trenutni->zauzeto++;
            for (int i = trenutni->zauzeto-1; i >0 ; --i) {
                trenutni->zapisi[i]=trenutni->zapisi[i-1];
            }
            for (int i = trenutni->zauzeto; i >0 ; --i) {
                trenutni->cvorovi[i]=trenutni->cvorovi[i-1];
            }
            trenutni->zapisi[0]=otac->zapisi[indeks];
            trenutni->cvorovi[0]=prethodnik->cvorovi[prethodnik->zauzeto];
            prethodnik->zauzeto--;
            otac->zapisi[indeks]=prethodnik->zapisi[prethodnik->zauzeto];
            prethodnik->zapisi[prethodnik->zauzeto]= nullptr;
            prethodnik->cvorovi[prethodnik->zauzeto+1]= nullptr;
            zapis_za_funkciju p;
            p.zapis= nullptr;
            p.ubacivac= nullptr;
            p.koren=koren;
            return p;


        }
        else if (sledbenik!= nullptr)
        {
            //SPAJANJE B SLEDBENIK
            Elem* temporary[trenutni->zauzeto + sledbenik->zauzeto+1];
            Cvor* privremeni[trenutni->zauzeto + sledbenik->zauzeto+2];
            int indeks = 0;
            for (int i = 0; i <otac->zauzeto+1; ++i) {
                if (otac->cvorovi[i]==trenutni)
                {
                    indeks=i;
                    break;
                }
            }
            for (int i = 0; i <otac->zauzeto ; ++i) {
                if (otac->zapisi[i]->CA_ID==primarni_kljuc)
                {
                    otac->zapisi[i]=zamena;
                    break;
                }
            }
            for (int i = 0; i < trenutni->zauzeto; ++i) {
                    temporary[i]=trenutni->zapisi[i];
                    privremeni[i]=trenutni->cvorovi[i];
            }
            privremeni[trenutni->zauzeto]=trenutni->cvorovi[trenutni->zauzeto];
            temporary[trenutni->zauzeto]=otac->zapisi[indeks];
            for (int i = 0; i <sledbenik->zauzeto ; ++i) {
                temporary[trenutni->zauzeto+1+i]=sledbenik->zapisi[i];
                privremeni[trenutni->zauzeto+1+i]=sledbenik->cvorovi[i];
            }
            privremeni[trenutni->zauzeto + sledbenik->zauzeto+1]=sledbenik->cvorovi[sledbenik->zauzeto];

            trenutni->zauzeto=trenutni->zauzeto+sledbenik->zauzeto+1;
            for (int i = 0; i <trenutni->zauzeto ; ++i) {
                trenutni->zapisi[i]=temporary[i];
                trenutni->cvorovi[i]=privremeni[i];
            }
            trenutni->cvorovi[trenutni->zauzeto]=privremeni[trenutni->zauzeto];

            for (int i = otac->zauzeto-2; i >= indeks  ; --i) {
                otac->zapisi[i]=otac->zapisi[i+1];
            }
            for (int i = otac->zauzeto-1; i > indeks ; --i) {
                otac->cvorovi[i]=otac->cvorovi[i+1];
            }
            otac->zapisi[otac->zauzeto-1]= nullptr;
            otac->cvorovi[otac->zauzeto]= nullptr;
            otac->zauzeto--;

            //sledbenik= nullptr;
            if (otac->zauzeto<limit)
            {
                zapis_za_funkciju p;
                p.koren=koren;
                p.ubacivac= otac;
                p.zapis= nullptr;
                return p;
            }
            else
            {
                zapis_za_funkciju p;
                p.zapis= nullptr;
                p.ubacivac= nullptr;
                p.koren=koren;
                return p;

            }
        }
        else
        {
            //SPAJANJE B PRETHODNIK
            int indeks = 0;
             for (int i = 0; i <otac->zauzeto+1; ++i) {
                if (otac->cvorovi[i]==trenutni)
                {
                    indeks=i-1;
                    break;
                }
            }
            for (int i = 0; i <otac->zauzeto ; ++i) {
                if (otac->zapisi[i]->CA_ID==primarni_kljuc)
                {
                    otac->zapisi[i]=zamena;
                    break;
                }
            }
            Elem* temporary[trenutni->zauzeto + prethodnik->zauzeto+1];
            Cvor* privremeni[trenutni->zauzeto + prethodnik->zauzeto+2];


            for (int i = 0; i < prethodnik->zauzeto; ++i) {
                temporary[i]=prethodnik->zapisi[i];
                privremeni[i]=prethodnik->cvorovi[i];
            }
            privremeni[prethodnik->zauzeto]=prethodnik->cvorovi[prethodnik->zauzeto];
            temporary[prethodnik->zauzeto]=otac->zapisi[indeks];
            for (int i = 0; i <trenutni->zauzeto ; ++i) {
                temporary[prethodnik->zauzeto+1+i]=trenutni->zapisi[i];
                privremeni[prethodnik->zauzeto+1+i]=trenutni->cvorovi[i];
            }
            privremeni[trenutni->zauzeto + prethodnik->zauzeto+1]=trenutni->cvorovi[trenutni->zauzeto];

            prethodnik->zauzeto=trenutni->zauzeto+prethodnik->zauzeto+1;
            for (int i = 0; i <prethodnik->zauzeto ; ++i) {
                prethodnik->zapisi[i]=temporary[i];
                prethodnik->cvorovi[i]=privremeni[i];
            }
            prethodnik->cvorovi[prethodnik->zauzeto]=privremeni[prethodnik->zauzeto];

            for (int i = otac->zauzeto-2; i >= indeks  ; --i) {
                otac->zapisi[i]=otac->zapisi[i+1];
            }
            for (int i = otac->zauzeto-1; i > indeks ; --i) {
                otac->cvorovi[i]=otac->cvorovi[i+1];
            }
            otac->zapisi[otac->zauzeto-1]= nullptr;
            otac->cvorovi[otac->zauzeto]= nullptr;
            otac->zauzeto--;




            if (otac->zauzeto<limit)
            {
                zapis_za_funkciju p;
                p.koren=koren;
                p.ubacivac= otac;
                p.zapis= nullptr;
                return p;
            }
            else
            {
                zapis_za_funkciju p;
                p.zapis= nullptr;
                p.ubacivac= nullptr;
                p.koren=koren;
                return p;
            }

        }
    }
}

void DELETE_NODES(Cvor* koren)
{
    stack <Cvor*> Red_brisac;
    queue <Cvor*> Red_obilazak;
    Cvor* current=nullptr;
    Red_obilazak.push(koren);
    Red_brisac.push(koren);
    Elem* trenutni=nullptr;
    while (!Red_obilazak.empty())
    {
        current = Red_obilazak.front();
        Red_obilazak.pop();
        if (current->cvorovi[0]!= nullptr) {
            for (int i = 0; i < current->zauzeto + 1; ++i) {
                if (current->cvorovi[i] != nullptr) {
                    Red_obilazak.push(current->cvorovi[i]);
                    Red_brisac.push(current->cvorovi[i]);
                }
            }
        }
    }

    while (!Red_brisac.empty())
    {
        current = Red_brisac.top();
        Red_brisac.pop();
        delete current;
    }
}


Cvor* DELETE_NODE(Cvor* koren,long long int primarni_kljuc)
{
    Cvor* trenutni=koren;
    stack <Cvor*> pomocni;
    while (true) {
        if (list(trenutni))break;
        pomocni.push(trenutni);
        int provera = 0;
        for (int i = 0; i < trenutni->zauzeto; ++i) {
            if (primarni_kljuc <= trenutni->zapisi[i]->CA_ID) {
                trenutni = trenutni->cvorovi[i];
                provera = 1;
                break;
            }
        }
        if (provera == 0) {
            trenutni = trenutni->cvorovi[trenutni->zauzeto];
        }
    }
    int provera=0;
    for (int i = 0; i < trenutni->zauzeto ; ++i) {
        if (trenutni->zapisi[i]->CA_ID == primarni_kljuc){provera=1;break;}
    }
    if (provera==0){cout << "Greska zapis sa primarnim kljucem " << primarni_kljuc << " ne posotoji u indeksu!" << endl;}
    else
    {   int limit = (trenutni->m)/2;
        if (trenutni->zauzeto-1>=limit)
        {
            int indeks = 0;
            for (int i = 0; i < trenutni->zauzeto; ++i) {
                if (trenutni->zapisi[i]->CA_ID == primarni_kljuc) {
                    indeks = i;
                    break;
                }
            }
            if (indeks == trenutni->zauzeto - 1) {
                Cvor *otac = pomocni.top();
                pomocni.pop();
                Elem *zapis = trenutni->zapisi[indeks];
                Elem *zamena = trenutni->zapisi[indeks - 1];
                int checker = 0;
                while (true) {

                    for (int i = 0; i < otac->zauzeto; ++i) {
                        if (otac->zapisi[i]->CA_ID == primarni_kljuc) {
                            checker = 1;
                            break;
                        }
                    }
                    if (checker == 1)break;
                    else {
                        if (pomocni.empty())break;
                        otac = pomocni.top();
                        pomocni.pop();

                    }
                }
                if (checker==1){
                for (int i = 0; i < otac->zauzeto; ++i) {
                    if (otac->zapisi[i]->CA_ID == primarni_kljuc) {
                        otac->zapisi[i] = zamena;
                        delete zapis;

                    }
                }}
                trenutni->zapisi[trenutni->zauzeto-1]= nullptr;
                trenutni->zauzeto--;
                trenutni->cvorovi[trenutni->zauzeto] = trenutni->cvorovi[trenutni->zauzeto + 1];
                trenutni->cvorovi[trenutni->zauzeto + 1] = nullptr;
            } else {
                Elem *zapis = trenutni->zapisi[indeks];
                for (int i = indeks; i < trenutni->zauzeto - 1; ++i) {
                    trenutni->zapisi[i] = trenutni->zapisi[i + 1];
                }
                trenutni->zauzeto--;
                delete zapis;
                trenutni->cvorovi[trenutni->zauzeto] = trenutni->cvorovi[trenutni->zauzeto + 1];
                trenutni->cvorovi[trenutni->zauzeto + 1] = nullptr;
            }
        }
        else{
            //PROVERA DA LI SE MOZE IZVRSITI POZAJMICA ILI MORA SPAJANJE CVOROVA


            int indeks = 0;
            for (int i = 0; i < trenutni->zauzeto; ++i) {
                if (trenutni->zapisi[i]->CA_ID == primarni_kljuc) {
                    indeks = i;
                    break;
                }
            }

            Cvor* sledbenik= nullptr;
            Cvor* otac = pomocni.top();
            Cvor* prethodnik= nullptr;
            if (otac!= nullptr)
            {
                for (int i = 0; i < otac->zauzeto+1; ++i) {
                    if (otac->cvorovi[i] == trenutni && i>0) {
                        prethodnik = otac->cvorovi[i-1];
                        break;
                    }
                }
                for (int i = 0; i < otac->zauzeto; ++i) {
                    if (otac->cvorovi[i]== trenutni && i<otac->zauzeto) {
                        sledbenik = otac->cvorovi[i+1];
                        break;
                    }
                }
                pomocni.pop();
                if (sledbenik != nullptr && sledbenik->zauzeto - 1 >= limit)
                {
                    Elem *zapis = trenutni->zapisi[indeks];
                    for (int i = indeks; i < trenutni->zauzeto - 1; ++i) {
                        trenutni->zapisi[i] = trenutni->zapisi[i + 1];
                    }
                    trenutni->zapisi[trenutni->zauzeto-1] = sledbenik->zapisi[0];

                    for (int i = 0; i < otac->zauzeto + 1; ++i) {
                        if (otac->cvorovi[i] == trenutni) {
                            otac->zapisi[i]=trenutni->zapisi[trenutni->zauzeto-1];
                            break;
                        }
                    }
                    for (int i = 0; i <sledbenik->zauzeto-1 ; ++i) {
                        sledbenik->zapisi[i]=sledbenik->zapisi[i+1];
                        sledbenik->cvorovi[i]=sledbenik->cvorovi[i+1];
                    }
                    sledbenik->cvorovi[sledbenik->zauzeto-1]=sledbenik->cvorovi[sledbenik->zauzeto];
                    sledbenik->cvorovi[sledbenik->zauzeto]= nullptr;
                    sledbenik->zauzeto--;
                    while (true) {
                        int checker = 0;
                        for (int i = 0; i < otac->zauzeto; ++i) {
                            if (otac->zapisi[i]->CA_ID == primarni_kljuc) {
                                Elem* zapisivac=otac->zapisi[i];
                                checker = 1;
                                otac->zapisi[i]=trenutni->zapisi[trenutni->zauzeto-1];
                                delete zapisivac;
                                break;
                            }
                        }
                        if (checker == 1){break;}
                        else {
                            if (pomocni.empty())break;
                            otac = pomocni.top();
                            pomocni.pop();
                        }
                    }


                }
                else if (prethodnik != nullptr && prethodnik->zauzeto - 1 >= limit)
                {
                    Elem *zapis = trenutni->zapisi[indeks];
                    for (int i = indeks; i > 0; --i) {
                        trenutni->zapisi[i] = trenutni->zapisi[i - 1];
                    }
                    trenutni->zapisi[0] = prethodnik->zapisi[prethodnik->zauzeto-1];

                    for (int i = 0; i < otac->zauzeto + 1; ++i)
                    {
                        if (otac->cvorovi[i] == trenutni) {
                            otac->zapisi[i - 1]=prethodnik->zapisi[prethodnik->zauzeto-2];
                            otac->zapisi[i]=trenutni->zapisi[trenutni->zauzeto-1];
                            break;
                        }
                    }


                    prethodnik->cvorovi[prethodnik->zauzeto-1]=prethodnik->cvorovi[prethodnik->zauzeto];
                    prethodnik->cvorovi[prethodnik->zauzeto]= nullptr;
                    prethodnik->zapisi[prethodnik->zauzeto-1]=nullptr;
                    prethodnik->zauzeto--;
                    while (true) {
                        int checker = 0;
                        for (int i = 0; i < otac->zauzeto; ++i) {
                            if (otac->zapisi[i]->CA_ID == primarni_kljuc) {
                                Elem* zapisivac=otac->zapisi[i];
                                otac->zapisi[i] = trenutni->zapisi[trenutni->zauzeto-1];
                                delete zapisivac;
                                checker = 1;
                                break;
                            }
                        }
                        if (checker == 1)break;
                        else {
                            if (pomocni.empty())break;
                            otac = pomocni.top();
                            pomocni.pop();
                        }
                    }

                }
                else
                {
                    // SPAJANJE
                    int helper;
                    for (int i = 0; i <otac->zauzeto+1 ; ++i) {
                        if (otac->cvorovi[i]==trenutni){helper=i;break;}
                    }

                    if (sledbenik!= nullptr)
                    {
                       Elem* temporary[sledbenik->zauzeto+trenutni->zauzeto];
                        for (int i = 0; i <trenutni->zauzeto ; ++i) {
                            temporary[i]=trenutni->zapisi[i];
                        }
                        for (int i = 0; i < sledbenik->zauzeto; ++i)
                        {
                            temporary[trenutni->zauzeto+i]=sledbenik->zapisi[i];
                        }
                        Elem* zapis;
                        for (int i = 0; i <sledbenik->zauzeto+trenutni->zauzeto ; ++i) {
                            if (temporary[i]->CA_ID==primarni_kljuc)
                            {
                                zapis=temporary[i];
                                for (int j = i; j <sledbenik->zauzeto+trenutni->zauzeto-1 ; ++j) {
                                    temporary[j]=temporary[j+1];
                                }
                                break;
                            }
                        }
                        trenutni->cvorovi[trenutni->zauzeto]= nullptr;
                        trenutni->zauzeto=trenutni->zauzeto-1+sledbenik->zauzeto;
                        trenutni->cvorovi[trenutni->zauzeto]=sledbenik->cvorovi[sledbenik->zauzeto];
                        sledbenik->cvorovi[sledbenik->zauzeto]= nullptr;


                        for (int i = 0; i < trenutni->zauzeto; ++i) {
                            trenutni->zapisi[i]=temporary[i];
                        }

                        for (int i = helper+1; i < otac->zauzeto ; ++i)
                        {
                            otac->cvorovi[i]=otac->cvorovi[i+1];
                            otac->zapisi[i-1]=otac->zapisi[i];
                        }
                        otac->cvorovi[otac->zauzeto]= nullptr;
                        otac->zauzeto--;
                        int limit_un;
                        if (koren->m%2==1){limit_un=(koren->m)/2;}
                        else{limit_un=((koren->m)/2)-1;}
                        Elem* zamena=trenutni->zapisi[trenutni->zauzeto-1];
                        Cvor* pomagac=koren;
                        queue<Cvor*> level;
                        level.push(pomagac);
                        while (!level.empty())
                        {   pomagac=level.front();
                            if (!list(pomagac)) {

                                for (int i = 0; i < pomagac->zauzeto + 1; ++i) {
                                    if (pomagac->cvorovi[i] != nullptr)
                                        level.push(pomagac->cvorovi[i]);
                                }
                                for (int i = 0; i <pomagac->zauzeto; ++i) {
                                    if (pomagac->zapisi[i]->CA_ID==primarni_kljuc)
                                    {
                                        pomagac->zapisi[i]=zamena;break;
                                    }
                                }
                            }
                            level.pop();
                        }

                        if (otac->zauzeto<limit_un)
                        {
                            if (otac==koren) {
                                if (otac->zauzeto==0) {koren = trenutni;delete koren;}
                                else{koren=otac;}
                            }
                            else
                            {
                                while (true)
                                {
                                    zapis_za_funkciju p;
                                    p = B_DELETE_NODE(koren, pomocni, otac,primarni_kljuc,limit_un,zamena);
                                    koren=p.koren;
                                    pomocni.pop();
                                    if (p.ubacivac== nullptr)break;
                                    else{otac=p.ubacivac;}
                                }
                            }


                        }
                        delete zapis;

                    }

                    else
                    {
                        Elem* zapis;
                        Elem* temporary[prethodnik->zauzeto+trenutni->zauzeto];

                        for (int i = 0; i <prethodnik->zauzeto ; ++i) {
                            temporary[i]=prethodnik->zapisi[i];
                        }
                        for (int i = 0; i < trenutni->zauzeto; ++i)
                        {
                            temporary[prethodnik->zauzeto+i]=trenutni->zapisi[i];
                        }
                        for (int i = 0; i <prethodnik->zauzeto+trenutni->zauzeto ; ++i) {
                            if (temporary[i]->CA_ID==primarni_kljuc)
                            {
                                zapis=temporary[i];
                                for (int j = i; j <prethodnik->zauzeto+trenutni->zauzeto ; ++j) {
                                    temporary[j]=temporary[j+1];
                                }
                                break;
                            }
                        }
                        prethodnik->cvorovi[trenutni->zauzeto]= nullptr;
                        prethodnik->zauzeto=trenutni->zauzeto+prethodnik->zauzeto-1;
                        prethodnik->cvorovi[prethodnik->zauzeto]=trenutni->cvorovi[trenutni->zauzeto];
                        trenutni->cvorovi[trenutni->zauzeto]= nullptr;
                        for (int i = 0; i < prethodnik->zauzeto; ++i) {
                            prethodnik->zapisi[i]=temporary[i];
                        }


                        for (int i = helper; i < otac->zauzeto ; ++i)
                        {
                            otac->cvorovi[i]=otac->cvorovi[i+1];
                            otac->zapisi[i-1]=otac->zapisi[i];
                        }

                        otac->cvorovi[otac->zauzeto]= nullptr;

                        otac->zapisi[helper]=prethodnik->zapisi[prethodnik->zauzeto-1];

                        int limit_un;
                        if (koren->m%2==1){limit_un=(koren->m)/2;}
                        else{limit_un=((koren->m)/2)-1;}
                        Elem* zamena=prethodnik->zapisi[prethodnik->zauzeto-1];
                        Cvor* pomagac=koren;
                        queue<Cvor*> level;
                        level.push(pomagac);
                        otac->zauzeto--;
                        while (!level.empty())
                        {   pomagac=level.front();
                            if (!list(pomagac)) {

                                for (int i = 0; i < pomagac->zauzeto + 1; ++i) {
                                    if (pomagac->cvorovi[i] != nullptr)
                                        level.push(pomagac->cvorovi[i]);
                                }
                                for (int i = 0; i <pomagac->zauzeto; ++i) {
                                    if (pomagac->zapisi[i]->CA_ID==primarni_kljuc)
                                    {
                                        pomagac->zapisi[i]=zamena;break;
                                    }
                                }
                            }
                            level.pop();
                        }

                        if (otac->zauzeto<limit_un)
                        {
                            if (otac==koren) {
                                if (otac->zauzeto==0) {koren = trenutni;delete koren;}
                                else{koren=otac;}
                            }
                            else
                            {
                                while (true)
                                {
                                    zapis_za_funkciju p;
                                    p = B_DELETE_NODE(koren, pomocni, otac,primarni_kljuc,limit_un,zamena);
                                    koren=p.koren;
                                    pomocni.pop();
                                    if (p.ubacivac== nullptr)break;
                                    else{otac=p.ubacivac;}
                                }

                            }
                        }
                        delete zapis;
                    }
                }
            }
            else
            {
                Elem *zapis = trenutni->zapisi[indeks];
                for (int i = indeks; i < trenutni->zauzeto - 1; ++i) {
                    trenutni->zapisi[i] = trenutni->zapisi[i + 1];
                }
                trenutni->zauzeto--;

                delete zapis;
                if (trenutni->zauzeto==0)
                {

                    delete koren;
                    koren = nullptr;
                }
            }
        }
    }

    if (!pomocni.empty()) {
        pomocni.pop();
    }
    return koren;

}

void SEARCH_NODE(Cvor* koren,long long int primarni_kljuc,double &vrednost)
{
    Cvor *trenutni=koren;
    while (true)
    {
        if (list(trenutni))
        {
            int uspesno=0;
            for (int i = 0; i < trenutni->zauzeto ; ++i) {
                if (trenutni->zapisi[i]->CA_ID==primarni_kljuc)
                {
                    ispis_zapis(trenutni->zapisi[i]);
                    uspesno=1;
                    break;}
            }
            vrednost++;
            if (uspesno==0)cout << "Podatak sa primarnim kljucem " << primarni_kljuc << " nije prondjen" << endl;
            break;
        }
        else
        {   vrednost++;
            if (primarni_kljuc<=trenutni->zapisi[0]->CA_ID)
            {
                trenutni=trenutni->cvorovi[0];
            }
            else
            {   int provera=0;
                for (int i = 0; i <trenutni->zauzeto-1 ; ++i)
                {
                    if (primarni_kljuc <= trenutni->zapisi[i+1]->CA_ID && primarni_kljuc > trenutni->zapisi[i]->CA_ID)
                    {
                        trenutni=trenutni->cvorovi[i+1];
                        provera=1;
                        break;
                    }
                }
                if (provera==0)
                {
                    trenutni=trenutni->cvorovi[trenutni->zauzeto];
                }
            }
        }


    }
    cout << "Ukupan broj koraka je jednak " << vrednost << endl;
}

void SEARCH_NODE_K(Cvor* koren,long long int primarni_kljucevi[],double &vrednost,int k,std::ofstream& izlaz)
{
    Cvor *trenutni=koren;
    while (true)
    {
        if (trenutni->cvorovi[0]!= nullptr)
        {
            int uspesno=0;
            for (int i = 0; i < trenutni->zauzeto ; ++i) {
                if (trenutni->zapisi[i]->CA_ID>=primarni_kljucevi[0])
                {
                    uspesno=1;
                    trenutni=trenutni->cvorovi[i];
                    break;
                }
            }
            if (uspesno==0){trenutni=trenutni->cvorovi[trenutni->zauzeto];}
            vrednost++;
        }
        else{vrednost++;break;}
    }


            for (int i = 0; i < k; ++i) {
                    while (true)
                    {   if (primarni_kljucevi[i]<=trenutni->zapisi[trenutni->zauzeto-1]->CA_ID || trenutni->cvorovi[trenutni->zauzeto]==nullptr)break;
                        trenutni=trenutni->cvorovi[trenutni->zauzeto];
                        vrednost++;
                    }
                    for (int j = 0; j <trenutni->zauzeto ; ++j) {
                        if (primarni_kljucevi[i]==trenutni->zapisi[j]->CA_ID)
                        {   Elem* zapis=trenutni->zapisi[j];
                            izlaz << zapis->CA_ID << "|" << zapis->CA_B_ID << "|" << zapis->CA_C_ID << "|" <<
                                  zapis->CA_NAME << "|" << zapis->CA_TAX_ST << "|" << zapis->CA_BAL << endl;
                            break;
                        }
                    }
                }

}

void  ISPIS_INDEKSA(Cvor* koren)
{
    stack <Cvor*> stek;
    stack <int>indentacija;
    Cvor* trenutni=nullptr;
    stek.push(koren);
    int l=0;
    indentacija.push(l);
    while (!stek.empty())
    {
        l=indentacija.top();
        indentacija.pop();
        trenutni=stek.top();
        cout << endl;
        for (int i = 0; i <l ; ++i) {
            cout << "-";
        }
        cout << "[";
        for (int i = 0; i <trenutni->zauzeto ; ++i) {
            cout << (trenutni->zapisi[i]->CA_ID-43000000000);
            if (i<trenutni->zauzeto-1)cout << " ";
        }
        cout << "]";
        stek.pop();
        for (int i = trenutni->zauzeto; i>=0 ; --i) {
            if (!list(trenutni))
            {
                stek.push(trenutni->cvorovi[i]);
                indentacija.push(l+1);
            }
        }
    }
    cout << endl;
}


int main() {

    Cvor *koren = nullptr;
    char karakter;
    cout << "Moguce opcije su:";
    cout << endl;
    cout << "1.Stvaranje i unistavanje indeksa za datu tabelu\n"
         << "2.Ispis indeksa na standardni izlaz\n"
         << "3.Dodavanje novog zapisa u tabelu\n"
         << "4.Brisanje zapisa u tabeli po datom primarnom kljucu\n"
         << "5.Pretrazivanje jednog podatka i ispis ukupnog broja koraka za koji je pretraga zavrsena"
         << endl
         << "6.Pretrazivanje k podataka\n"
         << "7.Pretrazivanje k sukcesivnih podataka\n"
         << "8.Kraj programa" << endl;
    while (true)
    {
        int opcija;
        cout << endl;
        cout << "Unesite zeljenu opciju:";
        cin >> opcija;
        if (opcija == 8)break;
        switch (opcija) {
            case 1: {
                int m;
                cout << "Unesite red B+ stabla (mora biti izmedju 3 i 10 ukljucujuci i njih):";
                cin >> m;
                if (m < 3 || m > 10){cout << "Greska los unos reda stabla!" << endl;}
                else {
                    if (koren != nullptr)
                    {
                        DELETE_NODES(koren);
                        koren= nullptr;
                    }




                    string datoteka;
                    cout << endl;
                    cout << "Unesite ime datoteke:";

                    cin >> datoteka;
                    std::ifstream dat;
                    dat.open(datoteka);
                    if (!dat.is_open()) {
                        cout << "Greska datoteka " << datoteka <<
                             " nije uspesno otvorena ili ne postoji!" << endl;
                    } else {
                        koren = new Cvor(m);
                        while (true) {
                            long long int CA_ID;
                            long long int CA_B_ID;
                            long long int CA_C_ID;

                            string CA_NAME = "";
                            int CA_TAX_ST;
                            double CA_BAL;

                            dat >> CA_ID;
                            dat >> karakter;
                            if (karakter == '\n')break;
                            dat >> CA_B_ID;
                            dat >> karakter;
                            dat >> CA_C_ID;
                            dat >> karakter;
                            while (true) {
                                dat >> noskipws >> karakter;
                                if (karakter == '|')break;
                                CA_NAME += karakter;
                            }
                            if (CA_NAME=="")break;
                            dat >> CA_TAX_ST;
                            dat >> karakter;
                            dat >> CA_BAL;
                            dat >> karakter;
                            Elem *zapis = new Elem(CA_ID, CA_B_ID, CA_C_ID, CA_NAME, CA_TAX_ST, CA_BAL);

                            koren=INSERT_NODE(koren, zapis);

                        }

                        dat.close();

                    }

                }
                break;

                case 2: {
                    if (koren == nullptr) {
                        cout << "Prvo se mora napraviti indeks!" << endl;
                    } else {
                        cout << endl;
                        ISPIS_INDEKSA(koren);
                        cout << endl;

                    }
                }
                break;

                case 3:
                {
                    cout << "Unesite trazene podatke u formatu koji je dat u postavci:";
                    long long int CA_ID;
                    long long int CA_B_ID;
                    long long int CA_C_ID;
                    char karakter='a';
                    string CA_NAME = "";
                    int CA_TAX_ST;
                    double CA_BAL;
                    cin >> CA_ID;
                    //cin >> karakter;
                    cin >> CA_B_ID;
                    //cin >> karakter;
                    cin >> CA_C_ID;
                    cin >> karakter;
                    CA_NAME += karakter;
                    while (true) {
                        cin >> noskipws >> karakter;
                        if (karakter == '\n')break;
                        CA_NAME += karakter;
                    }
                    cin >> skipws >> CA_TAX_ST;
                    cin >> skipws >> CA_BAL;
                   // cin >> karakter;
                    Elem *zapis = new Elem(CA_ID, CA_B_ID, CA_C_ID, CA_NAME, CA_TAX_ST, CA_BAL);
                    if (koren== nullptr){cout << "Greska morate prvo stvoriti indeks!" << endl;}
                    else{koren=INSERT_NODE(koren, zapis);}


                }
                break;

                case 4:
                {
                    if (koren == nullptr) {
                        cout << "Prvo se mora napraviti indeks!" << endl;
                    } else {
                        cout << "Unesite primarni kljuc koji zelite da obrisete iz indeksa:";
                        long long int primary_key;
                        cin >> primary_key;

                        koren=DELETE_NODE(koren,primary_key);
                    }

                }
                break;

                case 5: {
                    if (koren == nullptr) {
                        cout << "Prvo se mora napraviti indeks!" << endl;
                    } else {
                        cout << "Unesite primarni kljuc na koji zelite da izvrsite proveru";
                        long long int primarni_kljuc;
                        cin >> primarni_kljuc;
                        double vrednost = 0;
                        SEARCH_NODE(koren, primarni_kljuc, vrednost);
                    }
                }
                break;

                case 6: {
                    if (koren == nullptr) {
                        cout << "Prvo se mora napraviti indeks!" << endl;
                    } else {
                        std::ofstream izlaz;
                        izlaz.open("izlaz.txt", std::ofstream::out | std::ofstream::trunc);
                        izlaz.close();
                        izlaz.open("izlaz.txt");
                        cout << "Unesite broj pretrazivanja k=";
                        int k;
                        cin >> k;
                        double prosek=0;
                        long long int niz[k];
                        cout << "Unesite primarne kljuceve na koje zelite da izvrsite pretragu:";
                        for (int i = 0; i < k; ++i) {

                            cin >> niz[i];

                        }
                        for (int i = 0; i <k ; ++i) {
                            long long int broj=niz[i];
                            int indeks=i;
                            for (int j = i+1; j <k ; ++j) {
                                if (niz[j]<=broj)
                                {
                                    indeks=j;
                                    broj=niz[j];
                                }
                            }
                            niz[indeks]=niz[i];
                            niz[i]=broj;
                        }
                        for (int i = 0; i < k; ++i) {
                            double dodaj=0;
                            SEARCH_NODE(koren, niz[i], dodaj);
                            prosek+=dodaj;
                        }
                        prosek = prosek / ((double) k);
                        cout << endl;
                        cout << "Prosecan broj koraka za uspesnu i neuspesnu pretragu je jednak " << prosek << endl;
                    }

                }
                break;

                case 7: {
                    if (koren == nullptr) {
                        cout << "Prvo se mora napraviti indeks!" << endl;
                    } else {
                        std::ofstream izlaz;
                        izlaz.open("izlaz.txt", std::ofstream::out | std::ofstream::trunc);
                        izlaz.close();
                        izlaz.open("izlaz.txt");
                        cout << "Unesite broj pretrazivanja k=";
                        int k;
                        cin >> k;
                        double prosek;
                        long long int niz[k];
                        cout << "Unesite pocetni primarni kljuc:";
                        long long int primary_key;
                        cin >> primary_key;
                        niz[0] = primary_key;
                        for (int i = 1; i < k; ++i) {
                            niz[i] = niz[i - 1] + 1;
                        }
                        SEARCH_NODE_K(koren, niz, prosek,k, izlaz);

                        prosek = prosek / ((double) k);

                        cout << "Prosecan broj koraka za uspesnu i" << endl << "neuspesn pretragu je jednak " << prosek << endl;
                    }
                }
                break;
            }

        }
    }
    cout << endl;
    cout << "ZAVRSETAK PROGRAMA";
    cout << endl;
    exit(0);
}