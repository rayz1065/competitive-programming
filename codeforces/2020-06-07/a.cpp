#include <bits/stdc++.h>
#define MAXN 105

using namespace std;

int n;

int values[MAXN];

void init(){
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> values[i];
}

void solve(){
    for(int i = 0; i < n; i++)
        values[i] = abs(values[i]);

    for(int i = 2; i < n; i+= 2){
        int a = i, b = i - 1;
        if((values[a] - values[a - 1] < 0 && values[b] - values[b - 1] < 0) || (values[a] - values[a - 1] > 0 && values[b] - values[b - 1] > 0))
            values[a] = - values[a];
        if((values[a] - values[a - 1] < 0 && values[b] - values[b - 1] < 0) || (values[a] - values[a - 1] > 0 && values[b] - values[b - 1] > 0))
            values[a] = - values[a], values[b] = - values[b];
        if((values[a] - values[a - 1] < 0 && values[b] - values[b - 1] < 0) || (values[a] - values[a - 1] > 0 && values[b] - values[b - 1] > 0))
            values[a] = - values[a];
    }

    for(int i = 0; i < n; i++)
        cout<<values[i]<<" ";
    cout<<"\n";
}

int main(){
    int t;
    cin >> t;

    while(t--){
        init();
        solve();
    }
}
