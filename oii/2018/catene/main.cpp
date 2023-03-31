#include <bits/stdc++.h>
#define MAXN 1000005
using namespace std;
typedef pair<int, int> pii;
typedef pair<long long, long long> pllll;
vector<pii> grafo[MAXN];
pllll valore[MAXN];

void dfs(int node, int padre, int valPadre){
    //cout<<node<<" "<<padre<<" "<<valPadre<<endl;
    int n = grafo[node].size();
    long long sommaSec = 0;
    long long nodiBest[grafo[node].size()];
    for(int i = 0; i < grafo[node].size(); i++){
        if(grafo[node][i].first != padre){
            dfs(grafo[node][i].first, node, grafo[node][i].second);
            sommaSec+= valore[grafo[node][i].first].second;
            nodiBest[i] = {valore[grafo[node][i].first].first - valore[grafo[node][i].first].second};
        }
        else
            nodiBest[i] = 0;
    }
    long long valMaxSec = 0;
    sort(nodiBest, nodiBest + grafo[node].size());
    valMaxSec = max(valMaxSec, nodiBest[n - 1]);
    if(n >= 2)
        valMaxSec = max(valMaxSec, nodiBest[n - 1] + nodiBest[n - 2]);

    valore[node].second = valMaxSec + sommaSec;
    if(valPadre > 0){ // se il padre non esiste valPadre sarà 0
        long long valMaxPrim = 0;
        for(int i = 0; i < grafo[node].size(); i++){ // con il nodo padre e con il nodo i
            if(padre != grafo[node][i].first)
                valMaxPrim = max(valMaxPrim, valore[grafo[node][i].first].first - valore[grafo[node][i].first].second);
        }
        valore[node].first = valMaxPrim + valPadre + sommaSec;
    }
    //cout<<"| "<<node<<" "<<valore[node].first<<" "<<valore[node].second<<" sommasec = "<<sommaSec<<endl;
}

long long profitto_massimo(int N, int U[], int V[], int W[]){
    //cout<<endl<<"---------------------\n\n";
    for(int i = 0; i < N - 1; i++){
        grafo[U[i]].push_back({V[i], W[i]});
        grafo[V[i]].push_back({U[i], W[i]});
    }
    dfs(1, 0, 0);
    return valore[1].second;
}
