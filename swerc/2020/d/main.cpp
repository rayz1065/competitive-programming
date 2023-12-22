#include <bits/stdc++.h>
#define MAXN 100005
#define MAXM 100005
using namespace std;

int n, m, minDist, maxDist;

struct arco{
    int a;
    int b;
    int len;
    bool visited;
} archi[MAXM];

int dist[MAXN];
vector<pair<int, int>> grafo[MAXN];

void djikstra(int nodo){
    fill(dist, dist + n, INT_MAX >> 1);
    dist[nodo] = 0;
    set<pair<int, int>> ff;
    ff.insert({0, nodo});
    while(!ff.empty()){
        nodo = ff.begin()->second;
        ff.erase(ff.begin());
        for(auto i:grafo[nodo]){
            int idxArco = i.second;
            int a = i.first;
            int l = archi[idxArco].len;
            int newDist = dist[nodo] + l;
            if(dist[a] > newDist){
                dist[a] = newDist;
                ff.insert({newDist, a});
            }
        }
    }
}

void init(){
    cin >> n >> m >> minDist >> maxDist;
    for(int i = 0; i < m; i++){
        int da, a, len;
        cin >> da >> a >> len;
        archi[i] = {da, a, len, false};
        grafo[da].push_back({a, i});
        grafo[a].push_back({da, i});
    }
}

int solve(){
    djikstra(0);
    for(int i = 0; i < n; i++){
        if(dist[i]*2 < maxDist){
            for(auto j:grafo[i]){
                int idxArco = j.second;
                archi[idxArco].visited = true;
            }
        }
    }

    int s = 0;
    for(int i = 0; i < m; i++)
        s+= archi[i].visited;
    return s;
}

int main(){
    init();
    cout<<solve();
}
