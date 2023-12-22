#include <bits/stdc++.h>
#define MAXN 100005
#define MAXB 35

using namespace std;

typedef long long int lli;

int n;
int a[MAXN];
lli sortedForBits[MAXB];

void init(){
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> a[i];
    memset(sortedForBits, 0, sizeof sortedForBits);
}

int lastBit(int x){
    return 32 - __builtin_clz(x);
}

lli solve(){
    for(int i = 0; i < n; i++){
        sortedForBits[lastBit(a[i])]++;
    }

    long long int s = 0;
    for(int i = 0; i < MAXB; i++){
        s+= sortedForBits[i]*(sortedForBits[i] - 1)/2;
    }

    return s;
}

int main(){
    int t;
    cin >> t;

    while(t--){
        init();
        cout<<solve()<<"\n";
    }
}
