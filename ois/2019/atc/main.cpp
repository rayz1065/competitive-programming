#include <bits/stdc++.h>
#define MAXN 205
using namespace std;

int N, M;
char mappa[MAXN][MAXN];
int dist[MAXN][MAXN];
bool visited[MAXN][MAXN];
int movR[] = {-1, 0, 1, 0}, movC[] = {0, 1, 0, -1};

typedef pair<int, int> pii;

inline bool inRange(int r, int c){
    return (r >= 0 && c >= 0 && r < N && c < M);
}

int solve(int r, int c){
    dist[r][c] = 0;
    visited[r][c] = true;
    queue<pii> FF;
    FF.push({r, c});

    while(!FF.empty()){
        pii pos = FF.front();
        FF.pop();
        r = pos.first, c = pos.second;
        for(int m = 0; m < 4; m++){
            int newR = r + movR[m], newC = c + movC[m];
            while(inRange(newR, newC) && mappa[newR][newC] != '#'){
                if(!visited[newR][newC]){
                    dist[newR][newC] = dist[r][c] + 1;
                    visited[newR][newC] = true;
                    FF.push({newR, newC});
                }
                newR+= movR[m], newC+= movC[m];
            }
        }
    }
    return dist[N - 1][M - 1] - 1;
}

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);

    in >> N;
    M = N;

    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++)
            in >> mappa[i][j];
    }

    cout << solve(0, 0)<<endl;
}
