#include <bits/stdc++.h>
#define MAXN 5005

using namespace std;

int N;
vector<int> grafo[MAXN];

bool init(){
    if(!(cin >> N))
        return false;

    for(int i = 0; i < N; i++)
         grafo[i].clear();

    for(int i = 0; i < N; i++){
        int k;
        cin >> k;
        for(int j = 0; j < k; j++){
            int a;
            cin >> a;
            a--;

            grafo[i].push_back(a);
        }
    }
    return true;
}

/*void dfs(int nodo){
    visited[nodo] = true;
    for(auto i:grafo[nodo])
        if(!visited[i])
            dist[i] = dist[nodo] + 1, dfs(i);
}

void apsp(){
    for(int i = 0; i < N; i++){
        fill(visited, visited + N, false);
        fill(dist, dist + N, INT_MAX >> 1);

        dist[i] = 0;
        dfs(i);

        for(int j = 0; j < N; j++)
            adjMat[i][j] = dist[j];
    }
}

int maxDist(int nodo){
    int S = 0;
    for(int i = 0; i < N; i++)
        S = max(S, adjMat[nodo][i]);
    return S;
}
*/

set<int> best, worst;
int dist[MAXN];
int dfsSpanningTree[MAXN];

void dfs(int nodo){
    for(auto i:grafo[nodo])
        if(dist[i] == INT_MAX >> 1)
            dist[i] = dist[nodo] + 1, dfsSpanningTree[i] = nodo, dfs(i);
}

int getFarthest(int nodo){
    fill(dfsSpanningTree, dfsSpanningTree + N, -1);
    fill(dist, dist + N, INT_MAX >> 1);
    dist[nodo] = 0;

    dfs(nodo);

    return max_element(dist, dist + N) - dist;
}

void solve(){
    best.clear(), worst.clear();
    int edNode = getFarthest(getFarthest(0));
    int diametro = dist[edNode];

    for(int i = 0; i < N; i++)
        if(dist[i] == diametro)
            worst.insert(i);

    int nodo = edNode;
    while(nodo != -1 && dist[nodo] > diametro/2 + diametro%2)
        nodo = dfsSpanningTree[nodo];
    while(nodo != -1 && dist[nodo] >= diametro/2)
        best.insert(nodo), nodo = dfsSpanningTree[nodo];

    edNode = getFarthest(*worst.begin());

    for(int i = 0; i < N; i++)
        if(dist[i] == diametro)
            worst.insert(i);
}

int main(){
    while(init()){
        solve();
        // nodi + 1
        cout<<"Best Roots  :";
        for(auto i:best)
            cout<<" "<<i + 1;
        cout<<"\nWorst Roots :";
        for(auto i:worst)
            cout<<" "<<i + 1;
        cout<<"\n";
    }
}
