#include <bits/stdc++.h>
#define MAXN 105

using namespace std;

int n;
int a[MAXN];

void init(){
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> a[i];
}

int solve(){
    sort(a, a + n);
    for(int i = 1; i < n; i++)
        if(a[i] - a[i - 1] > 1)
            return false;
    return true;
}

int main(){
    int t;
    cin >> t;

    while(t--){
        init();
        cout<<(solve() ? "YES" : "NO")<<"\n";
    }
}
