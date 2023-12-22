#include <bits/stdc++.h>

using namespace std;

int n;

string s;

void init(){
    cin >> n;
    cin >> s;
}

string solve(){
    sort(s.begin(), s.end());
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
