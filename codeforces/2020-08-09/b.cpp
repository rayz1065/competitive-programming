#include <bits/stdc++.h>
#define MAXN 105

using namespace std;

int n, m;
char grid[MAXN][MAXN];

void init(){
    cin >> n >> m;

    for(int i = 0; i < n; i++){
        cin >> grid[i];
    }
}

int solve(){
    int s = 0;

    for(int r = 0; r < n - 1; r++)
        if(grid[r][m - 1] == 'R')
            s++;
    for(int c = 0; c < m - 1; c++)
        if(grid[n - 1][c] == 'D')
            s++;

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
