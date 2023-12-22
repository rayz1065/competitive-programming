#include <bits/stdc++.h>

using namespace std;

int n, q;

char s[105];

void init(){
    cin >> n >> q;
    cin >> s;
}

void solve(){
    for(int i = 0; i < q; i++){
        int l, r;
        cin >> l >> r;
        l--, r--;

        bool found = false;

        char firstChar = s[l];
        char lastChar = s[r];

        for(int i = r + 1; i < n; i++)
            if(s[i] == lastChar) found = true;
        for(int i = 0; i < l; i++)
            if(s[i] == firstChar) found = true;

        if(found)
            cout<<"YES";
        else
            cout<<"NO";
        cout<<"\n";
    }
}

int main(){
    int t;
    cin >> t;

    while(t--){
        init();
        solve();
    }
}
