#include <bits/stdc++.h>

using namespace std;

int main(){
    int N;
    long long scambia, inverti, prezzoTot = 0;
    cin>>N>>scambia>>inverti;

    bool lastWasZero = false, foundZeros = false;
    if(scambia > inverti)
        scambia = inverti;

    for(int i = 0; i < N; i++){
        char s;
        cin>>s;
        if(s == '0'){
            if(!lastWasZero && foundZeros)
                prezzoTot+= scambia;
            foundZeros = true;
            lastWasZero = true;
        }
        else if(s == '1' && lastWasZero){
            lastWasZero = false;
        }
    }

    if(foundZeros)
        prezzoTot+= inverti;
    cout<<prezzoTot;
}
