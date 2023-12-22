#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

typedef long long int lli;

int n;
lli a[MAXN];

void init(){
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> a[i];
}

lli solve(){
    lli s = 0;
    for(int i = 1; i < n; i++){
        s+= max((lli)0, a[i - 1] - a[i]);
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
