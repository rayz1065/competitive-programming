#include <cstdio>
#include <iostream>

using namespace std;
int main(){

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int a, liv=1;
    cin>>a;
    liv=(a*(a+1))/2;
    int val[liv], valori[liv], posRim=a;
    for(int i=0; i<liv; i++){
        cin>>valori[i];
    }
    for(int i=liv-1; i>=0; i--){
        if(i+a>liv-1){
            val[i]=valori[i];
        }
        else{
            if(val[i+a]>val[i+a+1]){
                val[i]=val[i+a]+valori[i];
            }
            else{
                val[i]=val[i+a+1]+valori[i];
            }
        }
        posRim--;
        if(posRim==0){
            a--;
            posRim=a;
        }
    }
    cout<<val[0];
}
