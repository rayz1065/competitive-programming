#include <bits/stdc++.h>
#define MAXN 1000005
using namespace std;

int freq[MAXN];
int orig[MAXN];

int sommaLeCifre(int N){
    int S = 0;
    while(N > 0){
        S+= N%10;
        N/= 10;
    }
    return S;
}

int enigma(int N){
    int S = N;
    while(N >= 10){
        N = sommaLeCifre(N);
        S+= N;
    }
    return S;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int eMin, eMax;
    cin >> eMin >> eMax;

    for(int i = max(0, eMin - 150); i <= eMax; i++){
        int E = enigma(i);
        if(E >= eMin && E <= eMax){
            freq[E - eMin]++;
            orig[E - eMin] = i;
        }
    }
    for(int i = 0; i <= eMax - eMin; i++){
        if(freq[i] == 0)
            cout<<"IMPOSSIBLE\n";
        else if(freq[i] == 1)
            cout<<orig[i]<<"\n";
        else
            cout<<"AMBIGUOUS\n";
    }
}
