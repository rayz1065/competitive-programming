#include <bits/stdc++.h>
#define MAXN 27

using namespace std;

typedef long long int lli;

int n = 4;
lli grid[MAXN][MAXN];
vector<int> sol;

void populateGrid(){
    for(int i = 0; i < MAXN; i++)
        for(int j = 0; j < MAXN; j++){
            if(i == 0){
                if(j == 0) grid[i][j] = 1;
                else if(j == 1) grid[i][j] = 1;
                else grid[i][j] = grid[i][j - 1] + grid[i][j - 2];
            }
            else{
                if(j == 0) grid[i][j] = grid[i - 1][j + 2];
                else if(j == 1) grid[i][j] = grid[i - 1][j + 2];
                else grid[i][j] = grid[i][j - 1] + grid[i][j - 2];
            }
        }
}

void dfs(int i, int j, lli s){
    s+= grid[i][j];
    if(i == n - 1 && j == n - 1){
        sol.push_back(s);
        return ;
    }

    if(i == n - 1){
        dfs(i, j + 1, s);
        return ;
    }
    if(j == n - 1){
        dfs(i + 1, j, s);
        return ;
    }
    dfs(i + 1, j, s);
    dfs(i, j + 1, s);
}

int main(){
    populateGrid();
    dfs(0, 0, 0);
    sort(sol.begin(), sol.end());
    for(auto i:sol)
        cout<<i<<" ";
    cout<<"\n";
}
