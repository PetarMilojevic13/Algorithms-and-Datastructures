#include <iostream>
using namespace std;
#include <queue>
const int MAX=100;
#include <stack>
struct Elem {
    int key;
    Elem *next;
    Elem* left;
    Elem* right;
    Elem* parent;
    Elem(int broj,Elem* levi=nullptr,Elem* desni=nullptr,Elem* otac=nullptr,Elem *sledeci=nullptr):left(levi),right(desni),parent(otac),key(broj),next(sledeci){};
};

queue <Elem*> Q;
queue <Elem*> Ispis;

int LEVEL_ORDER_FORMATTED (Elem* root)
{   Elem* granicnik= nullptr;
    if (root== nullptr){
        return 0;}
    else
    {
        Elem *node;
        int level = 0;
        Q.push(root);
        Q.push(granicnik);
        while (true)
        {
            node = Q.front();


            Q.pop();
            if (node->left != nullptr)
            {
                Q.push(node->left);
            }
            if (node->right != nullptr)
            {
                Q.push(node->right);
            }
            if (Q.front()==nullptr)
            {
                level++;
                Q.pop();
                if (Q.empty())break;
                else Q.push(granicnik);
            }
        }
        return level;
    }
}

void printTree(Elem* root) {
    if (root== nullptr)cout << "Stblo je prazno!" << endl;
    else {

        int i, line_len = 62;
        int first_skip = line_len, in_between_skip;

            Ispis.push(root);



        for( i = 0; i <= LEVEL_ORDER_FORMATTED(root); i++ ) {
            int j = 1 << i, k, l;
            in_between_skip = first_skip;
            first_skip = (first_skip-2)/2;
            for( k = 0; k < first_skip; k++) cout<<" ";
            for(k = 0; k < j; k++) {
                Elem *btn = Ispis.front();
                Ispis.pop();
                if( btn ) {
                    Ispis.push(btn->left);
                    Ispis.push(btn->right);
                } else  {
                    Ispis.push(nullptr);
                    Ispis.push(nullptr);
                }
                if( btn ) {
                    cout << btn->key;
                    Elem *node=btn->next;
                    int count=0;
                    while (node)
                    { count++;
                      node=node->next;
                    }
                   // cout << " Duplikati:" << count;
                }
                else      cout << "  ";
                for( l = 0; l < in_between_skip; l++) cout << " ";
            }
            cout << endl;
            cout << endl;
        }
        while (!Ispis.empty())
        {
            Ispis.pop();
        }
        while (!Q.empty())
        {
            Q.pop();
        }
        cout << endl;
        Q.push(root);
        while (!Q.empty())
        {
            Elem *cvor=Q.front();
            Elem *node=cvor->next;
            int count=0;
            while (node)
            { count++;
                node=node->next;
            }
            cout << "Kljuc " << cvor->key << ":" << count << " duplikata";
            cout <<endl;

            Q.pop();
            if (cvor->left!=nullptr)Q.push(cvor->left);
            if (cvor->right!=nullptr)Q.push(cvor->right);
        }
    }


}



Elem* insert_node(int broj,Elem* root)
{
    Elem *trenutni=root;
    Elem *q=nullptr;
    if (root==nullptr)
    {
        Elem* novi= new Elem(broj);
        root=novi;
    }
    else
    {
        while (true)
        {   if (trenutni==nullptr)break;
            if (trenutni->key==broj)
            {
                int counter=0;
                Elem* novi= new Elem(broj);
                Elem *cvor=trenutni;
                while (cvor->next!=nullptr)
                {
                    cvor=cvor->next;
                }
                cvor->next=novi;
                break;
            }
            else
            {
                if (broj<trenutni->key)
                {
                    q=trenutni;
                    trenutni=trenutni->left;
                }
                else
                {
                    q = trenutni;
                    trenutni = trenutni->right;
                }
            }
        }
        if (trenutni==nullptr)
        {
            Elem* novi= new Elem(broj);
            if (broj < q->key)q->left=novi;
            else q->right=novi;
            novi->parent=q;
        }
    }
    return root;
}

Elem* search_node(int broj, Elem* root)
{
    Elem *trenutni=root;
    while (true)
    {
        if (trenutni==nullptr)break;
        else
        {
            if (broj== trenutni->key)return trenutni;
            else
            {
                if (broj < trenutni->key)
                {
                    trenutni=trenutni->left;
                }
                else
                {
                    trenutni=trenutni->right;
                }
            }
        }
    }
    return trenutni;
}

Elem* search_node_with_step_counter(int broj, Elem* root,double &koraci)
{
    Elem *trenutni=root;
    while (true)
    {
        if (trenutni==nullptr)break;
        else
        {   koraci++;
            if (broj== trenutni->key)return trenutni;
            else
            {
                if (broj < trenutni->key)
                {
                    trenutni=trenutni->left;
                }
                else
                {
                    trenutni=trenutni->right;
                }
            }
        }
    }
    return trenutni;
}

