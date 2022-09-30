#include <bits/stdc++.h>
#define MAXN 50001
#define MAXM 100001
using namespace std;

int N, M;
int partenza[MAXM], arrivo[MAXM], dist[MAXN];
bool visited[MAXN];
vector<pair<int, int> > grafo[MAXN];

int djikistra(int da, int a){
    set<pair<int, int> > FF;
    FF.insert({0, da});
    dist[da] = 0;
    while(!FF.empty()){
        int nodo = FF.begin()->second;
        FF.erase(FF.begin());
        if(!visited[nodo]){
            visited[nodo] = true;
            for(auto i:grafo[nodo]){
                /// l'arco in questo caso è i.second, il nodo di arrivo i.first
                if(partenza[i.second] >= dist[nodo] && dist[i.first] > arrivo[i.second]){
                    dist[i.first] = arrivo[i.second];
                    FF.insert({arrivo[i.second], i.first});
                }
            }
        }
    }
    return dist[a];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;

    int S, E;
    cin >> S >> E >> M;

    for(int i = 0; i < M; i++){
        int da, a;
        cin >> da >> partenza[i] >> a >> arrivo[i];
        grafo[da].push_back({a, i});
    }
    fill(dist, dist + N, INT_MAX/2);

    int distanza = djikistra(S, E);
    if(!visited[E])
        cout<<"IMPOSSIBLE\n";
    else
        cout<<distanza;
    cout<<endl;
}
