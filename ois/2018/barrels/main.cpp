#include <bits/stdc++.h>
#define MAXN 1000005

#ifdef _WIN32
// no getchar_unlocked on Windows so just call getchar
inline int getchar_unlocked() { return getchar(); }
#endif

using namespace std;
int N;
int capi[MAXN];
int libero[MAXN];
int water[MAXN];

int getNext(int barile){
    if(barile > N || capi[barile] > water[barile])
        return barile;
    libero[barile] = getNext(libero[barile]);
    return libero[barile];
}

int pour(int barile, int litri){
    if(barile > N)
        return N + 1;

    int versa = min(capi[barile] - water[barile], litri);
    litri-= versa;
    water[barile]+= versa;
    if(litri > 0 && capi[barile] == water[barile]){
        int next = getNext(libero[barile]);
        next = pour(next, litri);
        libero[barile] = next;
        return libero[barile];
    }
    return barile;
}

void fastscan(int &number){
    register int c;
    number = 0;
    c = getchar_unlocked();
    while(c <= 47)
        c = getchar_unlocked();
    for (; (c>47 && c<58); c=getchar_unlocked())
        number = number*10 + c - 48;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    fastscan(N);
    fastscan(T);
    for(int i = 0; i < N; i++)
        fastscan(capi[i]);

    for(int i = 0; i <= N; i++)
        libero[i] = i + 1;

    char azione;
    int arg1, barile;
    for(int i = 0; i < T; i++){
        azione = getchar();
        fastscan(arg1);
        if(azione == 'P'){
            fastscan(barile);
            pour(barile, arg1);
        }
        else
            printf("%d\n", water[arg1]);
    }
}
