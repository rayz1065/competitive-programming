#include <bits/stdc++.h>
#define MAXN 50005

using namespace std;

int n;
int a[MAXN];

void init(){
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> a[i];
}

bool solve(){
    for(int i = 0; i < n - 1; i++)
        if(a[i] <= a[i + 1]) return true;
    return false;
}

int main(){
    int t;
    cin >> t;

    while(t--){
        init();
        cout<<(solve() ? "YES" : "NO")<<"\n";
    }
}
