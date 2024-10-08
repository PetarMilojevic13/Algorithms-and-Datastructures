#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct cvor{ int posudice[100][4];
    struct cvor *levi,*desni,*otac;
    int uspesnostpotomka;}CVOR;
int resenjeigrre(int a[100][4],int n){
    for (int i = 0; i <n ; ++i) {
        int boja=a[i][3];
        for (int j = 3; j >=0 ; --j) {
            if (a[i][j]!=boja)return 0;
        }

    }
    return 1;
}
int proverapopunjenostibocice(int a[4]){
    int i;
    for ( i = 0; i <4 ; ++i) {
        if (a[i]==0)return i;}}


int TOPboja(int a[4]){
    int i;
    for (i = 3; i >=0 ; --i) {
        if (a[i]!=0)return a[i];}
    if (i==-1)return 0;
}
int slobodanprostor(int a[4]){
    if (a[3]==0){
        int i;
        for (i = 2; i >=0 ; --i) {
            if (a[i]!=0){break;}
        }
        return 3-i;
    }
    else return 0;
}

int topduzinaboje(int a[4],int boja){
    int pocetak,kraj;
    for (int i = 3; i >=0 ; --i) {
        if (a[i]==boja){pocetak=i;break;}}
    int i;
    for (i = pocetak; i >=0 ; --i) {
        if (a[i]!=boja){break;}}
    kraj=i;
    return pocetak-kraj;
}
int indeksprvogmestasabojomkodubacivanja(int a[4]){
    for (int i = 3; i >=0 ; --i) {
        if (a[i]!=0)return i;}
}
int indeksprvogslobodnogmestaubacivanje(int  a[4]){
    for (int i = 0; i<4 ; ++i) {
        if(a[i]==0)return i;
    }
}
CVOR* pravljenjenovogcvora(CVOR *cvor,int n){
    CVOR *pomocnicvor= calloc(1,sizeof(struct cvor));
    pomocnicvor->levi=1;
    for (int i = 0; i <n ; ++i) {
        for (int j = 0; j <4 ; ++j) {
            (pomocnicvor->posudice[i])[j]=(cvor->posudice[i])[j];
        }}
    return pomocnicvor;}




