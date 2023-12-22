#include <bits/stdc++.h>
#define MAXN 10001
using namespace std;

int cicleLenght(int N){
    while(N%2==0) N/=2;
    while(N%5==0) N/=5;

    if(N==1) return 0;

    int val = 1, S = 0;

    do{
        S++;
        val = (val*10)%N;
    } while(val!=1);

    return S;
}

int main(){
    int T;
    cin>>T;
    int maxCicle[MAXN];
    int maxCicleLenght = 0;
    maxCicle[0] = 1;

    for(int i=1; i<MAXN; i++){
        int cicleOfI = cicleLenght(i);
        if(cicleOfI > maxCicleLenght){
            maxCicleLenght = cicleOfI;
            maxCicle[i] = i;
        }
        else
            maxCicle[i] = maxCicle[i-1];
    }

    for(int i=0; i<T; i++){
        int N;
        cin>>N;
        cout<<maxCicle[N-1]<<endl;
    }
}
