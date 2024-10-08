#include <stdio.h>
#include<stdlib.h>
typedef struct { int row,column; double value; } tTuple;
void transponovano(int N,int M ,int numberofnonzero,tTuple *p){
    double transponovana[M][N];
    tTuple *pocetak;
    pocetak=p;
    int counter;
    for (int i=0; i <M ; ++i) {
        for (int j = 0; j < N; ++j) {p=pocetak;counter=0;
            for (int k = 0; k <numberofnonzero ; ++k) {if (p->row==j && p->column==i) {transponovana[i][j]=p->value;break;}else p++;counter++;}
            if (counter==numberofnonzero) transponovana[i][j]=0;}}
    for (int i = 0; i <M; ++i) {
        for (int j = 0; j <N ; ++j) {
            printf("%2.2lf\t",transponovana[i][j]);}printf("\n");}}
int main() { printf("NOTACIJA KOLONA I VRSTA JE UZETA DA POCINJE OD 0\n");
    printf("UBACEN JE I ISPIS COO KAKO IZGLEDA!\n");
    printf("1.Izvriste unos retke matrice zadatih dimenzija i broja nenultih elemenata i njen ispis uz pomoc COO cuvanja elemenata!\n");
    printf("2.Dohvatite vrednost elementa zadate vrste i kolone.\n");
    printf("3.Transponujte matricu.\n");
    printf("4.Kraj programa!\n");
    int pocetnaprovera=0;

    while(1){int opcija;
    int M, N,brojac;
        int numberofnonzero;
        double broj;
        tTuple *Vektor;
        printf("Unesite opciju:");
        scanf("%d",&opcija);
        if (opcija==4)break;
        switch(opcija){
            case 1:
    printf("Unesite broj vrsta matrice N=");
    scanf("%d", &N);
    printf("Unesite broj kolona matrice M=");
    scanf("%d", &M);
    printf("Broj nenultih elemenata je :");
    scanf("%d", &numberofnonzero);
    printf("Unesite elemente matrice\n");
    brojac = 0;
                Vektor= malloc(numberofnonzero* sizeof(tTuple));

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            scanf("%lf", &broj);
            if (broj != 0) {
                tTuple torka = {i, j, broj};
                Vektor[brojac] = torka;
                brojac += 1;
            }
        }
    }
                printf("COO ispis : ");
                printf("[");
                for (int i = 0; i <numberofnonzero-1 ; ++i) {
                    printf("(%d,%d,%.2f) ",Vektor[i].row,Vektor[i].column,Vektor[i].value);}
                printf("(%d,%d,%.2f)",Vektor[numberofnonzero-1].row,Vektor[numberofnonzero-1].column,Vektor[numberofnonzero-1].value);
                printf("]\n");
                printf("Matrica:\n");
                int k = 0;
                for (int i = 0; i < N; ++i) {
                    for (int j = 0; j < M; ++j) {
                        if (Vektor[k].row == i && Vektor[k].column == j) {
                            printf("%2.2lf\t", Vektor[k].value);
                            k += 1;
                        }
                        else printf("%2.2lf\t", 0);
                    }
                    printf("\n");
                }
                printf("\n");
                pocetnaprovera=1;
                break;
            case 2:
        if (pocetnaprovera==0){ printf("Morate prvo izvrsiti unos matrice!\n");break;}
    printf("Unesite pozicije elementa ciju vrednost zelite da dohvatite (vrsta,kolona):");
    int vrsta, kolona, brojacvalue;
    brojacvalue = 0;
    scanf("%d%d", &vrsta, &kolona);
    if ((vrsta>N)||(kolona>M)){printf("Pozicije elementa su izvan matrice!\n");}
    else{
    for (int i = 0; i < numberofnonzero; ++i) {
        if (Vektor[i].row == vrsta && Vektor[i].column == kolona) {
            printf("Vrednost je %2.2lf", Vektor[i].value);
            printf("\n");
            brojacvalue = 1;
            break;
        }
    }
    if (brojacvalue == 0) printf("Vrednost je %2.2lf\n", 0);}

    putchar('\n');
    break;

        case 3:
                if (pocetnaprovera==0){ printf("Morate prvo izvrsiti unos matrice!\n");break;}
            printf("Transponovana matrica:\n");

transponovano(N,M,numberofnonzero,Vektor);
            putchar('\n');}}}

