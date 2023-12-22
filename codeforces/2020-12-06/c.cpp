#include <bits/stdc++.h>
#define MAXN 305

using namespace std;

int n;
char grid[MAXN][MAXN];
bool dontChange[MAXN][MAXN];
int changed;

void init(){
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> grid[i];
    memset(dontChange, 0, sizeof dontChange);
    changed = 0;
}

bool inRange(int x, int y){
    return x >= 0 && y >= 0 && x < n && y < n;
}

void printGrid(){
    for(int i = 0; i < n; i++)
        cout<<grid[i]<<"\n";
}

bool isVerticalWin(int x, int y){
    if(grid[x][y] == '.')
        return false;
    while(inRange(x - 1, y) && grid[x - 1][y] == grid[x][y])
        x--;

    int s = 1;
    while(inRange(x + 1, y) && grid[x + 1][y] == grid[x][y])
        x++, s++;

    return (s >= 3);
}

bool isHorizzontalWin(int x, int y){
    if(grid[x][y] == '.')
        return false;

    while(inRange(x, y - 1) && grid[x][y - 1] == grid[x][y])
        y--;

    int s = 1;
    while(inRange(x, y + 1) && grid[x][y + 1] == grid[x][y])
        y++, s++;

    return s >= 3;
}

bool isWin(int x, int y){
    bool s = isHorizzontalWin(x, y) || isVerticalWin(x, y);
    return s;
}

void changeCell(int x, int y){
    assert(inRange(x, y) && !dontChange[x][y] && grid[x][y] != '.');
    if(grid[x][y] == 'X') grid[x][y] = 'O';
    else grid[x][y] = 'X';

    for(int i = -2; i <= 2; i++)
        if(inRange(x + i, y)) dontChange[x + i][y] = true;
    for(int i = -2; i <= 2; i++)
        if(inRange(x, y + i)) dontChange[x][y + i] = true;
    changed+= 1;
}

void changeCellRec(int x, int y){
    if(!inRange(x, y)) return ;

    if(isWin(x, y)){
        changeCell(x, y);
        changeCellRec(x + 3, y);
        changeCellRec(x, y + 3);
    }
}

void solve(){
    for(int x = 0; x < n; x++){
        for(int y = 0; y < n; y++){
            if(isVerticalWin(x, y) && isHorizzontalWin(x, y) && !dontChange[x][y]){
                changeCellRec(x, y);
            }
        }
    }
    for(int x = 0; x < n; x++){
        for(int y = 0; y < n; y++){
            if(isWin(x, y) && !dontChange[x][y])
                changeCell(x, y);
        }
    }
    /*for(int diag = 2; diag < 2*n; diag+= 3){
        int x = 0, y = diag;
        while(x < n && y >= n){
            x++, y--;
        }
        while(inRange(x, y)){
            if(isWin(x, y))
                grid[x][y] = 'O';
            x++, y--;
        }
    }*/
}

int main(){
    int t;
    cin >> t;

    while(t--){
        init();
        solve();
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                // assert(!isWin(i, j));
            }
        }
        printGrid();
    }
}
