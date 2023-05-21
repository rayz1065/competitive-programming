#include <bits/stdc++.h>
#define MAXN 26
#define MAXS 200
using namespace std;

typedef unsigned long long int ll;

ll memo[MAXN][MAXS];
int x;

ll solve(int remDicies, int currSum){
    if(remDicies == 0){
        return (currSum >= x);
    }
    if(memo[remDicies][currSum] != -1)
        return memo[remDicies][currSum];

    ll S = 0;
    for(int i = 1; i <= 6; i++){
        S+= solve(remDicies - 1, currSum + i);
    }

    return memo[remDicies][currSum] = S;
}

ll pw(int base, int exp){
    ll S = 1;
    for(int i = 0; i < exp; i++)
        S*= base;
    return S;
}

ll gcd(ll a, ll b){
    return (b == 0)? a : gcd(b, a%b);
}

int main(){
    int N;
    while(cin >> N >> x){
        if(N == 0 && x == 0)
            break ;
        for(int i = 0; i <= N; i++)
            fill(memo[i], memo[i] + MAXS, -1);

        ll S = solve(N, 0), T = pw(6, N), g = gcd(S, T);

        if(S == 0)
            cout<<0<<"\n";
        else if(S == T)
            cout<<1<<"\n";
        else
            cout<<S/g<<"/"<<T/g<<"\n";
    }
}
