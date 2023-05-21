#include <bits/stdc++.h>
#define MAXN 505
#define MAXM 505

using namespace std;

int N;
int adjMat[2*MAXN][2*MAXN];

int s, t;

/// s = 0
/// t = N + M + 1
/// b: i + 1
/// n: j + N + 1

void init(){
    int N, M;
    cin >> N >> M;

    s = 0;
    t = N + M + 1;

    memset(adjMat, 0, sizeof(adjMat));

    for(int i = 0; i < N; i++){
        adjMat[0][i + 1] = 1;
        for(int j = 0; j < M; j++)
            cin >> adjMat[i + 1][j + N + 1];
    }
    for(int j = 0; j < M; j++)
        adjMat[j + N + 1][t] = 1;

    ::N = N + M + 2;
}

int mf, f;
int dist[MAXN*2], bfsTree[MAXN*2];

bool findAugPath(){
    fill(dist, dist + N, INT_MAX >> 1);
    fill(bfsTree, bfsTree + N, -1);

    dist[s] = 0;
    queue<int> FF;
    FF.push(s);

    while(!FF.empty() && dist[t] == INT_MAX >> 1){
        int nodo = FF.front();
        FF.pop();

        for(int i = 0; i < N; i++){
            if(adjMat[nodo][i] > 0 && dist[i] == INT_MAX >> 1)
                dist[i] = dist[nodo] + 1, bfsTree[i] = nodo, FF.push(i);
        }
    }

    while(!FF.empty())
        FF.pop();
    return (dist[t] != INT_MAX >> 1);
}

void augment(int nodo, int minArco){
    if(bfsTree[nodo] == -1)
        f = minArco;
    else{
        int da = bfsTree[nodo];
        augment(da, min(minArco, adjMat[da][nodo]));

        adjMat[da][nodo]-= f;
        adjMat[nodo][da]+= f;
    }
}

int solve(){
    mf = 0;
    while(findAugPath()){
        augment(t, INT_MAX >> 1);
        mf+= f;
    }

    return mf;
}

int main(){
    FILE *out = stdout;

    int T;
    cin >> T;

    for(int t = 1; t <= T; t++){
        init();
        fprintf(out, "Case %d: a maximum of %d nuts and bolts can be fitted together\n", t, solve());
    }
}
