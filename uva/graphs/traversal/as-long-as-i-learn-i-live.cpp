#include <bits/stdc++.h>

#define MAXN 105

using namespace std;

int N, M;
vector<int> grafo[MAXN];
int val[MAXN];

void init(){
    cin >> N >> M;
    for(int i = 0; i < N; i++)
        grafo[i].clear();
    for(int i = 0; i < N; i++)
        cin >> val[i];

    for(int i = 0; i < M; i++){
        int da, a;
        cin >> da >> a;
        grafo[da].push_back(a);
    }
}

pair<int, int> solve(int nodo){
    int S = 0;

    while(grafo[nodo].size() > 0){
        int bestVal = -1, bestNode = -1;
        for(auto i:grafo[nodo])
            if(val[i] > bestVal)
                bestVal = val[i], bestNode = i;
        S+= bestVal, nodo = bestNode;
    }
    return {nodo, S};
}

int main(){
    FILE *out = stdout;

    int T;
    cin >> T;

    for(int t = 1; t <= T; t++){
        init();

        auto p = solve(0);

        fprintf(out, "Case %d: %d %d\n", t, p.second, p.first);
    }
}
