#include <bits/stdc++.h>
#define MAXP 500
#define MAXN 75000
#define DEBUG 1
using namespace std;

long long punti[MAXP];

struct nodo{
    nodo *prima;
    nodo *dopo;
    int marble;
};

void adv(nodo *&ite, int ammonto){
    if(ammonto < 0){
        while(ite != NULL && ammonto < 0){
            ite = ite->prima;
            ammonto++;
        }
    }
    else{
        while(ite != NULL && ammonto > 0){
            ite = ite->dopo;
            ammonto--;
        }
    }
}

void inserisci(nodo *ite, int val){
    nodo *newNodo = new nodo;
    if(newNodo == NULL){
        cout<<"C'e' stato un errore\n";
        exit(1);
    }
    nodo *successivo = ite->dopo;
    newNodo->marble = val;

    successivo->prima = newNodo;

    newNodo->dopo = successivo;
    newNodo->prima = ite;

    ite->dopo = newNodo;
}

void crea(nodo *&nuovo){
    nuovo->prima = nuovo;
    nuovo->dopo = nuovo;
    nuovo->marble = 0;
}

int cancella(nodo *&ite){
    ite->prima->dopo = ite->dopo;
    ite->dopo->prima = ite->prima;
    int v = ite->marble;
    nodo *memo = ite->dopo;
    delete ite;
    ite = memo;
    return v;
}

void stampa(nodo *curr){
    int s = 0;
    nodo *memo = curr;
    while(s++ == 0 || curr != memo){
        cout<<curr->marble<<" "<<((curr->marble < 10)?" ":"");
        curr = curr->dopo;
    }
    cout<<endl;
}

void stampaRelazioni(nodo *curr){
    int s = 0;
    nodo *memo = curr;
    while(s++ == 0 || curr != memo){
        cout<<curr->prima->marble<<" <- "<<curr->marble<<" "<<((curr->marble < 10)?" ":"")<<" -> "<<curr->dopo->marble<<endl;
        curr = curr->dopo;
    }
    cout<<endl;
}

int main(){
    fstream in, out;
    in.open("input9.txt", ios::in);

    char desc[100];
    in.getline(desc, 100);
    int i = 0, P = 0, N = 0;
    while(desc[i] != '\0' && desc[i] >= '0' && desc[i] <= '9')
        P = P*10 + desc[i++] - '0';
    while(desc[i] != '\0' && (desc[i] < '0' || desc[i] > '9'))
        i++;
    while(desc[i] != '\0' && desc[i] >= '0' && desc[i] <= '9')
        N = N*10 + desc[i++] - '0';

    nodo *currNodo = new nodo;
    crea(currNodo);

    long long maxScore = 0;

    int g = -1;
    for(int i = 1; i <= N; i++){
        g = (g + 1)%P;
        if(i%23 == 0){
            adv(currNodo, -7);
            punti[g]+= i + cancella(currNodo);
            maxScore = max(maxScore, punti[g]);
        }
        else{
            adv(currNodo, 1);
            inserisci(currNodo, i);
            adv(currNodo, 1);
        }
    }

    cout<<maxScore<<endl;
}
