#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define INFINITE 999999999
int ** Upis_grafa(int upis_provera,int *dimenzija) {
    if (upis_provera == 1) {
        printf("\nPrvo morate dealocirati prethodni graf kako ne bi doslo do curenja memorije,pa tek stvoriti novi graf\n");
        return 0;
    }
    else {
        printf("\nUnesite red matrice susednosti koju zelite da stvorite:");
        scanf("%d", dimenzija);
        int **matrix_susednosti = calloc(*dimenzija, sizeof(int *));
        for (int i = 0; i < *dimenzija; ++i) {
            matrix_susednosti[i] = calloc(*dimenzija, sizeof(int));
        }
        for (int i = 0; i <*dimenzija ; ++i) {
            for (int j = 0; j <*dimenzija ; ++j) {
                matrix_susednosti[i][j]=0;
            }
        }

        return matrix_susednosti;
    }
}

void node_adder_deleter(int **matrica,int *dimenzija,int *zaglavlja)
{   int cvor_opcija;
    printf("\nUnesite zeljenu opciju:\n "
           "1.Ubacivanje cvora\n"
           "2.Uklanjanje cvora\n");
    printf("Opcija:");
    scanf("%d",&cvor_opcija);
    if (cvor_opcija==1) {  int ubacivanje_opcija;
        printf("Unesite gde zelite da dodate novi cvor:\n");
        printf("1.Ubacivanje prethodno obrisanog cvora u okviru liste\n");
        printf("\n2.Ubacivanje cvora na kraj liste i time stalno povecanje dimenzije matrice za 1\nradi lakseg baratanja operacijama matrice susednosti\n");
        printf("Opcija:");
        scanf("%d",&ubacivanje_opcija);
        if (ubacivanje_opcija==1){
        printf("\nMaksimalna vrednost(indeks) cvora je jednak %d\n", (*dimenzija) - 1);
        printf("\nUnesite indeks (vrednost) cvora koju zelite da ubacite u matricu susednosti:");
        int indeks;
        scanf("%d", &indeks);
        if (indeks < 0)printf("\nLOS INDEKS!\n");
        else if (indeks >= *dimenzija)printf("\nIndeks je veci od dimenzija date matrice!\n");
        else {
            if (*(zaglavlja+indeks) != 0) { printf("\nCvor sa indeksom i vrednoscu %d je vec ubacen\n", indeks); }
            else {
                zaglavlja[indeks] = 1;
                for (int i = 0; i < *dimenzija; ++i) {
                    matrica[indeks][i] = 0;
                    matrica[i][indeks] = 0;
                }
            }
        }
    }
    else{
        int dime=*dimenzija;
        *dimenzija=(*dimenzija)+1;
    }
    }
    else if (cvor_opcija==2)
    {   int brisanje_opcija;
        printf("\nUnesite gde zelite da obrisete novi cvor:\n");
        printf("\n1.Brisanje prethodno obrisanog cvora u okviru liste\n");
        printf("\n2.Brisanje cvora na kraj liste i time stalno povecanje dimenzije matrice za 1\nradi lakseg baratanja operacijama matrice susednosti\n");
        printf("Opcija:");
        scanf("%d",&brisanje_opcija);
        if (brisanje_opcija==1){
        printf("\nMaksimalna vrednost(indeks) cvora je jednak %d\n",(*dimenzija)-1);
        printf("\nUnesite indeks (vrednost) cvora koju zelite da obrisete iz matricu susednosti:");
        int indeks;
        scanf("%d",&indeks);
        if (indeks<0)printf("\nLOS INDEKS!\n");
        else if (indeks>=*dimenzija)printf("\nIndeks je veci od dimenzija date matrice!\n");
        else {
            if (zaglavlja[indeks]==0){ printf("\nCvor sa indeksom i vrednoscu %d ne postoji\n",indeks);}
            else {zaglavlja[indeks]=0;
                for (int i = 0; i <*dimenzija ; ++i) {
                    matrica[indeks][i]=0;
                    matrica[i][indeks]=0;
                }
            }
        }
        }
        else
        {   int dime=*dimenzija;
            *dimenzija=dime-1;
        }


    }
    else {printf("Lose unesena opcija!\n");}
}

