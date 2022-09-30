#include <bits/stdc++.h>
#define MAXN 105
#pragma GCC optimize ("O3")

#ifndef _WIN32
    #define getchar() getchar_unlocked()
#endif // _WIN32

using namespace std;

typedef long long int lli;

void read_int(lli &n){
    n = 0;
    char c = getchar();
    while(c < '0') c = getchar();
    while(c >= '0')
        n = n * 10 + c - '0', c = getchar();
}

lli gcd(lli a, lli b){
    if(b == 0ll) return a;
    return gcd(b, a%b);
}

lli init(){
    int n;
    cin >> n;

    lli s, a;
    read_int(s);

    while(--n){
        read_int(a);
        s = gcd(s, a);
    }

    return s;
}

struct inff{
    lli val;
    int c;
};

vector<lli> sol;
vector<inff> fattori;

void fattorizza(lli a){
    for(int i = 2; (lli) i*i <= a; i++){
        if(a % i == 0){
            inff curr = {i, 0};
            while(a%i == 0)
                curr.c++, a/= i;
            fattori.push_back(curr);
        }
    }
    if(a != 1ll)
        fattori.push_back({a, 1});
}

void push_sol(int i, lli curr){
    if(i == fattori.size()){
        sol.push_back(curr);
        return ;
    }

    for(int j = 0; j <= fattori[i].c; j++){
        push_sol(i + 1, curr);
        curr*= fattori[i].val;
    }
}

void solve(lli a){
    fattorizza(a);
    push_sol(0, 1ll);
    sort(sol.begin(), sol.end());

    for(auto i:sol)
        cout<<i<<" ";
    cout<<"\n";
}

int main(){
    lli c = init();
    solve(c);
}
