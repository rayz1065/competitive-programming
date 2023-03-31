#include <cstdio>
#include <iostream>

using namespace std;
int main(){
    freopen("input.txt", "r", stdin); //usa questa riga di codice per dire "l'input prendilo dal file input.txt (nella stessa directory del file .cpp)"
    freopen("output.txt", "w", stdout); // usa questa riga di codice per dire "l'output scrivimelo nel file output.txt (sempre nella stessa directory"
    int mas=0 ,user=0, N=0;
    cin>>N;
    for(int cont=0; cont<N; cont++){
        cin>>user;
        if(user>mas){
            mas=user;
        }
    }
    cout<<mas;
}
