#include <bits/stdc++.h>
#define MAXN 25

using namespace std;

int N, M;
int adjMat[MAXN][MAXN];

char memberName[MAXN][20];

bool init(){
    cin >> N >> M;
    if(N == 0){
        return false;
    }

    for(int i = 0; i < N; i++)
        fill(adjMat[i], adjMat[i] + N, INT_MAX >> 1),
        adjMat[i][i] = 0;

    for(int i = 0; i < N; i++){
        cin >> memberName[i];
    }

    for(int i = 0; i < M; i++){
        int da, a, w;
        cin >> da >> a >> w, da--, a--;
        adjMat[da][a] = adjMat[a][da] = w;
    }
    return true;
}

void fillAdjMat(){
    for(int k = 0; k < N; k++)
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                adjMat[i][j] = min(adjMat[i][j], adjMat[i][k] + adjMat[k][j]);
}

int getDist(int nodo){
    int S = 0;
    for(int i = 0; i < N; i++)
        S+= adjMat[i][nodo];
    return S;
}

int solve(){
    fillAdjMat();

    int best = 0, bestCost = INT_MAX >> 1;

    for(int i = 0; i < N; i++){
        if(getDist(i) < bestCost)
            bestCost = getDist(i), best = i;
    }

    return best;
}

int main(){
    FILE *out = stdout;

    for(int t = 1; init(); t++){
        fprintf(out, "Case #%d : %s\n", t, memberName[solve()]);
    }
}
