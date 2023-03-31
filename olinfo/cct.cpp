#include <bits/stdc++.h>
#define MAXN 100005
#define MAXK 21

using namespace std;

int N, K;
int dist[MAXN][MAXK];
int tempReq[MAXN];
int carota[MAXN];

int bfs(){
    int nodo = 0, k = 0;
    set<pair<int, pair<int,int>>> FF;
    FF.insert({0, {nodo, k}});
    dist[nodo][k] = 0;

    while(!FF.empty()){
        nodo = FF.begin()->second.first, k = FF.begin()->second.second;

        int nd = FF.begin()->first;
        if(nodo == N)
            return nd;

        FF.erase(FF.begin());

        if(nd == dist[nodo][k]){
            if(k == K && dist[nodo + 1][0] > dist[nodo][k]){
                dist[nodo + 1][0] = dist[nodo][k];
                FF.insert({dist[nodo + 1][0], {nodo + 1, 0}});
            }
            int nuke = min(K, k + carota[nodo]);
            if(dist[nodo + 1][nuke] > dist[nodo][k] + tempReq[nodo]){
                dist[nodo + 1][nuke] = dist[nodo][k] + tempReq[nodo];
                FF.insert({dist[nodo + 1][nuke], {nodo + 1, nuke}});
            }
        }
    }
}

int main(){
    cin >> N >> K;

    for(int i = 0; i < N + 1; i++)
        for(int k = 0; k <= K; k++)
            dist[i][k] = INT_MAX >> 1;

    for(int i = 0; i < N; i++)
        cin >> tempReq[i];
    for(int i = 0; i < N; i++)
        cin >> carota[i];

    cout<<bfs()<<"\n";
}
