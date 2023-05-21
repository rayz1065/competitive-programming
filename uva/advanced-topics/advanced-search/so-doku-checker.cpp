#include <bits/stdc++.h>

#define ILLEGAL "Illegal"
#define UNIQUE "Unique"
#define AMBIGUOUS "Ambiguous"
#define IMPOSSIBLE "Impossible"

#define MAXN 10

using namespace std;

int n = 9;
int grid[MAXN][MAXN];
bool rowHas[MAXN][MAXN];
bool colHas[MAXN][MAXN];
bool sqrHas[MAXN/3][MAXN/3][MAXN];
bool illegal;
int nSol;

bool setCell(int r, int c, int v){
    if(rowHas[r][v]) return false;
    if(colHas[c][v]) return false;
    if(sqrHas[r/3][c/3][v]) return false;

    grid[r][c] = v;
    return rowHas[r][v] = colHas[c][v] = sqrHas[r/3][c/3][v] = true;
}

void unsetCell(int r, int c){
    int v = grid[r][c];
    grid[r][c] = 0;
    rowHas[r][v] = colHas[c][v] = sqrHas[r/3][c/3][v] = false;
}

bool init(){
    memset(rowHas, 0, sizeof rowHas);
    memset(colHas, 0, sizeof colHas);
    memset(sqrHas, 0, sizeof sqrHas);
    memset(grid, 0, sizeof grid);
    illegal = false;
    nSol = 0;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            int v;
            if(!(cin >> v))
                return false;
            if(v != 0 && !setCell(i, j, v))
                illegal = true;
        }
    }
    return true;
}

void solve(int r, int c){
    if(c == n) r++, c = 0;
    if(r == n){
        nSol++;
        return ;
    }
    if(nSol > 1)
        return ;

    if(grid[r][c] != 0){
        solve(r, c + 1);
        return ;
    }

    for(int v = 1; v <= 9; v++){
        if(setCell(r, c, v)){
            solve(r, c + 1);
            unsetCell(r, c);
        }
    }
}

int main(){
    for(int t = 1; init(); t++){
        cout<<"Case "<<t<<": ";
        if(illegal)
            cout<<ILLEGAL;
        else{
            solve(0, 0);
            if(nSol == 0)
                cout<<IMPOSSIBLE;
            else if(nSol == 1)
                cout<<UNIQUE;
            else
                cout<<AMBIGUOUS;
        }

        cout<<".\n";
    }
}
