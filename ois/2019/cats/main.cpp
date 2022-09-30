#include <bits/stdc++.h>
#define MAXN 1005
using namespace std;

int N, M;
int fem[MAXN], mas[MAXN];
bool solved[MAXN][MAXN];
int memo[MAXN][MAXN];

int solve(int f, int m){
    if(f >= N || m >= M)
        return 0;
    if(solved[f][m])
        return memo[f][m];
    solved[f][m] = true;
    return memo[f][m] = max(max(solve(f + 1, m), solve(f, m + 1)), solve(f + 1, m + 1) + abs(fem[f] - mas[m]));
}

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);

    in >> N >> M;

    for(int i = 0; i < N; i++){
        in >> fem[i];
    }
    for(int i = 0; i < M; i++){
        in >> mas[i];
    }

    cout << solve(0, 0)<<endl;
}
