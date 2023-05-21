#include <bits/stdc++.h>
#define MAXN 55

using namespace std;

int N, M;
int adjMat[MAXN][MAXN];

map<string, int> persone;
int foundP = 0;

int addP(string a){
    if(persone.count(a) == 0)
        persone[a] = foundP++;
    return persone[a];
}

bool init(){
    cin >> N >> M;

    if(N == 0 && M == 0)
        return false;

    foundP = 0;
    persone.clear();

    for(int i = 0; i < N; i++)
        fill(adjMat[i], adjMat[i] + N, INT_MAX >> 1), adjMat[i][i] = 0;

    for(int i = 0; i < M; i++){
        string a, b;
        cin >> a >> b;

        int u = addP(a);
        int w = addP(b);

        adjMat[u][w] = adjMat[w][u] = 1;
    }
    return true;
}

int solve(){
    for(int k = 0; k < N; k++)
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                adjMat[i][j] = min(adjMat[i][j], adjMat[i][k] + adjMat[k][j]);

    int S = 0;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            S = max(S, adjMat[i][j]);

    if(S == INT_MAX >> 1)
        return -1;
    return S;
}

int main(){
    FILE *out = stdout;

    for(int t = 1; init(); t++){
        int S = solve();

        fprintf(out, "Network %d: ", t), (S == -1) ? fprintf(out, "DISCONNECTED\n\n") : fprintf(out, "%d\n\n", S);
    }
}
