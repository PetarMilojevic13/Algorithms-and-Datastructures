#include <iostream>
#include <fstream>
using namespace std;
const int MAX=100;

int LKG(int klica, int a, int c, int m)
{
    int X = (a * klica + c) % m;
    return X;
}

int m_ary_search(int k, int m,int *K,int key)
{
    int mid=-5;
    int low = 0;
    int high = k-1;

    while (low <= high)
    {
        int brojac = 1;
        int dodatak = (high - low + 1) / m;
        int mid = low + dodatak;
        int stari_low = low;
        while (true)
        {
            mid = stari_low + dodatak*brojac;
            if (K[mid] == key) return mid;
            else
            {
                if (K[mid] > key)
                {
                    high = mid - 1; break;
                }
                else
                {
                    low = mid + 1;
                    if (brojac == m - 1)break;
                    brojac++;
                }
            }
        }
    }

    return -1;

}


double& m_ary_search_evaluation(int k, int m,int *K,int key,double& koraci)
{
    int mid=-5;
    int low = 0;
    int high = k-1;

    while (low <= high)
    {
        int brojac = 1;
        int dodatak = (high - low + 1) / m;
        int mid = low + dodatak;
        int stari_low = low;
        while (true)
        {
            mid = stari_low + dodatak*brojac;
            koraci++;
            if (K[mid] == key) {return koraci;}
            else
            {   koraci++;
                if (K[mid] > key)
                {
                    high = mid - 1; break;
                }
                else
                {
                    low = mid + 1;
                    if (brojac == m - 1)break;
                    brojac++;
                }
            }
        }
    }

    return koraci;

};


int optimised_m_ary_search(int k, int m, int* K, int key,int &trenutni)
{
    int mid = -5;
    int low = trenutni;
    int high = k - 1;

    while (low <= high)
    {
        int brojac = 1;
        int dodatak = (high - low + 1) / m;
        int mid = low + dodatak;
        int stari_low = low;
        while (true)
        {
            mid = stari_low + dodatak * brojac;
            if (K[mid] == key)
            {
                trenutni = mid; return mid;
            }
            else
            {
                if (K[mid] > key)
                {
                    high = mid - 1; break;
                }
                else
                {
                    low = mid + 1;
                    if (low == high && K[low] > key && low > 0) { trenutni = low - 1; }
                    else if (low == high && K[low] < key && high < k - 1) { trenutni = low + 1; }
                    else if (low == high) { trenutni = low; }
                    if (brojac == m - 1)break;
                    brojac++;
                }
            }
        }
    }

    return -1;

}

double& optimised_m_ary_search_evaluation(int k, int m, int* K, int key,int &trenutni,double& koraci)
{
    int mid = -5;
    int low = trenutni;
    int high = k - 1;

    while (low <= high)
    {
        int brojac = 1;
        int dodatak = (high - low + 1) / m;
        int mid = low + dodatak;
        int stari_low = low;
        while (true)
        {
            mid = stari_low + dodatak * brojac;
            koraci++;
            if (K[mid] == key)
            {
                trenutni = mid; return koraci;
            }
            else
            {   koraci++;
                if (K[mid] > key)
                {
                    high = mid - 1; break;
                }
                else
                {
                    low = mid + 1;
                    if (low == high && K[low] > key && low > 0) { trenutni = low - 1; }
                    else if (low == high && K[low] < key && high < k - 1) { trenutni = low + 1; }
                    else if (low == high) { trenutni = low; }
                    if (brojac == m - 1)break;
                    brojac++;
                }
            }
        }
    }

    return koraci;

}

