#include <bits/stdc++.h>
#define MAXN 305

using namespace std;

int n, m;
int grid[MAXN][MAXN];

void init(){
    cin >> n >> m;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            cin >> grid[i][j];
}

int neigh(int i, int j){
    return 4 - (i == 0 || i == n - 1) - (j == 0 || j == m - 1);
}

void solve(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(grid[i][j] > neigh(i, j)){
                cout<<"NO\n";
                return ;
            }
        }
    }
    cout<<"YES\n";
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cout<<neigh(i, j)<<" ";
        }
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
