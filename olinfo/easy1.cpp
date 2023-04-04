#include <cstdio>
#include <iostream>

using namespace std;
int main(){
    freopen("input.txt", "r", stdin);       //usa questa riga di codice per dire "l'input prendilo dal file input.txt (nella stessa directory del file .cpp)"
    freopen("output.txt", "w", stdout);     // usa questa riga di codice per dire "l'output scrivimelo nel file output.txt (sempre nella stessa directory"
    int mas=0,user=0, N=0;
    cin>>N;                                 //n rappresenta il numero di input
    cin>>mas;
    for(int cont=1; cont<N; cont++){        //sarà necessario partire dal primo numero di input e arrivare al ennesimo numero
        cin>>user;                          //i dati vengono inseriti nella variabile temporanea user
        if(user>mas){                       //l'ultimo dato estratto viene confrontato con il valore maggiore al momento
            mas=user;                       //se è maggiore allora questo sarà il dato che verrà confrontato
        }
    }
    cout<<mas;                              //viene mandato un output
}
