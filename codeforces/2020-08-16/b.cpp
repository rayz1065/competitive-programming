#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

typedef long long int lli;

lli n, k;
lli a[MAXN];

void init(){
    cin >> n >> k;
    for(int i = 0; i < n; i++)
        cin >> a[i];
}

void solve(){
    lli gt = *max_element(a, a + n);
    lli lw = *min_element(a, a + n);

    if(k%2){
        for(int i = 0; i < n; i++)
            a[i] = gt - a[i];
        return ;
    }
    else{
        for(int i = 0; i < n; i++)
            a[i] = a[i] - lw;
        return ;
    }
}

int main(){
    int t;
    cin >> t;

    while(t--){
        init();
        solve();
        for(int i = 0; i < n; i++)
            cout<<a[i]<<" ";
        cout<<"\n";
    }
}
