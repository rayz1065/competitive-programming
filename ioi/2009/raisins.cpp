#include <bits/stdc++.h>
#define MAXN 51
using namespace std;

int N, M;
int raisins[MAXN][MAXN], somma[MAXN][MAXN], memo[MAXN][MAXN][MAXN][MAXN];

int calcolaSomma(int r, int c, int R, int C){
    R--;
    C--;
    int S = somma[R][C];
    if(r > 0 && c > 0)
        S+= somma[r - 1][c - 1];
    if(r > 0)
        S-= somma[r - 1][C];
    if(c > 0)
        S-= somma[R][c - 1];
    return S;
}

void computaSomme(){
    somma[0][0] = raisins[0][0];
    for(int j = 1; j < M; j++){
        somma[0][j] = raisins[0][j] + somma[0][j - 1];
    }
    for(int i = 1; i < N; i++){
        int S = raisins[i][0];
        somma[i][0] = S + somma[i - 1][0];
        for(int j = 1; j < M; j++){
            S+= raisins[i][j];
            somma[i][j] = S + somma[i - 1][j];
        }
    }
}

int solve(int r, int c, int R, int C){
    if(R == r + 1 && C == c + 1)
        return 0;

    if(memo[r][c][R][C] == 0){
        memo[r][c][R][C] = INT_MAX;
        for(int i = r + 1; i < R; i++)
            memo[r][c][R][C] = min(solve(i, c, R, C) + solve(r, c, i, C), memo[r][c][R][C]);
        for(int i = c + 1; i < C; i++)
            memo[r][c][R][C] = min(solve(r, i, R, C) + solve(r, c, R, i), memo[r][c][R][C]);
        memo[r][c][R][C]+= calcolaSomma(r, c, R, C);
    }
    return memo[r][c][R][C];
}

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);

    in>>N>>M;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            in>>raisins[i][j];
        }
    }
    computaSomme();
    out<<solve(0, 0, N, M);
}
