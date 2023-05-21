#include <bits/stdc++.h>
#define MAXN 105

using namespace std;

int N, M;
int adjMat[MAXN][MAXN];

void init(){
    cin >> N >> M;
    for(int i = 1; i <= N; i++)
        fill(adjMat[i] + 1, adjMat[i] + N + 1, INT_MAX >> 1), adjMat[i][i] = 0;

    for(int i = 0; i < M; i++){
        int da, a, w;
        cin >> da >> a >> w;
        adjMat[da][a] = adjMat[a][da] = min(adjMat[da][a], w);
    }
}

bool isPossib(int i){
    for(int j = 2; j <= 5; j++)
        if(adjMat[j][i] != adjMat[1][i])
            return false;
    return true;
}

int getFarthest(int nodo){
    int S = 0;
    for(int i = 1; i <= N; i++)
        S = max(S, adjMat[nodo][i]);
    return S;
}

int solve(){
    for(int k = 1; k <= N; k++)
        for(int i = 1; i <= N; i++)
            for(int j = 1; j <= N; j++)
                adjMat[i][j] = min(adjMat[i][j], adjMat[i][k] + adjMat[k][j]);

    vector<int> possibiliPos;
    for(int i = 1; i <= N; i++){
        if(isPossib(i))
            possibiliPos.push_back(i);
    }

    int bestS = INT_MAX>>1, sol = -1;
    for(auto i:possibiliPos){
        if(getFarthest(i) < bestS)
            bestS = getFarthest(i), sol = i;
    }
    if(sol == -1)
        return -1;
    return bestS;
}

int main(){
    FILE *out = stdout;

    int T;
    cin >> T;

    for(int t = 1; t <= T; t++){
        init();
        fprintf(out, "Map %d: %d\n", t, solve());
    }
}
