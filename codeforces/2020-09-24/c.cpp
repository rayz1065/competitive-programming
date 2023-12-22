#include <bits/stdc++.h>
#define MAXN 300005

using namespace std;

typedef long long int lli;

int n, q;
lli a[MAXN];

void init(){
    cin >> n >> q;
    for(int i = 0; i < n; i++)
        cin >> a[i];

    int l, r;
    for(int i = 0; i < q; i++)
        cin >> l >> r;
}

lli solve(){
    lli bestPos = 0, bestNeg = 0;

    for(int i = 0; i < n; i++){
        lli currBestPos = bestPos, currBestNeg = bestNeg;

        bestNeg = max(currBestNeg, currBestPos + a[i]);
        bestPos = max(currBestPos, currBestNeg - a[i]);

        // cout<<"up to "<<i<<"("<<a[i]<<"): "<<bestPos<<" +?\t"<<bestNeg<<" -?\n";
    }

    return max(bestPos, bestNeg);
}

int main(){
    int t;
    cin >> t;

    while(t--){
        init();
        cout<<solve()<<"\n";
    }
}
