#include <bits/stdc++.h>

using namespace std;

int x, y;

void init(){
    cin >> x >> y;
}

int solve(){
    int am = x + y;
    int diff = abs(x - y);
    if(diff > 1) am+= diff - 1;
    return am;
}

int main(){
    int t;
    cin >> t;

    while(t--){
        init();
        cout<<solve()<<"\n";
    }
}
