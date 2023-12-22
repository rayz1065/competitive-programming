#include <bits/stdc++.h>
#define MAXN 100005
using namespace std;

typedef long long int lli;
typedef pair<lli, lli> pii;

int n;
lli num[MAXN];
lli sol = 0;

pii extendedEuclidianAlgorithm(lli a, lli b){
    if(a == 0){
        // gcd = b;
        return {0, 1};
    }

    pii nxtSol = extendedEuclidianAlgorithm(b%a, a);
    lli x = nxtSol.second - (b/a)*nxtSol.first;
    lli y = nxtSol.first;

    return {x, y};
}

lli solveDiophantine(lli a, lli m, lli b){
    // a*x - m*y = b
    pii extSol = extendedEuclidianAlgorithm(a, m);
    return extSol.first * b;
}

void init(){
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> num[i];
}

void op(int len, int i, lli val){
    assert(val%len == 0);
    num[i]+= val;
    cout<<val<<" ";
}

void solve(){
    cout<<1<<" "<<n - 1<<"\n";
    for(int i = 0; i < n - 1; i++){
        // cout<<i<<"\t"<<num[i]<<"\t"<<solveDiophantine(n - 1, n, -num[i])<<"\n";
        lli sol = solveDiophantine(n - 1, n, -num[i]) * (n - 1);
        op(n - 1, i, sol);
    }
    cout<<"\n";

    cout<<n<<" "<<n<<"\n";
    op(1, n - 1, -num[n - 1]);
    cout<<"\n";

    cout<<1<<" "<<n<<"\n";
    for(int i = 0; i < n; i++){
        // cout<<i<<"\t"<<num[i]<<"\t"<<solveDiophantine(n - 1, n, -num[i])<<"\n";
        op(n, i, -num[i]);
    }
    cout<<"\n";

    for(int i = 0; i < n; i++)
        assert(num[i] == 0);
}


int main(){
    init();
    solve();
}