int main()
{     srand(time(NULL));
    int k;
    int* K = nullptr;
    int max;
    int min;


        //Izbor koji zadatak korisnik zeli da radi posto drugi zadatak zavisi od prvog zadatka.
        //Vrednost kljuca od -9999 je uzeta kao granicnik u nizu kljuceva!



        cout << "\n1.Unos uredjenog niza kljuceva K duzine k sa standarnog ulaza ili iz datoteke!\n"
                        "2.Generisanje uredjenog niza kljuceva K sa duzinom k u zadatom opsegu uz pomoc pseudoslucajnih brojeva!\n"
                        "3.Pretragu uredjenog niza K uz pomoc m-arne pretrage!\n"
                        "4.Optimizovanu pretragu uredjenog niza K na niz kljuceva P!\n"
                        "5.Evaluaciju performansi m-arnog pretrazivanja generisanjem sekvence kljuceva u zadatom opsegu\ni odredjivanjem prosecnog broja koraka potrebnog za  pretrazivanje!\n"
                        "6.Evaluaciju performansi optimizovanog m-arnog pretrazivanja generisanjem sekvence kljuceva u zadatom opsegu\ni odredjivanjem prosecnog broja koraka potrebnog za  pretrazivanje!\n"
                        "7.Kraj programa!\n";
                while (true)
                {
                    int datoteka_standardniulaz;
                    cout << endl;
                    cout << "Unesite opciju prvog zadatka:";
                    int opcija_zadatka;
                    cin >> opcija_zadatka;
                    if (opcija_zadatka == 7)break;
                    cout << endl;
                    switch (opcija_zadatka)
                    {
                        case 1:
                            cout << "Da li zelite da unesete podatke putem datoteke (1) ili standarnog ulaza (2):";
                            cin >> datoteka_standardniulaz;
                            if (datoteka_standardniulaz != 2 && datoteka_standardniulaz != 1)
                            {
                                cout << "Los unos!\n";	break;
                            }
                            else
                            {

                                if (datoteka_standardniulaz == 2) {
                                    cout << "Unesite duzinu niza:";

                                    cin >> k;
                                    if (k <= 0) { cout << "Los unos\n"; break; }

                                    if (K != nullptr) delete [] K;
                                    K = new int[k];
                                    cout << "Unesite niz K:";
                                    for (int i = 0; i < k; i++)
                                    {
                                        int broj;
                                        cin >> broj;
                                        K[i] = broj;
                                    }
                                    for (int i = 0; i < k; i++)
                                    {
                                        int broj = K[i];
                                        int indeks = i;
                                        for (int j = i+1; j < k; j++)
                                        {
                                            if (K[j] < broj) { broj = K[j]; indeks = j; }
                                        }
                                        K[indeks] = K[i];
                                        K[i] = broj;
                                    }

                                }
                                else
                                {
                                    string datoteka;
                                    cout << "Unesite ime datoteke:";
                                    cin >> datoteka;
                                    std::ifstream fajl (datoteka);
                                    fajl >> k;
                                    K=new int[k];
                                    for (int i = 0; i < k; i++)
                                    {
                                        int broj;
                                        fajl >> broj;
                                        K[i] = broj;
                                    }
                                    for (int i = 0; i < k; i++)
                                    {
                                        int broj = K[i];
                                        int indeks = i;
                                        for (int j = i+1; j < k; j++)
                                        {
                                            if (K[j] < broj) { broj = K[j]; indeks = j; }
                                        }
                                        K[indeks] = K[i];
                                        K[i] = broj;
                                    }

                                }

                            }
                            break;

                        case 2:
                        {










                                    cout << "Unesite duzinu niza:";

                                    cin >> k;

                                    if (k <= 0) { cout << "Los unos\n"; break; }
                                    cout << endl;
                                    cout << "Unesite opseg iz kojeg zelite da brojevi budu generisani:";
                                    cin >> min >> max;
                                    int broj = min + (rand() % (max-min+1));

                                    if (K != nullptr) delete[] K;
                                    K = new int[k];

                                    for (int i = 0; i < k; i++)
                                    {

                                            broj = min + (rand() % (max-min+1));


                                        K[i] = broj;
                                    }




                                    for (int i = 0; i < k; i++)
                                    {
                                        int broj = K[i];
                                        int indeks = i;
                                        for (int j = i+1; j < k; j++)
                                        {
                                            if (K[j] < broj) { broj = K[j]; indeks = j; }
                                        }
                                        K[indeks] = K[i];
                                        K[i] = broj;
                                    }


                                cout << "Generisani niz:";
                                for (int i = 0; i <k ; ++i) {
                                    cout << K[i] << " ";
                                }
                                cout << endl;

                            break;}

                        case 3:

                        {
                            int m;
                            cout << "Unesite vrednost m:";
                            cin >> m;
                            int key;
                            cout << "Unesite vrednost kljuca koji trazite:";
                            cin >> key;
                            int rezultat = m_ary_search(k, m, K, key);
                            if (rezultat == -1)
                            {
                                cout << "Trazeni broj " << key << " nije pronadjen!";
                                cout << endl;
                            }
                            else
                            {
                                cout << "Trazeni broj " << key << " je pronadjen na poziciji " << rezultat;
                                cout << endl;
                            }
                        }
                            break;



                        case 4:

                        {
                            int trenutni = 0;
                            int* P;
                            int p;

                            cout << "Unesite vrednost p:";
                            cin >> p;
                            P = new int[p];
                            cout << "Unesite uredjeni niz P:";
                            for (int i = 0; i < p; i++)
                            {
                                cin >> P[i];
                            }
                            int m;
                            cout << "Unesite vrednost m:";
                            cin >> m;

                            for (int i = 0; i < k; i++)
                            {
                                int broj = P[i];
                                int indeks = i;
                                for (int j = i + 1; j < p; j++)
                                {
                                    if (P[j] < broj) { broj = P[j]; indeks = j; }
                                }
                                P[indeks] = P[i];
                                P[i] = broj;
                            }

                            for (int i = 0; i < p; i++)
                            {
                                int rezultat = optimised_m_ary_search(k, m, K, P[i], trenutni);
                                if (rezultat == -1)
                                {
                                    cout << P[i] << "-" << "nije pronadjen\n";
                                }
                                else
                                {
                                    cout << P[i] << "-" << rezultat << endl;
                                }
                            }
                        }
                            break;

                        case 5:
                        {
                            double prosek=0;
                            cout << "Unesite duzinu sekvence koju biste zeleli da generisete:";
                            int sekvenca_duzina;
                            int* Sekvenca;
                            cin >> sekvenca_duzina;
                            if (sekvenca_duzina<=0){cout << "Los unos!\n";break;}
                            cout << "Unesite opseg:";
                            cin >> min >> max;
                            int klica = min + (rand() % (max-min+1));
                            if (sekvenca_duzina<=0){cout << "Los unos!\n";break;}
                            cout << "Generisana sekvenca:";
                            Sekvenca= new int [sekvenca_duzina];
                            for (int i = 0; i <sekvenca_duzina ; ++i) {
                                Sekvenca[i]=  min + (rand() % (max-min+1));
                            }
                            for (int i = 0; i < sekvenca_duzina; i++)
                            {
                                int broj = Sekvenca[i];
                                int indeks = i;
                                for (int j = i + 1; j < sekvenca_duzina ; j++)
                                {
                                    if (Sekvenca[j] < broj) { broj = Sekvenca[j]; indeks = j; }
                                }
                                Sekvenca[indeks] = Sekvenca[i];
                                Sekvenca[i] = broj;

                            }
                            for (int i = 0; i < sekvenca_duzina; ++i) {
                                cout << Sekvenca[i] << " ";
                            }
                            cout << endl;

                            if (K==nullptr){ cout << "Niz nije prvo stvoren!\n";break;}
                            for (int m = 2; m < 7; ++m) {
                                prosek=0;
                                for (int i = 0; i <sekvenca_duzina ; ++i) {
                                    m_ary_search_evaluation(k,m,K,Sekvenca[i],prosek);
                                }
                                prosek = prosek / ((double)sekvenca_duzina);
                                cout << "Prosecan broj koraka za m=" << m << " je jednak " << prosek << endl;
                            }
                            break;
                        }
                        case 6:
                            double prosecno=0;
                            int trenutni=0;
                            cout << "Unesite duzinu sekvence koju biste zeleli da generisete:";
                            int sekvenc_duzina;
                            int* Sekvenc;
                            cin >> sekvenc_duzina;
                            cout << "Unesite opseg:";
                            cin >> min >> max;
                            int klica = min + (rand() % (max-min+1));
                            if (sekvenc_duzina<=0){cout << "Los unos!\n";break;}
                            cout << "Generisana sekvenca:";
                            Sekvenc= new int [sekvenc_duzina];
                            for (int i = 0; i <sekvenc_duzina ; ++i) {
                                Sekvenc[i]= min + (rand() % (max-min+1));
                            }
                            for (int i = 0; i < sekvenc_duzina; i++)
                            {
                                int broj = Sekvenc[i];
                                int indeks = i;
                                for (int j = i + 1; j < sekvenc_duzina ; j++)
                                {
                                    if (Sekvenc[j] < broj) { broj = Sekvenc[j]; indeks = j; }
                                }
                                Sekvenc[indeks] = Sekvenc[i];
                                Sekvenc[i] = broj;
                                cout << Sekvenc[i] <<" ";
                            }
                            cout << endl;


                            if (K==nullptr){ cout << "Niz nije prvo stvoren!\n";break;}
                            for (int m = 2; m < 7; ++m) {
                                prosecno=0;
                                for (int i = 0; i <sekvenc_duzina ; ++i) {
                                    optimised_m_ary_search_evaluation(k,m,K,Sekvenc[i],trenutni,prosecno);
                                }
                                prosecno = prosecno / ((double)sekvenc_duzina);
                                cout << "Prosecan broj koraka za m=" << m << " je jednak " << prosecno << endl;
                            }
                            break;
                    }
                }
    }



