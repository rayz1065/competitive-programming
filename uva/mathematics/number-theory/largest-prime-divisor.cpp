#include <bits/stdc++.h>
#define MAXP 10000010

using namespace std;

typedef long long int ll;

int sieveSize;
vector<ll> primi;
bitset<MAXP> isP;

void eratostene(int ub){
    sieveSize = ub + 1;
    isP.set();
    isP[0] = isP[1] = false;

    for(int i = 2; i < sieveSize; i++){
        if(isP[i]){
            primi.push_back(i);
            for(ll j = (ll)i*i; j < sieveSize; j+= i)
                isP[j] = false;
        }
    }
}

bool isPrime(ll x){
    if(x < sieveSize)
        return isP[x];
    for(int i = 0; i < primi.size() && (ll)primi[i]*primi[i] <= x; i++){
        if(x%primi[i] == 0)
            return false;
    }
    return true;
}

ll solve(ll x){
    ll N = x;
    int numDiffPf = 0;
    ll S = 0;
    for(int i = 0; i < primi.size() && (ll)primi[i]*primi[i] <= x; i++){
        if(x%primi[i] == 0) numDiffPf++;
        while(x%primi[i] == 0)
            S = max(S, primi[i]), x/= primi[i];
    }
    if(x > 1)
        S = x, numDiffPf++;
    if(N == x || numDiffPf <= 1)
        return 0;
    return S;
}

int main(){
    // fstream out;
    // out.open("output.txt", ios::out);

    eratostene(MAXP - 1);

    ll N;
    cin >> N;

    while(N != 0){
        if(N < 0)
            N = -N;
        ll S = solve(N);
        if(S == N || S == 0)
            cout<<-1<<'\n';
        else
            cout<<S<<"\n";
        cin >> N;
    }
}
