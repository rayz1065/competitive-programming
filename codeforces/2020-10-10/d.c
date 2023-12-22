#include <bits/stdc++.h>

using namespace std;

int n;

void init(){
    cin >> n;
}

int solve(){
    return 42 + n;
}

int main(){
    int t;
    cin >> t;

    while(t--){
        init();
        cout<<solve()<<"\n";
    }
}
