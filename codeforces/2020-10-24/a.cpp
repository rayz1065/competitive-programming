#include <bits/stdc++.h>
#define MAXN 105

using namespace std;

int n, m;
int a[MAXN];

void init(){
    cin >> n >> m;
    for(int i = 0; i < n; i++)
        cin >> a[i];
}

bool solve(){
    int s = 0;
    for(int i = 0; i < n; i++)
        s+= a[i];
    return s == m;
}

int main(){
    int t;
    cin >> t;

    while(t--){
        init();
        cout<<(solve() ? "YES" : "NO")<< "\n";
    }
}
