#include <bits/stdc++.h>
#define MAXN 1005

using namespace std;


int N, M;
vector<int> grafo[MAXN];
int dist[MAXN];

void init(){
    cin >> N >> M;
    for(int i = 0; i < N; i++)
        grafo[i].clear();

    for(int i = 0; i < M; i++){
        int a, b;
        cin >> a >> b;
        grafo[a].push_back(b);
        grafo[b].push_back(a);
    }
}

void bfs(int nodo){
    fill(dist, dist + N, INT_MAX >> 1);
    dist[nodo] = 0;

    queue<int> FF;
    FF.push(nodo);

    while(!FF.empty()){
        nodo = FF.front();
        FF.pop();

        for(auto i:grafo[nodo]){
            if(dist[i] == INT_MAX >> 1){
                dist[i] = dist[nodo] + 1;
                FF.push(i);
            }
        }
    }
}

int main(){
    FILE *out = stdout;

    int T;
    cin >> T;

    for(int t = 1; t <= T; t++){
        init();
        bfs(0);

        if(t > 1)
            fprintf(out, "\n");
        for(int i = 1; i < N; i++)
            fprintf(out, "%d\n", dist[i]);
    }
}
