#include <bits/stdc++.h>
#define MAXN 205

using namespace std;

typedef long long int ll;

int n;
char numero[MAXN];

ll memo[MAXN][MAXN];

void init(){
    cin >> numero;
    for(int i = 0; i < MAXN; i++)
        for(int j = 0; j < MAXN; j++)
            memo[i][j] = -1;

    n = strlen(numero);
}

ll _solve(int st_idx, int i, ll curr){
    if(i == n) return curr;
    if(memo[st_idx][i] != -1) return memo[st_idx][i];

    if(curr *10 + numero[i] - '0' > INT_MAX) return memo[st_idx][i] = -1;
    curr = curr * 10 + numero[i] - '0';

    ll s = _solve(i + 1, i + 1, 0ll) + curr;
    s = max(s, _solve(st_idx, i + 1, curr));

    return memo[st_idx][i] = s;
}

ll solve(){
    return _solve(0, 0, 0ll);
}

//#define cout out
//fstream out;

int main(){
    //out.open("output.txt", ios::out);
    int t;
    cin >> t;

    while(t--)
        init(), cout<<solve()<<"\n";
}
