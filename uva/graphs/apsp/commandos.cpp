#include <bits/stdc++.h>
#define MAXN 105

using namespace std;

int N, M;
int adjMat[MAXN][MAXN];
int s, d;

void init(){
    cin >> N >> M;
    for(int i = 0; i < N; i++)
        fill(adjMat[i], adjMat[i] + N, INT_MAX >> 1),
        adjMat[i][i] = 0;

    for(int i = 0; i < M; i++){
        int da, a;
        cin >> da >> a;
        adjMat[da][a] = adjMat[a][da] = 1;
    }
    cin >> s >> d;
}

void fillAdjMat(){
    for(int k = 0; k < N; k++)
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                adjMat[i][j] = min(adjMat[i][j], adjMat[i][k] + adjMat[k][j]);
}

int solve(){
    fillAdjMat();

    int S = 0;

    for(int i = 0; i < N; i++)
        S = max(S, adjMat[s][i] + adjMat[i][d]);

    return S;
}

int main(){
    int T;
    cin >> T;

    for(int t = 1; t <= T; t++){
        init();
        printf("Case %d: %d\n", t, solve());
    }
}
