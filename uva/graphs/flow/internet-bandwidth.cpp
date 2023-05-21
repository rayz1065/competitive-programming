#include <bits/stdc++.h>
#define MAXN 1005

using namespace std;

int N, M;
// 1 -> N
int s, t;
// source, dest

int adjMat[MAXN][MAXN];
vector<int> grafo[MAXN];

void addIfNotExists(int da, int a){
    for(auto i:grafo[da]){
        if(i == a)
            return ;
    }
    grafo[da].push_back(a);
}

bool init(){
    cin >> N;
    if(N == 0)
        return false;

    for(int i = 0; i < N; i++)
        fill(adjMat[i], adjMat[i] + MAXN, 0), grafo[i].clear();

    cin >> s >> t >> M;
    s--, t--;

    for(int i = 0; i < M; i++){
        int da, a, w;
        cin >> da >> a >> w;

        da--, a--;
        adjMat[da][a]+= w, adjMat[a][da]+= w;

        addIfNotExists(da, a);
        addIfNotExists(a, da);
    }

    return true;
}

int dist[MAXN];
int bfsTree[MAXN];
int f, mf;

bool findAugPath(){
    fill(dist, dist + N, INT_MAX>>1);
    fill(bfsTree, bfsTree + N, -1);

    int nodo = s;
    dist[nodo] = 0;
    queue<int> FF;

    FF.push(nodo);

    while(!FF.empty()){
        nodo = FF.front();
        FF.pop();

        if(nodo == t){
            while(!FF.empty())
                FF.pop();
            return true;
        }

        for(auto i:grafo[nodo]){
            if(adjMat[nodo][i] > 0 && dist[i] == INT_MAX>>1)
                bfsTree[i] = nodo, dist[i] = dist[nodo] + 1, FF.push(i);
        }
    }
    return false;
}

void augment(int nodo){
    if(bfsTree[nodo] != -1){
        int da = bfsTree[nodo];

        f = min(f, adjMat[da][nodo]);
        augment(da);

        adjMat[da][nodo]-= f;
        adjMat[nodo][da]+= f;
    }
}

void edmons_karp(){
    mf = 0;
    while(findAugPath()){
        f = INT_MAX>>1;
        augment(t);
        mf+= f;
    }
}

int solve(){
    edmons_karp();
    return mf;
}

int main(){
    FILE *out = stdout;

    for(int t = 1; init(); t++){
        fprintf(out, "Network %d\nThe bandwidth is %d.\n\n", t, solve());
    }
}