void Grana_maker_deleter(int **matrica,int *dimenzija,int *zaglavlja)
{
    int grana_opcija;
    printf("\nUnesite zeljenu opciju: "
           "1.Ubacivanje grane\n"
           "2.Uklanjanje grane\n");
    printf("Opcija:");
    scanf("%d",&grana_opcija);
    if (grana_opcija==1)
    {   printf("\nMaksimalna vrednost(indeks) cvora je jednak %d\n",(*dimenzija)-1);
        printf("\nUnesite indeks(vrednost) cvora ciju izlaznu granu zelite da dodate:");
        int indeks_izlazni;
        scanf("%d",&indeks_izlazni);
        if (indeks_izlazni<0)printf("LOS INDEKS!\n");
        else if (zaglavlja[indeks_izlazni]==0){printf("\nCvor sa indeksom %d nije prvo dodat u graf!\n",indeks_izlazni);}
        else if (indeks_izlazni>=*dimenzija)printf("\nIndeks je veci od dimenzija date matrice!\n");
        else {
            printf("\nUnesite indeks(vrednost) cvora ciju ulaznu granu zelite da dodate:");
            int indeks_ulazni;
            scanf("%d",&indeks_ulazni);
            if (indeks_ulazni<0)printf("LOS INDEKS!\n");
            else if (zaglavlja[indeks_ulazni]==0){printf("\nCvor sa indeksom %d nije prvo dodat u graf!\n",indeks_ulazni);}
            else if (matrica[indeks_izlazni][indeks_ulazni]==1){printf("\nGrana je vec ubacena\n");}
            else {matrica[indeks_izlazni][indeks_ulazni]=1;}
        }
    }
    else if (grana_opcija==2)
    {
        printf("\nMaksimalna vrednost(indeks) cvora je jednak %d\n",(*dimenzija)-1);
        printf("\nUnesite indeks(vrednost) cvora ciju izlaznu granu zelite da izbrisete:");
        int indeks_izlazni;
        scanf("%d",&indeks_izlazni);
        if (indeks_izlazni<0)printf("\nLOS INDEKS!\n");
        else if (zaglavlja[indeks_izlazni]==0){printf("\nCvor sa indeksom %d nije prvo dodat u graf!\n");}
        else if (indeks_izlazni>=*dimenzija)printf("\nIndeks je veci od dimenzija date matrice!\n");
        else {
            printf("\nUnesite indeks(vrednost) cvora ciju ulaznu granu zelite da izbrisete:");
            int indeks_ulazni;
            scanf("%d",&indeks_ulazni);
            if (indeks_ulazni<0)printf("LOS INDEKS!\n");
            else if (zaglavlja[indeks_ulazni]==0){printf("\nCvor sa indeksom %d nije prvo dodat u graf!\n",indeks_ulazni);}
            else if (matrica[indeks_izlazni][indeks_ulazni]==0){printf("\nGrana ne postoji\n");}
            else {matrica[indeks_izlazni][indeks_ulazni]=0;}
        }
    }
    else {printf("\nLosa opcija\n");}
}

void Ispis_reprezentacije_grafa(int **matrica,int *zaglavlja,int *dimenzija)
{

    for (int i = 0; i <*dimenzija ; ++i)
    {
        if (zaglavlja[i]==1)
        {
            printf("%d-cvor: ",i);
            for (int j = 0; j <*dimenzija ; ++j) {
                printf("%d ",matrica[i][j]);
            }
            putchar('\n');
        }
        else
        {
            printf("%d-cvor ne postoji u grafu!\n",i);
        }
    }

}