int main () {
    int provera = 0;
    CVOR *niznajlevljihponivoima[100];

    CVOR *koren;
    int n, k, p;
    printf("Izabrana je pretpostavka da je maksimalni broj ukupnih bocica i maksimalan broj poteza jednak 100!\n");
    printf("Izabrana je pretpostavka da se boje predstavljaju uz pomoc brojeva, kako ne bi morala da se pravi niz\n"
           "za dekodovanje brojeva u slova dobijenih pomocu LKG generatora pseudoslucajnih brojeva!\n");
    printf("Prilikom resavanja igre uzeto je da se prva bocica ima indeks od 0!\n");
    printf("Uzeta je pretpostavka da se u jednom redu u konzoli ispisuje max 3 clana kako bi ispis mogao da bude lep\ni za veci broj bocica!\n");
    printf("Ponudjene opcije:\n");
    printf("1.Generisanje pocetnog stanja i formirarnje stabla ishoda\n");
    printf("2.Ispis izgleda formiranog stabla (formatiran po nivoima)\n");
    printf("3.Korisnik resava igru uz mogucu pomoc pri resavanju\n");
    printf("4.Ispis jednog validnog resenja igre\n");
    printf("5.Kraj izvrsavanja programa\n");
    while (1) {
        int opcija;
        int counter = 0;

        printf("Unesite zeljenu opciju:");
        scanf("%d", &opcija);
        if (opcija == 5) {
            printf("\nZAVRSETAK IGRE\n");
            break;
        }
        switch (opcija) {
            case 1: {
                provera = 1;
                counter += 1;
                if (counter > 0) {for (int i = 0; i < 10; ++i) {
                        niznajlevljihponivoima[i] = calloc(1, sizeof(CVOR));}

                    printf("Unesite parametre n(ukupan broj bocica), k(broj prarznih bocica)\np(maksimalan broj koraka do cilja):");
                    scanf("%d %d %d", &n, &k, &p);

                    // LKG obrada
                    int bojebocice[(n - k) * 4];
                    printf("Prazna pozicija-0\n");
                    for (int i = 0; i < n - k; ++i) {
                        printf("%d. boja-%d\n", i + 1, i + 1);
                    }
                    printf("Generisanje pocetnog stanja i formiranje stabla ishoda!\n");
                    koren = calloc(1, sizeof(struct cvor));
                    koren->desni = pravljenjenovogcvora(koren, n);
                    koren->otac = NULL;
                    koren->levi = 1;
                    // Pravljenje pocetnog niza boja iz kojeg ce se kasnije boje ubacivati u pocice korena

                    for (int i = 0; i < (n - k) * 4; ++i) {
                        bojebocice[i] = 0;
                    }
                    // Postavljanje semena
                    int pocetni = rand();
                    int brojka;
                    // LKG generisanje boja za niz boja
                    for (int i = 1; i < n - k + 1; ++i) {
                        for (int j = 0; j < 4; ++j) {
                            while (1) {
                                brojka = (pocetni * 1664525 + 1013904223) % ((n - k) * 4);
                                if (bojebocice[brojka]!= 0 || brojka<0)pocetni = rand();
                                else {
                                    pocetni = brojka;
                                    break;
                                }
                            }
                            bojebocice[brojka] = i;
                        }
                    }
                    // Punjenje bocica korena
                    for (int i = 0; i < (n - k) * 4; ++i) {
                        koren->posudice[i / 4][i % 4] = bojebocice[i];
                    }

                    //Formiranje stabla ishoda
                    //Stablo ishoda je formirano uz pomoc ulancane reprezentacije m-arnog stabla!

                    CVOR *cvor, *pomocnicvor, *drugipomocni;
                    cvor = koren;
                    int proveranajlevljeg = 0;
                    niznajlevljihponivoima[0] = cvor;


                    // Obrada
                    for (int y = 0; y < p; ++y) {
                        cvor = niznajlevljihponivoima[y];
                        int prvilevi = 0;
                        drugipomocni = pravljenjenovogcvora(cvor, n);
                        if (cvor->desni==NULL) {niznajlevljihponivoima[y+1]=drugipomocni;
                            continue;}
                        while (cvor->desni != NULL) {
                            // Kopiranje sadrzaja cvorar u drugipomocni cvor!
                            for (int i = 0; i < n; ++i) {
                                for (int j = 0; j < 4; ++j) {
                                    (drugipomocni->posudice[i])[j] = (cvor->posudice[i])[j];
                                }
                            }
                            proveranajlevljeg = 0;
                            for (int i = 0; i < n; ++i) {
                                //Provera da li je kombinacija zapravo dobra!
                                int proverakombinacije = 0;

                                for (int j = 0; j < n; ++j) {
                                    int boja = cvor->posudice[j][3];
                                    for (int l = 3; l >= 0; --l) {
                                        if (boja != cvor->posudice[j][l]) {
                                            proverakombinacije = 1;
                                            break;
                                        }
                                    }
                                    if (proverakombinacije == 1)break;
                                }
                                if (proverakombinacije == 0) {
                                    cvor->levi = 1;
                                    break;
                                }
                                else {
                                    //Provera da li je posuda prazna!
                                    if (proverapopunjenostibocice(cvor->posudice[i]) == 0)continue;
                                        // Ubacivanje sina cvora!
                                    else {
                                        int boja;
                                        int duzinaboje;
                                        boja = TOPboja(cvor->posudice[i]);
                                        duzinaboje = topduzinaboje(cvor->posudice[i], boja);
                                        int l;
                                        for (l = 0; l < n; ++l) {
                                            if (l == i)continue;
                                            else if ((TOPboja(cvor->posudice[l]) == boja) &&
                                                     (slobodanprostor(cvor->posudice[l]) >= duzinaboje)) {
                                                int prviindeks = indeksprvogslobodnogmestaubacivanje(cvor->posudice[l]);
                                                pomocnicvor = (CVOR *) pravljenjenovogcvora(cvor, n);
                                                drugipomocni->otac = cvor;
                                                drugipomocni->desni = pomocnicvor;
                                                for (int m = indeksprvogmestasabojomkodubacivanja(
                                                        pomocnicvor->posudice[i]);
                                                     m >
                                                     indeksprvogmestasabojomkodubacivanja(pomocnicvor->posudice[i]) -
                                                     duzinaboje; --m) {
                                                    drugipomocni->posudice[i][m] = 0;
                                                    drugipomocni->posudice[l][prviindeks] = boja;
                                                    prviindeks++;
                                                }
                                                //Provera da li je novo stanje najlevlji sin trenutnog stanja!
                                                if (proveranajlevljeg == 0) {
                                                    cvor->levi = drugipomocni;
                                                    proveranajlevljeg = 1;
                                                }
                                                if (prvilevi == 0) {
                                                    prvilevi = 1;
                                                    niznajlevljihponivoima[y + 1] = drugipomocni;
                                                }
                                                drugipomocni = pomocnicvor;
                                            } else if ((TOPboja(cvor->posudice[l]) == boja) &&
                                                       (slobodanprostor(cvor->posudice[l]) > 0)) {
                                                int duzinaubacivanja = slobodanprostor(cvor->posudice[l]);
                                                int prviindeks = indeksprvogslobodnogmestaubacivanje(cvor->posudice[l]);
                                                pomocnicvor = (CVOR *) pravljenjenovogcvora(cvor, n);
                                                drugipomocni->otac = cvor;
                                                drugipomocni->desni = pomocnicvor;
                                                for (int m = indeksprvogmestasabojomkodubacivanja(cvor->posudice[i]);
                                                     m > indeksprvogmestasabojomkodubacivanja(cvor->posudice[i]) -
                                                         duzinaubacivanja; --m) {
                                                    drugipomocni->posudice[i][m] = 0;
                                                    drugipomocni->posudice[l][prviindeks] = boja;
                                                    prviindeks++;
                                                }
                                                //Provera da li je novo stanje najlevlji sin trenutnog stanja!
                                                if (proveranajlevljeg == 0) {
                                                    cvor->levi = drugipomocni;
                                                    proveranajlevljeg = 1;
                                                }
                                                if (prvilevi == 0) {
                                                    prvilevi = 1;
                                                    niznajlevljihponivoima[y + 1] = drugipomocni;
                                                }
                                                drugipomocni = pomocnicvor;
                                            } else if (TOPboja(cvor->posudice[l]) == 0) {
                                                pomocnicvor = (CVOR *) pravljenjenovogcvora(cvor, n);
                                                drugipomocni->otac = cvor;
                                                drugipomocni->desni = pomocnicvor;
                                                int prviindeks = 0;
                                                for (int m = indeksprvogmestasabojomkodubacivanja(cvor->posudice[i]);
                                                     m > indeksprvogmestasabojomkodubacivanja(cvor->posudice[i]) -
                                                         duzinaboje; --m) {
                                                    drugipomocni->posudice[i][m] = 0;
                                                    drugipomocni->posudice[l][prviindeks] = boja;
                                                    prviindeks = prviindeks + 1;
                                                }
                                                //Provera da li je novo stanje najlevlji sin trenutnog stanja!
                                                if (proveranajlevljeg == 0) {
                                                    cvor->levi = drugipomocni;
                                                    proveranajlevljeg = 1;
                                                }
                                                if (prvilevi == 0) {
                                                    prvilevi = 1;
                                                    niznajlevljihponivoima[y + 1] = drugipomocni;
                                                }
                                                drugipomocni = pomocnicvor;
                                            }
                                        }
                                    }
                                }

                            }
                            //Prelazak na sledeci cvor u istom nivou!

                            cvor = cvor->desni;


                        }

                    }
                    // Trazenje koji cvor u stablu ima potomka koji je resenje igre!
                    CVOR *trenutni;
                    for (int i = p; i > 0; --i) {
                        if (niznajlevljihponivoima[i]->desni == NULL )continue;
                        trenutni = niznajlevljihponivoima[i];
                        cvor = trenutni;
                        while (cvor->desni != NULL) {
                            if (resenjeigrre(cvor->posudice, n) == 1) {
                                while (cvor != NULL) {
                                    cvor->uspesnostpotomka = 1;
                                    cvor = cvor->otac;
                                }

                            }
                            trenutni = trenutni->desni;
                            cvor = trenutni;

                        }
                    }
                    break;
                }
                // Ispisivanje cvorova dobijenih po nivoima (zbog prevelike duzine u odredjenim nivoima su cvorovi istog nivoa rasporedjeni u rarzlicitim redovima!

                case 2: {
                    if (provera == 0) {
                        printf("Morate prvo stvoriti pocetno stablo!\n");
                        break;
                    }
                    else {
                        CVOR *cvor;
                        int brojac = 0;
                        int checker = 0;
                        int i = 0;
                        cvor = niznajlevljihponivoima[i];
                        printf("%d. nivo:\n", 0);
                        for (int j = 3; j >= 0; --j) {
                            for (int l = 0; l < n; ++l) { printf("|%d|", cvor->posudice[l][j]); }
                            putchar('\n');
                        }
                        putchar('\n');
                        CVOR *trenutni;
                        int brojalica = 1;
                        /*for (int j = 1; j <p+1 ; ++j) {
                            trenutni=&niznajlevljihponivoima[j];
                            while(trenutni->otac!=NULL){
                            trenutni=trenutni->desni;
                            brojalica+=1;
                            if (brojalica>6){brojalica=0;break;}
                        }
                        }*/
                        // Ispis ostalih nivoa zajedno sa ispisom ciju su ispisani cvorovi sinovi!
                        CVOR *skupcvorova;
                        for (i = 1; i < p + 1; ++i) {
                            int brojalica = 0;
                            printf("%d. nivo:\n", i);
                            cvor = niznajlevljihponivoima[i];
                            if (cvor->otac == NULL) { break; }
                            while (cvor->otac != NULL) {
                                cvor = cvor->desni;
                                brojalica += 1;
                            }
                            cvor = niznajlevljihponivoima[i];
                            skupcvorova = calloc(brojalica, sizeof(CVOR));
                            for (int j = 0; j < brojalica; ++j) {
                                skupcvorova[j] = *cvor;
                                cvor = cvor->desni;
                            }
                            for (int j = 0; j < brojalica / 3; ++j) {
                                putchar('\n');
                                for (int k = j*3; k <j*3 +3; ++k){
                                    int pozicija=1;
                                    CVOR *pretrazivac=niznajlevljihponivoima[i-1];
                                    while(1){
                                        if (skupcvorova[k].otac == pretrazivac){
                                            printf("Sin %3d.c\t",pozicija);
                                            break;
                                        }
                                        else{pozicija+=1;pretrazivac=pretrazivac->desni;}
                                    }
                                    for (int l = 0; l < n-3; ++l) {
                                        printf("   ");

                                    }
                                }
                                putchar('\n');
                                for (int g = 3; g >= 0; --g) {
                                    for (int l = j * 3; l < j * 3 + 3; ++l) {
                                        for (int m = 0; m < n; ++m) {
                                            printf("|%d|", skupcvorova[l].posudice[m][g]);
                                        }
                                        putchar('\t');
                                    }
                                    putchar('\n');
                                }
                                putchar('\n');
                            }
                            if (brojalica - (brojalica / 3) * 3 > 0) {
                                putchar('\n');
                                for (int j = (brojalica/3)*3; j <brojalica; ++j){
                                    int pozicija=1;
                                    CVOR *pretrazivac=niznajlevljihponivoima[i-1];
                                    while(1){
                                        if (skupcvorova[j].otac == pretrazivac){
                                            printf("Sin %3d.c\t",pozicija);
                                            break;
                                        }
                                        else{pozicija+=1;pretrazivac=pretrazivac->desni;}
                                    }
                                    for (int l = 0; l < n-3; ++l) {
                                        printf("   ");

                                    }
                                }
                                putchar('\n');
                                for (int g = 3; g >= 0; --g) {
                                    for (int j = (brojalica / 3) * 3; j < brojalica; ++j) {
                                        for (int m = 0; m < n; ++m) {
                                            printf("|%d|", skupcvorova[j].posudice[m][g]);
                                        }
                                        putchar('\t');
                                    }
                                    putchar('\n');
                                }
                            }


                        }


                    }
                    putchar('\n');
                    break;
                }
                case 3: {
                    if (provera == 0) {
                        printf("Morate prvo stvoriti pocetno stablo!\n");
                        break;
                    }
                    int stara;
                    int nova;
                    CVOR *sin;
                    CVOR *cvor;
                    cvor=niznajlevljihponivoima[0];
                    int proveraposude[n][4];
                    for (int i = 0; i < 5; ++i) {
                        for (int j = 3; j >=0 ; +--j) {
                            proveraposude[i][j]=0;
                        }
                    }
                    for (int i = 0; i <n ; ++i) {
                        for (int j = 3; j >=0 ; --j) {
                            proveraposude[i][j]=cvor->posudice[i][j];
                        }

                    }
                    int i;
                    for (i = 0; i < p; ++i) {
                        sin =cvor->levi;
                        printf("\nVASE TRENUTNO STANJE:\n");
                        for (int j = 3; j >= 0; --j) {
                            for (int l = 0; l < n; ++l) { printf("|%d|", cvor->posudice[l][j]); }
                            putchar('\n');
                        }
                        putchar('\n');
                        //Provera da li je igra resena!

                        if (resenjeigrre(cvor->posudice, n) == 1) {
                            printf("CESTITAMO RESILI STE IGRU!\n");
                            break;
                        }
                        if (cvor->uspesnostpotomka == 0) {
                            printf("Nazalost dosli ste do stanja iz kojeg nema resenja!\n");
                            break;
                        }
                        // Provera usluzne opcije!
                        int usluznaopcija = 0;
                        printf("Zelite li pomoc pri igru (usluznaopcija=0) ili zelite samo da nastavite da igrate (usluznaopcija=1)!\n");
                        printf("Izaberite opciju:");
                        scanf("%d", &usluznaopcija);
                        if (usluznaopcija == 1){
                            // Izvrsavanje zeljene kombinacije!
                            int proveravac = 0;
                            while (1) {
                                if (proveravac == 1)break;
                                printf("Izaberite kolonu iz koje zelite da izvadite sadrzaj:");
                                scanf("%d", &stara);
                                printf("Izaberite kolonu u koju zelite da stavite sadrzaj:");
                                scanf("%d", &nova);
                                int boja = TOPboja(cvor->posudice[stara]);
                                if (stara == nova) { printf("Nemoguca opcija!\n"); }
                                else if ((TOPboja(cvor->posudice[stara]) == TOPboja(cvor->posudice[nova])) &&
                                         (slobodanprostor(cvor->posudice[nova]) >=
                                          topduzinaboje(cvor->posudice[stara], boja))) {
                                    int prviindeks = indeksprvogslobodnogmestaubacivanje(cvor->posudice[nova]);
                                    for (int m = indeksprvogmestasabojomkodubacivanja(cvor->posudice[stara]);
                                         m > indeksprvogmestasabojomkodubacivanja(cvor->posudice[stara]) -
                                             topduzinaboje(cvor->posudice[stara],
                                                           TOPboja(cvor->posudice[stara])); --m) {
                                        proveraposude[stara][m] = 0;
                                        proveraposude[nova][prviindeks] = boja;
                                        prviindeks++;

                                    }
                                    proveravac = 1;
                                } else if ((TOPboja(cvor->posudice[nova]) == boja) &&
                                           (slobodanprostor(cvor->posudice[nova]) > 0)) {
                                    int duzinaubacivanja = slobodanprostor(cvor->posudice[nova]);
                                    int prviindeks = indeksprvogslobodnogmestaubacivanje(cvor->posudice[nova]);
                                    for (int m = indeksprvogmestasabojomkodubacivanja(cvor->posudice[stara]);
                                         m > indeksprvogmestasabojomkodubacivanja(cvor->posudice[stara]) -
                                             duzinaubacivanja; --m) {
                                        proveraposude[stara][m] = 0;
                                        proveraposude[nova][prviindeks] = boja;
                                        prviindeks++;
                                    }
                                    proveravac = 1;
                                } else if (TOPboja(cvor->posudice[nova]) == 0) {
                                    int prviindeks = 0;
                                    for (int m = indeksprvogmestasabojomkodubacivanja(cvor->posudice[stara]);
                                         m > indeksprvogmestasabojomkodubacivanja(cvor->posudice[stara]) -
                                             topduzinaboje(cvor->posudice[stara], boja); --m) {
                                        proveraposude[stara][m] = 0;
                                        proveraposude[nova][prviindeks] = boja;
                                        prviindeks = prviindeks + 1;
                                    }
                                    proveravac = 1;
                                } else { printf("\nNazalost izabrarli ste neispravan potez!\n"); }
                            }
                            while (1) {
                                proveravac = 1;
                                for (int j = 0; j < n; ++j) {
                                    for (int l = 3; l >= 0; --l) {
                                        if (sin->posudice[j][l] != proveraposude[j][l]) {
                                            proveravac = 0;
                                            break;
                                        }

                                    }
                                    if (proveravac == 0) {
                                        sin = sin->desni;
                                        break;
                                    }

                                }

                                if (proveravac == 1){
                                    cvor=sin;
                                    break;}
                            }
                        } else {
                            while (1) {
                                if (sin->uspesnostpotomka == 1) {
                                    break;
                                }
                                else { sin = sin->desni; }
                            }
                            cvor=sin;
                            for (int j = 0; j < n; ++j) {
                                for (int l = 0; l <4 ; ++l) {
                                    proveraposude[j][l]=cvor->posudice[j][l];
                                }

                            }
                        }
                    }
                    if (i==p){
                        if (resenjeigrre(proveraposude,n)==1){
                            printf("\nCESTITAMO RESILI STE IGRU!\n");
                            for (int j = 3; j >= 0; --j) {
                                for (int l = 0; l < n; ++l)
                                {printf("|%d|", proveraposude[l][j]); }
                                putchar('\n');
                            }

                        }
                        else{printf("\nNAZALOST NISTE RESILI IGRU!\n");
                            for (int j = 3; j >= 0; --j) {
                                for (int l = 0; l < n; ++l)
                                {printf("|%d|", proveraposude[l][j]); }
                                putchar('\n');
                            }
                        }
                    }

                    break;


                }
                case 4: {
                    if (provera == 0) {
                        printf("Morate prvo stvoriti pocetno stablo!\n");
                        break;
                    }
                    putchar('\n');
                    CVOR *cvor;
                    CVOR *put[p+1];
                    int checker = 0;
                    int i;
                    for (i = 0; i < p + 1; ++i) {
                        cvor = niznajlevljihponivoima[i];
                        while (cvor->desni != NULL) {
                            if (cvor->levi == 1 && resenjeigrre(cvor->posudice, n) == 1) {
                                checker = 1;
                                put[i]=cvor;
                                break;
                            } else { cvor = cvor->desni; }
                        }
                        if (checker == 1)break;
                    }
                    if (checker == 0) {
                        printf("Nazalost ne postoji resenje za dati broj od %d poteza!\n", p);
                    } else {
                        for (int j = i - 1; j >= 0; --j) {
                            cvor = cvor->otac;
                            put[j] = cvor;
                        }
                        for (int j = 0; j < i + 1; ++j) {
                            for (int l = 3; l >= 0; --l) {
                                for (int m = 0; m < n; ++m) {
                                    printf("|%d|", put[j]->posudice[m][l]);
                                }
                                putchar('\n');
                            }
                            putchar('\n');
                        }
                    }

                }
            }

        }
    }
}