#include <bits/stdc++.h>
#define MAXN 105
using namespace std;

int n, m;
char image[MAXN][MAXN];

bool visited[MAXN][MAXN];

int movR[] = {1, 0, -1, 0}, movC[] = {0, 1, 0, -1};

bool init(){
    if(!(cin >> n >> m)) return false;

    for(int i = 0; i < n; i++){
        cin >> image[i];
    }
    memset(visited, 0, sizeof visited);
    return true;
}

bool inRange(int r, int c){
    return r >= 0 && c >= 0 && r < n && c < m;
}

void visit(int r, int c){
    if(!inRange(r, c) || visited[r][c] || image[r][c] != '-')
        return ;
    visited[r][c] = true;
    for(int m = 0; m < 4; m++){
        visit(r + movR[m], c + movC[m]);
    }
}

int solve(){
    int s = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(!visited[i][j] && image[i][j] == '-'){
                visit(i, j);
                s+= 1;
            }
        }
    }
    return s;
}

int main(){
    int t = 1;
    while(init()){
        cout<<"Case "<<t++<<": "<<solve()<<"\n";
    }
}
