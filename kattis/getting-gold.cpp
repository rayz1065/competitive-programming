#include <bits/stdc++.h>
#define MAXN 55

using namespace std;

enum Tile {
    FLOOR,
    GOLD,
    TRAP,
    WALL
};

int w, h;
int initial_r, initial_c;
Tile tiles[MAXN][MAXN];
bool visited[MAXN][MAXN];

int movr[] = {-1, 0, 1, 0};
int movc[] = {0, -1, 0, 1};

void read_in() {
    cin >> w >> h;
    for(int r = 0; r < h; r++) {
        for(int c = 0; c < w; c++) {
            char cell;
            cin >> cell;
            Tile tile = FLOOR;
            if(cell == 'P') {
                initial_r = r;
                initial_c = c;
            }
            else if(cell == 'G') {
                tile = GOLD;
            }
            else if(cell == '#') {
                tile = WALL;
            }
            else if(cell == 'T') {
                tile = TRAP;
            }
            tiles[r][c] = tile;
        }
    }
}

bool in_range(int r, int c) {
    return r >= 0 && r < h && c >= 0 && c < w;
}

void dfs(int r, int c) {
    if(visited[r][c]) {
        return ;
    }
    visited[r][c] = true;

    for(int m = 0; m < 4; m++) {
        int newr = r + movr[m];
        int newc = c + movc[m];
        if(in_range(newr, newc) && tiles[newr][newc] == TRAP) {
            // too dangerous
            return ;
        }
    }

    for(int m = 0; m < 4; m++) {
        int newr = r + movr[m];
        int newc = c + movc[m];
        if(in_range(newr, newc) && tiles[newr][newc] != WALL) {
            dfs(newr, newc);
        }
    }
}

int main() {
    read_in();
    dfs(initial_r, initial_c);

    int collected = 0;
    for(int r = 0; r < h; r++) {
        for(int c = 0; c < w; c++) {
            if(visited[r][c] && tiles[r][c] == GOLD) {
                collected+= 1;
            }
        }
    }
    cout << collected << "\n";
}