void Brisanje_reprezentacije(int **matrica,int *dimenzija,int *zaglavlja)
{
    for (int i = 0; i <*dimenzija ; ++i) {
        free(matrica[i]);
    }
    free(matrica);
    free(zaglavlja);
}


int main(){
    int opcija;
    int upis=0;
    int **matrica_prvideo=0;
    int *zaglavljacvorovi=0;
    int *dimenzija=calloc(1,sizeof(int));

    printf("INDEKSIRANJE JE UZETO DA SE OBAVLJA OD VREDNOSTI 0\n");



    printf("DEKLARACIJA IZBORA OPCIJA:\n");
    printf("1.Kreiranje praznog grafa zadatih dimenzija\n");
    printf("2.Dodavanje cvora u graf i uklanjanje cvora iz grafa\n");
    printf("3.Dodavanje i uklanjanje grana izmedju dva cvora u grafu\n");
    printf("4.Ispis reprezentacije grafa\n");
    printf("5.Brisanje grafa iz memorije\n");
    printf("6.Prelazak na drugi deo zadatka i zatim zavrsavanje programa\n");
    printf("7.Zavrsetak rada programa\n");

    while (1)

    {

        printf("\nUnesite zeljenu opciju:");
        scanf("%d",&opcija);
        if (opcija==7)break;

        switch (opcija){
            case 1:
                if (upis==1){printf("\nPrvo morate dealocirati prethodni graf kako ne bi doslo do curenja memorije,pa tek stvoriti novi graf\n");}
                else{
                    matrica_prvideo=Upis_grafa(upis,dimenzija);
                    zaglavljacvorovi= calloc(*dimenzija,sizeof(int));
                    for (int i = 0; i <*dimenzija ; ++i) {
                        zaglavljacvorovi[i]=1;
                    }
                    upis=1;}
                break;


            case 2:
                if (upis==0)printf("\nPrvo morate kreirati graf kako biste mogli da dodajete cvorove u njega\n");
                else
                {   int pret_dim=*dimenzija;
                    node_adder_deleter(matrica_prvideo,dimenzija,zaglavljacvorovi);
                    if (pret_dim<*dimenzija) {
                        int dime = *dimenzija - 1;
                        int *nova_zaglavlja = calloc(dime + 1, sizeof(int));
                        for (int i = 0; i < (*dimenzija) - 1; ++i) {
                            nova_zaglavlja[i] = zaglavljacvorovi[i];
                        }
                        nova_zaglavlja[dime] = 1;
                        free(zaglavljacvorovi);
                        zaglavljacvorovi = 0;
                        zaglavljacvorovi = nova_zaglavlja;

                        int **nova_matrica = calloc(*dimenzija, sizeof(int *));
                        for (int i = 0; i < *dimenzija; ++i) {
                            nova_matrica[i] = calloc(*dimenzija, sizeof(int));
                        }
                        for (int i = 0; i < (*dimenzija) - 1; ++i) {
                            for (int j = 0; j < (*dimenzija) - 1; ++j) {
                                nova_matrica[i][j] = matrica_prvideo[i][j];
                            }
                        }
                        for (int i = 0; i < *dimenzija; ++i) {
                            nova_matrica[i][(*dimenzija) - 1] = 0;
                            nova_matrica[(*dimenzija) - 1][i] = 0;
                        }
                        for (int i = 0; i < (*dimenzija) - 1; ++i) {
                            free(matrica_prvideo[i]);
                        }
                        free(matrica_prvideo);
                        matrica_prvideo = 0;
                        matrica_prvideo = nova_matrica;
                    }
                    else if (pret_dim>*dimenzija)
                    {
                        int dime = *dimenzija;
                        int *nova_zaglavlja = calloc(dime, sizeof(int));
                        for (int i = 0; i < dime; ++i) {
                            nova_zaglavlja[i] = zaglavljacvorovi[i];
                        }
                        free(zaglavljacvorovi);
                        zaglavljacvorovi = 0;
                        zaglavljacvorovi = nova_zaglavlja;

                        int **nova_matrica = calloc(dime, sizeof(int *));
                        for (int i = 0; i < dime; ++i) {
                            nova_matrica[i] = calloc(dime, sizeof(int));
                        }



                        for (int i = 0; i < dime; ++i) {
                            for (int j = 0; j <dime ; ++j) {
                                nova_matrica[i][j] = matrica_prvideo[i][j];
                            }}

                        for (int i = 0; i < (*dimenzija) + 1; ++i) {
                            free(matrica_prvideo[i]);
                        }
                        free(matrica_prvideo);
                        matrica_prvideo = 0;
                        matrica_prvideo = nova_matrica;
                    }
                }
                break;
            case 3:
                if (upis==0)printf("\nPrvo morate kreirati graf kako biste mogli da dodajete grane u njega\n");
                else{Grana_maker_deleter(matrica_prvideo,dimenzija,zaglavljacvorovi);}
                break;

            case 4:
                if (upis==0)printf("\nPrvo morate kreirati graf kako biste mogli da dodajete grane u njega\n");
                else{Ispis_reprezentacije_grafa(matrica_prvideo,zaglavljacvorovi,dimenzija);}
                break;

            case 5:
                if (upis==0)printf("\nPrvo morate kreirati graf kako biste mogli da ga obrisete\n");
                else{Brisanje_reprezentacije(matrica_prvideo,dimenzija,zaglavljacvorovi);
                    matrica_prvideo=0;
                    zaglavljacvorovi=0;
                    upis=0;}
                break;
            case 6:
            {
                FILE *datoteka;
                char ime_fajla[100];
                printf("\nUnesite ime datoteke:");
                scanf("%s",ime_fajla);
                datoteka=fopen(ime_fajla,"r");
                char *format="%d";

                // Ucitavanje grafa dugovanja iz ulazne datoteka!


                int n;
                fscanf(datoteka,format,&n);
                int **matrica=calloc(n,sizeof(int*));
                char provera= fgetc(datoteka);
                for (int i = 0; i <n ; ++i) {matrica[i]=calloc(n,sizeof(int));}
                for (int i = 0; i <n ; ++i) {
                    int broj;

                    for (int j = 0; j < n; ++j) {
                        fscanf(datoteka,format,&broj);
                        matrica[i][j]=broj;
                        provera=fgetc(datoteka);
                    }
                }

// Zavrsetak ucitavanja grafa dugovanja iz tekstualne datoteke!

// Pronalazak i ispis ciklusa u grafu uz pomoc Warshallovog algoritma!

                int susednosti[n][n];
                for (int i = 0; i < n; ++i) {
                    for (int j = 0; j < n; ++j) {
                        if (matrica[i][j]>0){susednosti[i][j]=1;}
                        else {susednosti[i][j]=0;}
                    }
                }


                for (int k = 0; k <n ; ++k) {
                    for (int i = 0; i <n ; ++i) {
                        for (int j = 0; j <n ; ++j) {
                            susednosti[i][j]=susednosti[i][j] || (susednosti[i][k] && susednosti[k][j]);
                        }
                    }
                }


                int **ciklusi_nizovi=0;
                int ciklusi_brojac=0;
                for (int i = 0; i <n ; ++i) {
                    if (susednosti[i][i]==1)ciklusi_brojac++;
                }
                ciklusi_nizovi= realloc(ciklusi_nizovi,ciklusi_brojac*sizeof(int*));
                for (int i = 0; i <ciklusi_brojac ; ++i) {
                    ciklusi_nizovi[i]=0;
                }
                int w[n][n];
                for (int i = 0; i <n ; ++i) {
                    for (int j = 0; j <n ; ++j) {
                        if (i==j)w[i][j]=0;
                        else if (matrica[i][j]>0){w[i][j]=matrica[i][j];}
                        else w[i][j]=INFINITE;
                    }
                }
                int t[n][n];
                for (int i = 0; i < n; ++i) {
                    for (int j = 0; j <n ; ++j) {
                        if (i==j || w[i][j]==INFINITE)t[i][j]=0;
                        else t[i][j]=i+1;
                    }
                }
                int d[n][n];
                for (int i = 0; i <n ; ++i) {
                    for (int j = 0; j <n ; ++j) {
                        d[i][j]=w[i][j];
                    }
                }

                for (int k = 0; k <n ; ++k) {
                    for (int i = 0; i <n ; ++i) {
                        for (int j = 0; j <n ; ++j) {
                            if (d[i][j]>d[i][k]+d[k][j])
                            {
                                t[i][j]=t[k][j];
                                d[i][j]=d[i][k]+d[k][j];
                            }

                        }}}



                int m=0;
                int stek[100];
                for (int i = 0; i <100 ; ++i) {
                    stek[i]=0;
                }
                for (int i = 0; i <n ; ++i) {
                    if (susednosti[i][i]==1)
                    {
                        for (int j = 0; j <n ; ++j) {
                            if (i!=j && t[i][j]>0 && matrica[j][i]>0)
                            {   int g=0;
                                ciklusi_nizovi[m]=realloc(ciklusi_nizovi[m],(g+1)*sizeof(int));
                                int prvi=i;
                                int drugi=j;
                                ciklusi_nizovi[m][g]=prvi+1;
                                while (1)
                                {
                                    if (prvi+1==t[prvi][drugi])break;
                                    stek[g]=t[prvi][drugi];
                                    g++;
                                    drugi=t[prvi][drugi]-1;

                                }
                                ciklusi_nizovi[m]= realloc(ciklusi_nizovi[m],(g+3)*sizeof(int));
                                int q=1;
                                for (int h = g-1; h >=0 ; --h) {
                                    ciklusi_nizovi[m][q]=stek[h];
                                    q++;
                                }
                                ciklusi_nizovi[m][q]=j+1;
                                ciklusi_nizovi[m][q+1]=0;
                                for (int k = 0; k <100 ; ++k) {
                                    stek[k]=0;
                                }

                            }
                        }
                        m++;
                    }
                }

                int indeks_trenutni=0;
                int duzina_ciklusovi=0;
                for (int i = 0; i <ciklusi_brojac ; ++i) {
                    if (i==0){duzina_ciklusovi++;}
                    else {
                        int Indeks_duzina=0;
                        int potencijalni_duzina=0;
                        while (1){if(ciklusi_nizovi[indeks_trenutni][Indeks_duzina]==0)break;Indeks_duzina++;}
                        while (1){if (ciklusi_nizovi[i][potencijalni_duzina]==0)break;potencijalni_duzina++;}
                        if (potencijalni_duzina!=Indeks_duzina){duzina_ciklusovi++;indeks_trenutni=i;}
                        else {
                            int provera=0;
                            for (int j = 0; j <Indeks_duzina ; ++j) {
                                int brojka=ciklusi_nizovi[indeks_trenutni][j];
                                for (int k = 0; k <potencijalni_duzina ; ++k) {
                                    if (brojka==ciklusi_nizovi[i][k]){provera=1;break;}
                                }
                                if (provera==1)break;
                            }
                            if (provera==0){duzina_ciklusovi++;indeks_trenutni=i;}

                        }
                    }}
                int indeksi_ciklusa[duzina_ciklusovi];
                int q=0;
                for (int i = 0; i <ciklusi_brojac ; ++i) {
                    if (i==0){indeksi_ciklusa[q]=i;q++;indeks_trenutni=i;}
                    else {
                        int Indeks_duzina=0;
                        int potencijalni_duzina=0;
                        while (1){if(ciklusi_nizovi[indeks_trenutni][Indeks_duzina]==0)break;Indeks_duzina++;}
                        while (1){if (ciklusi_nizovi[i][potencijalni_duzina]==0)break;potencijalni_duzina++;}
                        if (potencijalni_duzina!=Indeks_duzina){indeksi_ciklusa[q]=i;q++;indeks_trenutni=i;}
                        else {
                            int provera=0;
                            for (int j = 0; j <Indeks_duzina ; ++j) {
                                int brojka=ciklusi_nizovi[indeks_trenutni][j];
                                for (int k = 0; k <potencijalni_duzina ; ++k) {
                                    if (brojka==ciklusi_nizovi[i][k]){provera=1;break;}
                                }
                                if (provera==1)break;
                            }
                            if (provera==0){indeksi_ciklusa[q]=i;q++;}

                        }
                    }}

                printf("\nCIKLUSI:\n");
                putchar('\n');
                for (int i = 0; i < duzina_ciklusovi; ++i) {
                    int h=0;
                    int indeks=indeksi_ciklusa[i];
                    while (1){if (ciklusi_nizovi[indeks][h]==0)break;
                        h++;}
                    for (int j = 0; j <h ; ++j) {
                        printf("%d",ciklusi_nizovi[indeks][j]);
                        if (j<h-1)printf("->");
                    }
                    putchar('\n');
                }
                putchar ('\n');

                // Zavrsetak pronalazenja CIKLUSA U GRAFU!


// Pronalazenje najveceg moguceg novcanog iznosa koji je moguce kompenzovati za svaki pronadjeni ciklus;

                for (int i = 0; i <duzina_ciklusovi ; ++i) {
                    int h=0;
                    int indeks=indeksi_ciklusa[i];
                    while (1){if(ciklusi_nizovi[indeks][h]==0)break;h++;}
                    printf("ZA CIKLUS: ");
                    for (int j = 0; j <h ; ++j) {
                        printf("%d",ciklusi_nizovi[indeks][j]);
                        if (j<h-1)printf("->");
                    }
                    int brojka_prva=ciklusi_nizovi[indeks][0];
                    int brojka_druga=ciklusi_nizovi[indeks][h-1];
                    int minimum=matrica[brojka_druga-1][brojka_prva-1];
                    for (int j = 0; j <h-1 ; ++j) {
                        brojka_prva=ciklusi_nizovi[indeks][j];
                        brojka_druga=ciklusi_nizovi[indeks][j+1];
                        if (matrica[brojka_prva-1][brojka_druga-1]<minimum){minimum=matrica[brojka_prva-1][brojka_druga-1];}
                    }
                    printf(" Trazeni maksimalni iznos je jednak %d evra\n",minimum);
                    // Obrada i izvrsavanje kompenzacije u matrici susednosti!

                    brojka_prva=ciklusi_nizovi[indeks][0];
                    brojka_druga=ciklusi_nizovi[indeks][h-1];
                    matrica[brojka_druga-1][brojka_prva-1]= matrica[brojka_druga-1][brojka_prva-1]-minimum;
                    for (int j = 0; j <h-1 ; ++j) {
                        brojka_prva=ciklusi_nizovi[indeks][j];
                        brojka_druga=ciklusi_nizovi[indeks][j+1];
                        matrica[brojka_prva-1][brojka_druga-1]=matrica[brojka_prva-1][brojka_druga-1]-minimum;
                    }


                }
                putchar('\n');
                // STAMPANJE NOVE MATRICE SUSEDNOSTI NAKON IZVRSENE KOMPENZACIJE!

                printf("NOVA MATRICA SUSEDNOSTI:\n");
                putchar('\n');

                for (int i = 0; i <n ; ++i) {
                    for (int j = 0; j < n; ++j) {
                        printf("%d",matrica[i][j]);
                        if (j<n-1)putchar(' ');
                    }
                    putchar('\n');
                }
                fclose(datoteka);
                //printf("\nZAVRSETAK PROGRAMA\n");
                //exit(0);

            }
        }
    }
    printf("\nZAVRSETAK PROGRAMA\n");

}