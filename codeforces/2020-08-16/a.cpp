#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

typedef unsigned long long int ulli;

int n;
ulli a[MAXN];

void init(){
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> a[i];
}

int solve(){
    int d = a[0];
    for(int i = 1; i < n; i++)
        if(d != a[i]) return 1;
    return n;
}

int main(){
    int t;
    cin >> t;

    while(t--){
        init();
        cout<<solve()<<"\n";
    }
}
