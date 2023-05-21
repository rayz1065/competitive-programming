#include <bits/stdc++.h>

#define MAXN 15

using namespace std;

int n = 10;
string subtaskName;
char chrGrid[MAXN][MAXN];
bool grid[MAXN][MAXN];
int bestSol;

int movr[] = {-1, 0, 1, 0, 0};
int movc[] = {0, 1, 0, -1, 0};

bool init(){
    bestSol = INT_MAX >> 1;
    cin >> subtaskName;
    if(subtaskName == "end") return false;

    for(int i = 0; i < n; i++){
        cin >> chrGrid[i];

        for(int j = 0; j < n; j++){
            grid[i][j] = chrGrid[i][j] == 'O';
        }
    }

    return true;
}

bool inRange(int r, int c){
    return r >= 0 && c >= 0 && r < n && c < n;
}

void switchCell(int r, int c){
    for(int m = 0; m < 5; m++){
        int newr = r + movr[m], newc = c + movc[m];
        if(inRange(newr, newc))
            grid[newr][newc] = !grid[newr][newc];
    }
}

void solve(int r, int c, int depth){
    if(depth >= bestSol) return ;
    if(c == n) c = 0, r++;
    if(r == n){
        bestSol = depth;
        return ;
    }

    if(r == 0){
        solve(r, c + 1, depth);
        switchCell(r, c);
        solve(r, c + 1, depth + 1);
        switchCell(r, c);
    }
    else{
        if(r == n - 1){
            if(c > 0 && grid[r - 1][c] != grid[r][c - 1])
                return ;
            if(c == n - 1 && grid[r - 1][c] != grid[r][c])
                return ;
        }

        if(grid[r - 1][c]){
            switchCell(r, c);
            solve(r, c + 1, depth + 1);
            switchCell(r, c);
        }
        else{
            solve(r, c + 1, depth);
        }
    }
    return ;
}

int solve(){
    solve(0, 0, 0);
    if(bestSol > 100)
        return -1;
    return bestSol;
}

int main(){
    while(init()){
        cout<<subtaskName<<" "<<solve()<<"\n";
    }
}
