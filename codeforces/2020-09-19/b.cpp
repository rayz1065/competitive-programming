#include <bits/stdc++.h>

using namespace std;

typedef long long int lli;

lli x;

void init(){
    cin >> x;
}

int solve(){
    int c = 0;
    for(int i = 1; i <= 31 && x > 0; i++){
        lli n = (1ll<<i) - 1;
        lli sqrs = n*(n + 1)/2;
        x-= sqrs;
        if(x >= 0) c++;
    }
    return c;
}

int main(){
    int t;
    cin >> t;

    while(t--){
        init();
        cout<<solve()<<"\n";
    }
}
