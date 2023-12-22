#include <bits/stdc++.h>
#define MAXN 100000005

using namespace std;

int n;

void init(){
    cin >> n;
}

int solve(){
    if(n == 1) return 0;
    if(n == 2) return 1;

    if(n%2 == 0 || n == 3) return 2;
    return 3;
}

int main(){
    int t;
    cin >> t;

    while(t--){
        init();
        cout<<solve()<<"\n";
    }
}
