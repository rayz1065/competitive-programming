#include <bits/stdc++.h>
#define MAXGEN 50000
#define MAXN 10000
using namespace std;

long long numeri[MAXN];
long long metaNumeri[MAXN];
long long metaMetaNumeri[MAXN];
long long metaNumeriDaMetaMetaNumeri[MAXN];
long long numeriDaMetaNumeriDaMetaMetaNumeri[MAXN];

int main(){
    fstream in;
    in.open("output12.txt", ios::in);

    int N = 0;
    in>>numeri[N++];
    while(N < MAXN && in >> numeri[N]){
        metaNumeri[N - 1] = numeri[N] - numeri[N - 1];
        N++;
    }

    for(int i = 0; i < 100; i++){
        metaNumeriDaMetaMetaNumeri[i] = metaNumeri[i];
        numeriDaMetaNumeriDaMetaMetaNumeri[i] = numeri[i];
    }
    for(int i = 100; i < MAXGEN; i++){
        metaNumeriDaMetaMetaNumeri[i%MAXN] = metaNumeriDaMetaMetaNumeri[(i - 1)%MAXN] + ((i%2)?-53:55);
        numeriDaMetaNumeriDaMetaMetaNumeri[i%MAXN] = numeriDaMetaNumeriDaMetaMetaNumeri[(i - 1)%MAXN] + metaNumeriDaMetaMetaNumeri[i - 1];
        cout<<numeriDaMetaNumeriDaMetaMetaNumeri[i%MAXN]<<"\t";
    }


    for(int i = 0; i < MAXGEN; i++){
        cout<<i<<" "<<numeri[i]<<" "<<numeriDaMetaNumeriDaMetaMetaNumeri[i]<<" "<<metaNumeri[i]<<" "<<metaNumeriDaMetaMetaNumeri[i]<<"\n";
    }

}
