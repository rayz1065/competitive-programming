#include <bits/stdc++.h>
#define MAXN 20

using namespace std;

int n;
bool grid[MAXN][MAXN];

int movr[] = {0, 1, 0, -1};
int movc[] = {1, 0, -1, 0};

int bestSol;

void init(){
    cin >> n;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            cin >> grid[i][j];
    }
    bestSol = INT_MAX >> 1;
}

bool inRange(int r, int c){
    return r >= 0 && c >= 0 && r < n && c < n;
}

int getParity(int r, int c){
    int s = 0;

    for(int m = 0; m < 4; m++){
        int newr = r + movr[m], newc = c + movc[m];
        if(inRange(newr, newc) && grid[newr][newc])
            s++;
    }
    return s;
}

void solveState(int r, int c, int depth){
    if(c == n)
        r++, c = 0;
    if(depth >= bestSol)
        return ;

    if(r == n){
        bestSol = depth;
        return ;
    }

    if(r > 0){
        if(getParity(r - 1, c)%2){
            if(grid[r][c])
                return ;
            grid[r][c] = true;
            solveState(r, c + 1, depth + 1);
            grid[r][c] = false;
        }
        else{
            solveState(r, c + 1, depth);
        }
        return ;
    }

    solveState(r, c + 1, depth);

    if(!grid[r][c]){
        grid[r][c] = true;
        solveState(r, c + 1, depth + 1);
        grid[r][c] = false;
    }
}

int solve(){
    solveState(0, 0, 0);
    if(bestSol == INT_MAX>>1)
        return -1;
    return bestSol;
}

// fstream out;
// #define cout out

int main(){
    // out.open("output.txt", ios::out);
    int t;
    cin >> t;

    for(int i = 0; i < t; i++){
        init();
        cout<<"Case "<<(i + 1)<<": "<<solve()<<"\n";
    }
}
