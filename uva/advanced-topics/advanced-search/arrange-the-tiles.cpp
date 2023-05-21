#include <bits/stdc++.h>
#define N_TILES 12
#define N_ROWS 4
#define N_COLS 3

using namespace std;

string tiles[N_TILES];
bool used[N_TILES];
int grid[N_ROWS][N_COLS];
int mul;

typedef enum {TOP, RIGHT, BOTTOM, LEFT} side;

int factorial(int n){
    if(n) return n*factorial(n - 1);
    return 1;
}

void init(){
    for(int i = 0; i < N_TILES; i++)
        cin >> tiles[i];
    sort(tiles, tiles + N_TILES);

    mul = 1;
    int currMul = 1;
    for(int i = 1; i < N_TILES; i++){
        if(tiles[i] == tiles[i - 1])
            currMul++;
        else{
            mul*= factorial(currMul);
            currMul = 1;
        }
    }
    mul*= factorial(currMul);
}

int solve(int r, int c){
    if(c == N_COLS) r++, c = 0;
    if(r == N_ROWS){
        return 1;
    }

    int lst = -1;

    int s = 0;
    for(int i = 0; i < N_TILES; i++){
        if(!used[i]){
            if(lst != -1 && tiles[lst] == tiles[i]) continue;
            lst = i;
            if(r > 0){
                int ab = grid[r - 1][c];
                if(tiles[i][TOP] != tiles[ab][BOTTOM]) continue;
            }
            if(c > 0){
                int lf = grid[r][c - 1];
                if(tiles[i][LEFT] != tiles[lf][RIGHT]) continue;
            }
            grid[r][c] = i;
            used[i] = true;
            s+= solve(r, c + 1);
            used[i] = false;
        }
    }
    return s;
}

int solve(){
    return solve(0, 0)*mul;
}

int main(){
    int t;
    cin >> t;

    for(int i = 0; i < t; i++){
        init();
        cout<<"Case "<<(i + 1)<<": "<<solve()<<"\n";
    }
}
