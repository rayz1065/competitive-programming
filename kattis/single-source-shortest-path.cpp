#include <bits/stdc++.h>
#define MAXN 10005
using namespace std;

list<pair<int, int> > grafo[MAXN];
int dist[MAXN];

void djikistra(int nodo){
    set<pair<int, int> > FF;
    FF.insert({0, nodo});
    fill(dist, dist + MAXN, INT_MAX/2);
    dist[nodo] = 0;

    while(!FF.empty()){
        nodo = FF.begin()->second;
        FF.erase(FF.begin());
        for(auto j:grafo[nodo]){
            if(dist[j.first] > dist[nodo] + j.second){
                dist[j.first] = dist[nodo] + j.second;
                FF.insert({dist[j.first], j.first});
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M, Q, S;
    while(cin >> N >> M >> Q >> S){
        if(N == 0 && M == 0 && Q == 0 && S == 0)
            return 0;
        for(int i = 0; i < N; i++)
            grafo[i].clear();
        for(int i = 0; i < M; i++){
            int a, b, w;
            cin >> a >> b >> w;
            grafo[a].push_back({b, w});
        }
        djikistra(S);
        for(int i = 0; i < Q; i++){
            int a;
            cin >> a;
            if(dist[a] == INT_MAX/2)
                cout<<"Impossible\n";
            else
                cout<<dist[a]<<"\n";
        }
        cout<<"\n";
    }
}
