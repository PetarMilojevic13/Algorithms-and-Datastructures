#include <stdio.h>
#include<stdlib.h>
#include <string.h>
typedef struct elem {
    int ocena;
    char sifrapredmeta[15];
    struct elem *next, *prev;
} Kruznaulancana;
Kruznaulancana formiranjelistezastudenta(int indeks){
    Kruznaulancana *header;
    header= malloc(sizeof(struct elem));
    header->next=header;
    header->prev=header;
    header->ocena=indeks;
    for (int i = 0; i <15 ; ++i) {(header->sifrapredmeta)[i]='\0';}
    return *header;}

int main (){int N;
    printf("Studenti su predstavljeni u vidu statickog niza!\n");
    printf("Zaglavlje je uzeto kao element ulancane liste kao sto je opisano u udzbeniku!\n");
    printf("Za maksimalnu duzinu sifre je uzeta vrednost 15!\n");
    printf("Upisite maksimalan broj studenata u strukturi:");
    scanf("%d",&N);
    printf("Pri prvom biranju opcija mora biti izabrana opcija 1. za stvaranje novog \nstudenta kako bi dalje bilo moguce obavljanje ostalih opcija!\n");
    int indeksi[N],counter=0;
    Kruznaulancana skup[N];
    //staticki niz indeksa studenata
    printf("Izbor opcija:\n");
    printf("1.Stvaranje novog studenta\n"
           "2.Dodavanje polozenog predmeta za odredjenog studenta\n"
           "3.Prikaz svih predmeta sa odredjenom ocenom za odredjenog studenta\n"
           "4.Ponistavanje (brisanje) polozenog predmeta za odredjenog studenta\n"
           "5.Brisanje cele liste polozenih predmeta za odredjenog studenta\n"
           "6.Dohvatanje broja polozenih predmeta za studenta\n"
           "7.Ispisivanje svih polozenih predmeta odredjenog studenta\n"
           "8.Zavrsetak programa\n"
           "10.Unija predmeta koji su polozili dva zadata studenta\n");
    while (1) {unsigned int opcija,brojindeksa;
        unsigned int brojindeksaprvog,brojindeksadrugog;
        int checkerstudenata,ocena,proverazatrecutacku=0;
        Kruznaulancana *pokazivac,*prvozaglavlje,*drugozaglavlje;
        char sifra[15];
        printf("Unesite zeljenu opciju:");
        scanf("%u",&opcija);
        if (opcija==8)break;
        switch (opcija){
            case 1:
                checkerstudenata=0;
                printf("Unesite indeks novog studenta:");
                scanf("%u",&brojindeksa);
                for (int i = 0; i < counter; ++i) {if (brojindeksa==indeksi[i]){printf("Student sa indeksom %d je vec upisan!\n",brojindeksa);break;} else checkerstudenata+=1;}
                if (checkerstudenata==counter){indeksi[counter]=brojindeksa;Kruznaulancana glava=formiranjelistezastudenta(brojindeksa);
                    skup[counter]=glava; counter+=1;}
                break;
            case 2:
                if (counter==0){ printf("Pri prvom biranju mora biti izabrana opcija 1!\n");break;}
                checkerstudenata=0;
                printf("Unesite indeks\nstudenta za koga zelite da unesete polozeni predmet:");
                scanf("%u",&brojindeksa);
                for (int i = 0; i <counter ; ++i) {if (indeksi[i]==brojindeksa){pokazivac=&skup[i];break;}
                else {checkerstudenata+=1;}}
                if (checkerstudenata==counter)printf("Student sa brojem indeksa %d nije ubacen prethodno!\n",brojindeksa);
                else{
                    printf("Unesite sifru predmeta:");
                    scanf("%s",sifra);
                    printf("Upisite ocenu dobijenu na predmetu:");
                    scanf("%d",&ocena);
                    if (ocena<=5 || ocena>10)printf("Treba ubaciti polozen predmet u listu!\n");
                    else {
                        int duzinastringa;
                        duzinastringa = strlen(sifra);
                        if ((pokazivac->sifrapredmeta[0]) == ((pokazivac->next)->sifrapredmeta[0]))
                        {Kruznaulancana *novipredmet,*lokacijaposle;
                            novipredmet=malloc(sizeof(struct elem));
                            lokacijaposle=(pokazivac->next);
                            (novipredmet->next)=lokacijaposle;
                            (novipredmet->prev)=pokazivac;
                            (pokazivac->next)=novipredmet;
                            pokazivac->prev=novipredmet;
                            lokacijaposle->prev=novipredmet;
                            (novipredmet->ocena)=ocena;
                            for (int i = 0; i <duzinastringa ; ++i) {(novipredmet->sifrapredmeta)[i]=sifra[i];}
                            for (int i = duzinastringa; i <15 ; ++i) {(novipredmet->sifrapredmeta)[i]='\0';}}
                        else {Kruznaulancana *sledeci;
                            sledeci=pokazivac->next;
                            while(1){
                                int duzinastr,provera=0;
                                duzinastr= strlen(sifra);
                                for (int i = 0; i <duzinastringa ; ++i) {if ((sledeci->sifrapredmeta)[i]==sifra[i]){provera+=1;}else break;}
                                if ((strcmp((sledeci->sifrapredmeta),sifra)>0)&&(provera!=duzinastr))
                                {Kruznaulancana *novipredmet;
                                    novipredmet=malloc(sizeof(struct elem));
                                    if ((sledeci->prev)==pokazivac){(pokazivac->next)=novipredmet;novipredmet->prev=pokazivac;}
                                    else {((sledeci->prev)->next)=novipredmet;novipredmet->prev=sledeci->prev;}
                                    novipredmet->next=sledeci;
                                    sledeci->prev=novipredmet;
                                    novipredmet->ocena=ocena;
                                    for (int i = 0; i <duzinastringa ; ++i) {(novipredmet->sifrapredmeta)[i]=sifra[i];}
                                    for (int i = duzinastringa; i <15 ; ++i) {(novipredmet->sifrapredmeta)[i]='\0';}
                                    break;}
                                else if (provera==duzinastr){printf("Predmet je vec ubacen!\n");break;}
                                else if (((sledeci->next)->sifrapredmeta)[0]=='\0'){Kruznaulancana *novipredmet;
                                    novipredmet=malloc(sizeof(struct elem));
                                    sledeci->next=novipredmet;
                                    novipredmet->next=pokazivac;
                                    novipredmet->prev=sledeci;
                                    pokazivac->prev=novipredmet;
                                    novipredmet->ocena=ocena;
                                    for (int i = 0; i <duzinastringa ; ++i) {(novipredmet->sifrapredmeta)[i]=sifra[i];}
                                    for (int i = duzinastringa; i <15 ; ++i) {(novipredmet->sifrapredmeta)[i]='\0';}
                                    break;}
                                else {sledeci=sledeci->next;}}}}
                    putchar('\n');}break;

            case 3:if (counter==0){ printf("Pri prvom biranju mora biti izabrana opcija 1!\n");break;}
                checkerstudenata=0;
                printf("Unesite indeks studenta za koga zelite da prikazete predmete sa odredjenom ocenom:");
                scanf("%u",&brojindeksa);
                for (int i = 0; i <counter ; ++i) {if (indeksi[i]==brojindeksa){pokazivac=&skup[i];break;} else checkerstudenata+=1;}
                if (checkerstudenata==counter)printf("Student sa brojem indeksa %d nije ubacen prethodno!\n",brojindeksa);
                else{
                    printf("Unesite ocenu na osnovu koje trazite polozene predmete:");
                    scanf("%d",&ocena);
                    if (ocena<=5)
                    {printf("Ocena mora biti veca od 5, jer su u listi samo polozeni predmeti!\n");}
                    else if (ocena>10){ printf("Ocena mora biti validna!\n");}
                    else{
                        if (((pokazivac->next)->sifrapredmeta)[0]=='\0'){printf("Lista je prazna!\n");}
                        else{Kruznaulancana *sledeci;
                            int charcounter=0;
                            sledeci=pokazivac->next;
                            while(((sledeci->next)->sifrapredmeta)[0]!='\0'){
                                if ((sledeci->ocena)==ocena){
                                    for (int i = 0; i <15 ; ++i) {if ((sledeci->sifrapredmeta)[i]=='\0')break;
                                        else {printf("%c",(sledeci->sifrapredmeta)[i]);}}
                                    printf("->");proverazatrecutacku=1;sledeci=sledeci->next;}
                                else{sledeci=sledeci->next;}
                            }
                            if ((sledeci->ocena)==ocena){
                                for (int i = 0; i <15 ; ++i) {if ((sledeci->sifrapredmeta)[i]=='\0')break;
                                    else {printf("%c",(sledeci->sifrapredmeta)[i]);}}
                                printf("->");proverazatrecutacku=1;}
                            if (proverazatrecutacku==0){ printf("Ne postoji predmet sa tom ocenom!\n");}
                            else{
                            printf("KRAJ!\n");printf("\n");putchar('\n');}}}}break;

            case 4:
                if (counter==0){ printf("Pri prvom biranju mora biti izabrana opcija 1!\n");break;}
                checkerstudenata=0;
                printf("Unesite indeks studenta za koga zelite da izbrisete odredjeni predmet:");
                scanf("%u",&brojindeksa);
                for (int i = 0; i <counter ; ++i) {if (indeksi[i]==brojindeksa){pokazivac=&skup[i];break;} else checkerstudenata+=1;}
                if (checkerstudenata==counter)printf("Student sa brojem indeksa %d nije ubacen prethodno!\n",brojindeksa);
                else{ int duzinastr;
                    printf("Unesite sifru predmeta koji zelite da obrisete :");
                    scanf("%s",sifra);
                    duzinastr= strlen(sifra);
                    if (((pokazivac->next)->sifrapredmeta)[0]=='\0')
                    { printf("Lista je prazna!\n");}
                    else{int brojaczastring=0;
                        Kruznaulancana *sledeci;
                        sledeci=pokazivac->next;
                        for (int i = 0; i < duzinastr; ++i) {if (((sledeci->sifrapredmeta)[i])==sifra[i]){brojaczastring+=1;}else{break;}}
                        if (brojaczastring==duzinastr){if((pokazivac->prev)==sledeci){
                            pokazivac->next=sledeci->next;
                            pokazivac->prev=pokazivac;break;}
                            else {pokazivac->next=sledeci->next;
                                (sledeci->next)->prev=pokazivac;break;}}

                        while(1) {brojaczastring=0;
                            for (int i = 0; i < duzinastr; ++i) {if (((sledeci->sifrapredmeta)[i])==sifra[i]){brojaczastring+=1;}else{break;}}
                            if (brojaczastring==duzinastr){
                                if (((sledeci->next)->sifrapredmeta)[0]=='\0'){
                                    (sledeci->prev)->next=pokazivac;
                                    (pokazivac->prev)=(sledeci->prev);

                                    break;
                                }
                                else {(sledeci->prev)->next=sledeci->next;
                                    (sledeci->next)->prev=(sledeci->prev);

                                    break;}}
                            else if ((sledeci->ocena)==brojindeksa){
                                printf("Student nije polozio trazeni predmet tako da ne moze ni da bude uklonjen!\n");break;}
                            else{sledeci=sledeci->next;}
                        }
                    }
                }break;

            case 5:
                if (counter==0){ printf("Pri prvom biranju mora biti izabrana opcija 1!\n");break;}
                checkerstudenata=0;
                printf("Unesite indeks studenta za koga zelite da izbrisete predmete:");
                scanf("%u",&brojindeksa);
                for (int i = 0; i <counter ; ++i) {if (indeksi[i]==brojindeksa){pokazivac=&skup[i];break;} else checkerstudenata+=1;}
                if (checkerstudenata==counter){printf("Student sa brojem indeksa %d nije ubacen prethodno!\n",brojindeksa);}
                else{
                    if (((pokazivac->next)->sifrapredmeta)[0]=='\0')
                    { printf("Lista je prazna!\n");}
                    else{
                        Kruznaulancana *sledeci;
                        sledeci=pokazivac->next;
                        while(1){Kruznaulancana *pomocni;
                            pomocni=sledeci;
                            if(((sledeci->next)->sifrapredmeta)[0]=='\0')
                            {
                                pokazivac->next=pokazivac;
                                pokazivac->prev=pokazivac;

                                break;}
                            else{
                                sledeci=sledeci->next;
                                pokazivac->next=sledeci;
                                sledeci->prev=pokazivac;
                                }}}}break;

            case 6:
                if (counter==0){ printf("Pri prvom biranju mora biti izabrana opcija 1!\n");break;}
                checkerstudenata=0;
                printf("Unesite indeks studenta za koga zelite da izracunate broj polozenih predmeta:");
                scanf("%u",&brojindeksa);
                for (int i = 0; i <counter ; ++i) {if (indeksi[i]==brojindeksa){pokazivac=&skup[i];break;} else checkerstudenata+=1;}
                if (checkerstudenata==counter){printf("Student sa brojem indeksa %d nije ubacen prethodno!\n",brojindeksa);}
                else{int brojacpredmeta=0;
                    Kruznaulancana *sledeci;
                    if (((pokazivac->next)->sifrapredmeta)[0]=='\0'){
                        printf("Student nije polozio nijedan predmet!\n");break;}
                    else{brojacpredmeta=1;sledeci=pokazivac->next;}
                    while(1){
                        if (((sledeci->next)->sifrapredmeta)[0]=='\0')
                        { printf("Student sa indeksom %u je polozio %d predmeta\n",brojindeksa,brojacpredmeta);break;}
                        else{brojacpredmeta+=1;sledeci=sledeci->next;}
                    }
                }break;


            case 7:

                if (counter==0){ printf("Pri prvom biranju mora biti izabrana opcija 1!\n");break;}
                printf("Unesite indeks studenta za koga zelite da ispisete polozene predmete:");
                scanf("%u",&brojindeksa);
                checkerstudenata=0;
                for (int i = 0; i <counter ; ++i) {if (indeksi[i]==brojindeksa){pokazivac=&skup[i];break;} else checkerstudenata+=1;}
                if (checkerstudenata==counter){printf("Student sa brojem indeksa %d nije ubacen prethodno!\n",brojindeksa);}
                else{
                    Kruznaulancana *sledeci;
                    if (((pokazivac->next)->sifrapredmeta)[0]=='\0'){
                        printf("Student nije polozio nijedan predmet!\n");break;}
                    else{sledeci=pokazivac->next;}
                    while(1){int duzinastr;
                        duzinastr= strlen(sledeci->sifrapredmeta);
                        if (((sledeci->next)->sifrapredmeta)[0]=='\0')
                        {
                            for (int i = 0; i <duzinastr ; ++i) {printf("%c",(sledeci->sifrapredmeta)[i]);}
                            printf("->KRAJ! \n");
                            break;}
                        else{for (int i = 0; i <duzinastr ; ++i) {printf("%c",(sledeci->sifrapredmeta)[i]);}
                            printf("->");
                            sledeci=sledeci->next;}
                    }
                }break;


            case 10:
                checkerstudenata=0;
                if (counter<2){ printf("Moraju biti stvorena minimum 2 studenta!\n");break;}
                printf("Unesite indeks prvog studenta:");
                scanf("%u",&brojindeksaprvog);
                printf("Unesite indeks drugog studenta:");
                scanf("%u",&brojindeksadrugog);
                for (int i = 0; i <counter ; ++i) {if (indeksi[i]==brojindeksaprvog){prvozaglavlje=&skup[i];break;} else checkerstudenata+=1;}
                if (checkerstudenata==counter){ printf("Student sa indeksom %u nije ubacen!\n",brojindeksaprvog);break;}
                checkerstudenata=0;
                for (int i = 0; i <counter ; ++i) {if (indeksi[i]==brojindeksadrugog){drugozaglavlje=&skup[i];break;} else checkerstudenata+=1;}
                if (checkerstudenata==counter){ printf("Student sa indeksom %u nije ubacen!\n",brojindeksadrugog);break;}
                if (((prvozaglavlje->next)->sifrapredmeta)[0]=='\0'){if(((drugozaglavlje->next)->sifrapredmeta)[0]=='\0'){ printf("Obe liste predmeta su prazne!\n");}
                    else {drugozaglavlje=drugozaglavlje->next;
                        while((drugozaglavlje->sifrapredmeta)[0]!='\0')
                        {printf("%s",(drugozaglavlje->sifrapredmeta));
                            printf("->");drugozaglavlje=drugozaglavlje->next;}printf("KRAJ!\n");}}
                else if (((drugozaglavlje->next)->sifrapredmeta)[0]=='\0'){if(((prvozaglavlje->next)->sifrapredmeta)[0]=='\0'){ printf("Obe liste predmeta su prazne!\n");}
                        else {prvozaglavlje=prvozaglavlje->next;
                            while((prvozaglavlje->sifrapredmeta)[0]!='\0'){printf("%s",(prvozaglavlje->sifrapredmeta));
                                printf("->");prvozaglavlje=prvozaglavlje->next;}printf("KRAJ!\n");}}
                else{Kruznaulancana *unija,*pomocnaveza,*unijazaglavlje;
                    prvozaglavlje=prvozaglavlje->next;
                    drugozaglavlje=drugozaglavlje->next;
                    unija= malloc(sizeof (struct elem));
                    unija->next=unija;
                    unija->prev=unija;
                    for (int i = 0; i <15 ; ++i) {(unija->sifrapredmeta)[i]='\0';}
                    unijazaglavlje=unija;
                    while(1){
                        if((prvozaglavlje->sifrapredmeta)[0]=='\0'){
                            while((drugozaglavlje->sifrapredmeta)[0]!='\0'){
                                pomocnaveza=malloc(sizeof(struct elem));
                                unija->next=pomocnaveza;
                                pomocnaveza->prev=unija;
                                pomocnaveza->next=unijazaglavlje;
                                unija=pomocnaveza;
                                unijazaglavlje->prev=pomocnaveza;
                                for (int i = 0; i <15 ; ++i) {((unija->sifrapredmeta)[i])=((drugozaglavlje->sifrapredmeta)[i]);}
                                unija->ocena=drugozaglavlje->ocena;
                                drugozaglavlje=drugozaglavlje->next;}
                            break;}

                        else if ((drugozaglavlje->sifrapredmeta)[0]=='\0'){while((prvozaglavlje->sifrapredmeta)[0]!='\0'){
                                pomocnaveza=malloc(sizeof(struct elem));
                                unija->next=pomocnaveza;
                                pomocnaveza->prev=unija;
                                pomocnaveza->next=unijazaglavlje;
                                unija=pomocnaveza;
                                unijazaglavlje->prev=pomocnaveza;
                                for (int i = 0; i <15 ; ++i) {((unija->sifrapredmeta)[i])=((prvozaglavlje->sifrapredmeta)[i]);}
                                unija->ocena=prvozaglavlje->ocena;
                                prvozaglavlje=prvozaglavlje->next;}break;}
                        else{
                        if ((strcmp((prvozaglavlje->sifrapredmeta),(drugozaglavlje->sifrapredmeta)))<0){
                            pomocnaveza=malloc(sizeof(struct elem));
                            unija->next=pomocnaveza;
                            pomocnaveza->prev=unija;
                            pomocnaveza->next=unijazaglavlje;
                            unija=pomocnaveza;
                            unijazaglavlje->prev=pomocnaveza;
                            for (int i = 0; i <15 ; ++i) {((unija->sifrapredmeta)[i])=((prvozaglavlje->sifrapredmeta)[i]);}
                            unija->ocena=prvozaglavlje->ocena;
                            prvozaglavlje=prvozaglavlje->next;
                        }
                        else if ((strcmp((prvozaglavlje->sifrapredmeta),(drugozaglavlje->sifrapredmeta)))>0){
                            pomocnaveza=malloc(sizeof(struct elem));
                            unija->next=pomocnaveza;
                            pomocnaveza->prev=unija;
                            pomocnaveza->next=unijazaglavlje;
                            unija=pomocnaveza;
                            unijazaglavlje->prev=pomocnaveza;
                            for (int i = 0; i <15 ; ++i) {((unija->sifrapredmeta)[i])=((drugozaglavlje->sifrapredmeta)[i]);}
                            unija->ocena=drugozaglavlje->ocena;
                            drugozaglavlje=drugozaglavlje->next;
                        }
                        else {pomocnaveza=malloc(sizeof(struct elem));
                            unija->next=pomocnaveza;
                            pomocnaveza->prev=unija;
                            pomocnaveza->next=unijazaglavlje;
                            unija=pomocnaveza;
                            unijazaglavlje->prev=pomocnaveza;
                            for (int i = 0; i <15 ; ++i) {((unija->sifrapredmeta)[i])=((drugozaglavlje->sifrapredmeta)[i]);}
                            unija->ocena=drugozaglavlje->ocena;
                            prvozaglavlje=prvozaglavlje->next;
                            drugozaglavlje=drugozaglavlje->next;
                        }}}
                    unija=unijazaglavlje;
                    unija=unija->next;
                    while((unija->sifrapredmeta)[0]!='\0'){
                        printf("%s->",unija->sifrapredmeta);unija=unija->next;}
                    printf("KRAJ!\n");}}}
    Kruznaulancana *cistac,*cistac2;
    for (int i = 0; i <counter; ++i) {cistac=&skup[i];
        cistac2=cistac->next;
        while((cistac2->ocena)!=indeksi[i])
        {cistac->next=cistac2->next;
            (cistac2->next)->prev=cistac;
            cistac2->ocena=0;
            for (int j = 0; j <15 ; ++j) {cistac2->sifrapredmeta[j]='\0';}
            free(cistac2);
            cistac2=cistac->next;}
        }
    return 0;}