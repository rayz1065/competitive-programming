#include <bits/stdc++.h>
#define MAXN 1005

using namespace std;

int n, m;
bool mappa[MAXN][MAXN];
int comp[MAXN][MAXN];

bool in_range(int r, int c){
    return r >= 0 && c >= 0 && r < n && c < m;
}

int movr[] = {0, 1, 0, -1},
    movc[] = {1, 0, -1, 0};

bool dfs(int r, int c, int nc){
    if(!in_range(r, c))
        return false;

    if(comp[r][c] != -1 || !mappa[r][c])
        return true;

    comp[r][c] = nc;

    bool sol = true;
    for(int m = 0; m < 4; m++){
        sol = min(sol, dfs(r + movr[m], c + movc[m], nc));
    }

    return sol;
}

int main(){
    cin >> n >> m;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            cin >> mappa[i][j];

    memset(comp, (1<<8) - 1, sizeof(comp));
    int ncomp = 0, s = 0;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(mappa[i][j] && comp[i][j] == -1)
                s+= dfs(i, j, ncomp++);
        }
    }

    cout<<s<<"\n";
}
