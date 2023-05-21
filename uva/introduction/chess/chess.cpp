#include <bits/stdc++.h>
#define MAXN 11
#define MAXMOV 8
using namespace std;

int N, M, S;
int occ[MAXN][MAXN];
bool placed[MAXN][MAXN];
bool multiMove;
char t;
vector<int> movR, movC;

void init(){
    S = 0;
    cin >> t >> N >> M;

    memset(occ, 0, sizeof(occ));
    if(t == 'r'){
        // torre
        multiMove = true;
        movR = {0, 1, 0, -1};
        movC = {1, 0, -1, 0};
    }
    if(t == 'k'){
        // cavallo
        multiMove = false;
        movR = {-2, -2, -1, -1, 1, 1, 2, 2};
        movC = {-1, 1, -2, 2, -2, 2, -1, 1};
    }
    if(t == 'Q'){
        // regina
        multiMove = true;
        movR = {-1, -1, -1, 0, 1, 1, 1, 0};
        movC = {-1, 0, 1, 1, 1, 0, -1, -1};
    }
    if(t == 'K'){
        // re
        multiMove = false;
        movR = {-1, -1, -1, 0, 1, 1, 1, 0};
        movC = {-1, 0, 1, 1, 1, 0, -1, -1};
    }
}

inline bool inRange(int r, int c){
    return (r >= 0 && c >= 0 && r < M && c < N);
}

void stampa(){
    for(int r = 0; r < M; r++){
        for(int c = 0; c < N; c++)
            cout<<((placed[r][c])?'O':'-')<<" ";
        cout<<"\n";
    }
    cout<<"\n";
}

void piazza(int r, int c, int q){
    placed[r][c]+= q;
    if(!multiMove){
        for(int i = 0; i < movR.size(); i++){
            if(inRange(r + movR[i], c + movC[i]))
                occ[r + movR[i]][c + movC[i]]+= q;
        }
        return ;
    }
    for(int i = 0; i < movR.size(); i++){
        int newR = r + movR[i], newC = c + movC[i];
        do{
            occ[newR][newC]+= q;
            newR+= movR[i], newC+= movC[i];
        } while(inRange(newR, newC));
    }
}

void solve(int r, int c, int p){
    stampa();
    if(c == N){
        c = 0, r++;
        int maxScore = p;
        for(int i = r; i < M; i++){
            for(int j = 0; j < N; j++)
                maxScore+= 1 - placed[i][j];
        }
        if(maxScore < S)
            return ;
    }
    if(r == M){
        stampa();
        S = max(S, p);
        return ;
    }
    if(occ[r][c] == 0 && !placed[r][c]){
        piazza(r, c, 1);
        solve(r, c + 1, p + 1);
        piazza(r, c, -1);
    }
    solve(r, c + 1, p);
}

int main(){
    int T;
    cin >> T;
    for(int x = 1; x <= T; x++){
        init();
        if(t == 'Q' || t == 'r')
            S = min(N, M);
        else if(t == 'K')
            S = ((N + 1)/2)*((M + 1)/2);
        else
            S = (N*M + 1)/2;
        //solve(0, 0, 0);
        cout<<S<<"\n";
    }
}
