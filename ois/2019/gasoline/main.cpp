#include <bits/stdc++.h>
#define MAXN 1000005
using namespace std;

int prezzo[MAXN], dist[MAXN];

void fastIn(int &a){
    a = 0;
    char c = getchar_unlocked();
    while(c < '0' || c > '9')
        c = getchar_unlocked();
    while(c >= '0' && c <= '9'){
        a = a*10 + c - '0';
        c = getchar_unlocked();
    }
}

int main(){
    int N;
    fastIn(N);

    for(int i = 0; i < N; i++)
        fastIn(prezzo[i]);
    for(int i = 0; i < N; i++)
        fastIn(dist[i]);

    long long currDist = 0, S = 0;
    int bestPrezzo = prezzo[0];
    for(int i = 0; i < N; i++){
        if(prezzo[i] < bestPrezzo){
            S+= currDist*bestPrezzo;
            currDist = 0, bestPrezzo = prezzo[i];
        }
        currDist+= dist[i];
    }

    cout<<S + currDist*bestPrezzo<<"\n";
}