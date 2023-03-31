#include <cstdio>
#include <iostream>

using namespace std;
int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int tavolo, toto=0, persone, gemme;
    cin>>gemme;
    cin>>persone;
    tavolo=gemme;
    for(int cont=1;tavolo>0;cont++){
        if(cont>=tavolo){
            toto=toto+tavolo;
            tavolo=0;
        }
        else{
            toto=toto+cont;
            tavolo=tavolo-cont;
        }
        tavolo=tavolo-(persone-1);
    }
    cout<<toto;
}
