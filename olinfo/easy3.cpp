#include <cstdio>
#include <iostream>

using namespace std;
int main(){
    freopen("input.txt", "r", stdin); //usa questa riga di codice per dire "l'input prendilo dal file input.txt (nella stessa directory del file .cpp)"
    freopen("output.txt", "w", stdout); // usa questa riga di codice per dire "l'output scrivimelo nel file output.txt (sempre nella stessa directory"
    long sommas=-1, masp=0, user, masp2=0, masd=0, masd2=0;
    int N;
    cin>>N;
    for(int cont=0; cont<N; cont++){
        cin>>user;
        if(user%2==0&&user>masp2){
            if(user>masp){
                masp2=masp;
                masp=user;
            }
            else{
                masp2=user;
            }
        }
       if(user%2==1&&user>masd2){
            if(user>masd){
                masd2=masd;
                masd=user;
            }
            else{
                masd2=user;
            }
        }
    }
    if(masp2==0){
        masp=0;
    }
    if(masd2==0){
        masd=0;
    }
    if((masd+masd2)!=(masp+masp2)){
        if((masd+masd2)>(masp+masp2)){
            sommas=masd+masd2;
        }
        if((masd+masd2)<(masp+masp2)){
            sommas=masp+masp2;
        }
    }
    cout<<sommas;
}
