#include <bits/stdc++.h>
#define MAXN 100005
using namespace std;

int prezzi[MAXN];
int noPay[MAXN], doPay[MAXN];

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);

    int N, E;
    in >> N >> E;
    for(int i = 0; i < N; i++)
        in >> prezzi[i];

    noPay[0] = min(E, prezzi[0] - 1);
    doPay[0] = E - prezzi[0];
    int moneyMax;

    for(int i = 1; i < N; i++){
        moneyMax = max(noPay[i - 1], doPay[i - 1]);
        doPay[i] = moneyMax - prezzi[i];
        noPay[i] = max(doPay[i - 1], min(moneyMax, prezzi[i] - 1));
    }

    cout<<max(doPay[N - 1], noPay[N - 1]);
}