int LKG(int klica, int a, int c, int m)
{
    int X = (a * klica + c) % m;
    return X;
}

void delete_BST_tree(Elem *root)
{
    Q.push(root);
    Elem* node;
    while (true)
    {   if (Q.empty())break;
        node= Q.front();
        Q.pop();
        if (node->left!=nullptr)
        {
            Q.push(node->left);
        }
        if (node->right!=nullptr)
        {
            Q.push(node->right);
        }
        node->left=nullptr;
        node->right=nullptr;
        node->parent=nullptr;
        Elem *cvor=node;
        Elem *brisac=nullptr;
        while (cvor)
        {
            brisac = cvor;
            cvor = cvor->next;
            delete brisac;
        }
    }

}


struct Clan_Stack
        {

            int min;
            int max;
            Clan_Stack(int mini, int  maksi):min(mini),max(maksi){};
        };

stack <Clan_Stack> S;

Elem* FORMATTED_BST(int* K,int k)
{
    int low=0;
    int high=k-1;
    Elem* koren;
    if (k==0)
    {
        koren=nullptr;
        return koren;
    }
    int mid=(low+high)/2;
    koren= new Elem(K[mid]);
    S.push(Clan_Stack(low,mid-1));
    S.push(Clan_Stack(mid+1,high));
    Clan_Stack cvor(0,0);
    while (true)
    {
        cvor=S.top();
        S.pop();
        if (cvor.min>cvor.max)
        {

        }
        else
        {
            mid = (cvor.max + cvor.min) / 2;
            insert_node(K[mid],koren);
            Clan_Stack ubaciti1(cvor.min,mid-1);
            Clan_Stack ubaciti2(mid+1,cvor.max);
            S.push(ubaciti1);
            S.push(ubaciti2);
        }
        if (S.empty())break;
    }
    return koren;
}

int main() {
    srand(time(NULL));
    Elem *root = nullptr;
    int kljuc;
    int* K;
    int k;
    cout << "\n1.Formiranje stabla na osnovu uredjenog niza kljuceva K!\n"
            "2.Umetanje novog kljuca u stablo!\n"
            "3.Pretraga stabla na zadati kljuc!\n"
            "4.Formatiran ispis sadrzaja stabla!\n"
            "5.Evaluaciju performansi pretrazivanja u BST nad nizom kljuceva \n"
            "generisanjem sekvence kljuceva u zadatom opsegu i odredjivanjem prosecnog broja \n"
            "koraka potrebnog za pretrazivanje!\n"
            "6.Brisanje stabla iz memorije!\n"
            "7.Kraj programa!\n";
    while (true) {
        cout << endl;
        cout << "Unesite opciju drugog zadatka:";
        int opcija_zadatka_dva;
        cin >> opcija_zadatka_dva;
        if (opcija_zadatka_dva == 7)break;
        cout << endl;
        switch (opcija_zadatka_dva)
        {
            case 1: // FORMIRANJE STABLA
                cout << "Unesite duzinu uredjenog niza K:";
                cin >> k;
                K = new int [k];
                cout << "Unesite elemente uredjenog niza K:";
                for (int i = 0; i <k ; ++i) {
                    cin >> K[i];
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
                root=FORMATTED_BST(K,k);
                break;
            case 2:

                cout << "Unesite vrednost kljuca koju zelite da ubacite u stablo:";
                cin >> kljuc;
                root = insert_node(kljuc, root);
                break;
            case 3:

                cout << "Unesite vrednost kljuca kojeg zelite da pronadjete u stablu:";
                cin >> kljuc;

                if (search_node(kljuc, root) == nullptr) {
                    cout << "Trazeni kljuc " << kljuc << " nije pronadjen!";
                    cout << endl;
                } else {
                    cout << "Trazeni kljuc " << kljuc << " je pronadjen!";
                    cout << endl;
                }
                break;

            case 4:
            {
                printTree(root);

                break;}
            case 5:
            {   int min;
                int max;
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
                    Sekvenca[i]= min + (rand() % (max-min+1));
                    cout << Sekvenca[i] << " ";
                }
                cout << endl;

                for (int i = 0; i <sekvenca_duzina ; ++i) {
                    search_node_with_step_counter(Sekvenca[i],root,prosek);
                }
                cout << "Prosecan broj koraka je jednak:";
                prosek = prosek / ((double)sekvenca_duzina);
                cout << prosek;
                cout << endl;
                break;
            }
            case 6:
                delete_BST_tree(root);
                root = nullptr;
        }
    }
}




