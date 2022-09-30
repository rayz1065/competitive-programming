#include <bits/stdc++.h>
#define MAXN 100005
using namespace std;

int N;
int numeri[MAXN];
int fenwick[MAXN];

void aggiungi(int nodo, int val){
    while(nodo <= N){
        fenwick[nodo]+= val;
        nodo+= nodo & ((~nodo) + 1);
    }
}

int somma(int nodo){
    int S = 0;
    while(nodo > 0){
        S+= fenwick[nodo];
        nodo-= nodo & ((~nodo) + 1);
    }
    return S;
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>N;
    for(int i = 0; i < N; i++)
        cin>>numeri[i];

    for(int i = 0; i < N; i++){
        int precAlPostoGiusto    = somma(numeri[i]);
        ///int numeriCheVannoPrima  = numeri[i] - 1;
        ///int numeriCheVannoDopo   = N - numeri[i];
        int precAlPostoSbagliato = i - precAlPostoGiusto; /// numeri che vanno dopo al pivot ma sono prima
        int dopoAlPostoSbagliato = numeri[i] - 1 - precAlPostoGiusto; /// numeri che vanno prima del pivot ma sono dopo
        cout<<precAlPostoSbagliato + dopoAlPostoSbagliato<<" ";
        aggiungi(numeri[i], 1);
    }
    cout<<endl;
}
