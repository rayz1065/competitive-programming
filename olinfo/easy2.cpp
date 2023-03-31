#include <cstdio>
#include <iostream>

using namespace std;
int main(){
    freopen("input.txt", "r", stdin); //usa questa riga di codice per dire "l'input prendilo dal file input.txt (nella stessa directory del file .cpp)"
    freopen("output.txt", "w", stdout); // usa questa riga di codice per dire "l'output scrivimelo nel file output.txt (sempre nella stessa directory"
    int N, a, somma, mas=-1;
    cin>>N;
    for(int cont=0; cont<N; cont++){
        cin>>a;
        cin>>somma;
        somma=somma+a;
        if(somma%2==0&&somma>mas){
            mas=somma;
        }
        else{
            if(mas==somma){
                mas=-1;
            }
        }
    }
    cout<<mas;
}
