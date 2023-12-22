#include <bits/stdc++.h>
#define MAXN 100005
#define ROOT_NODE 0
using namespace std;

int n, m;
long long int s;

long long int edgeWeight[MAXN];
long long int edgeFreq[MAXN];

long long int currSum;
vector<pair<int, int>> grafo[MAXN];
set<pair<long long int, int>> edges;

void init(){
    cin >> n >> s;
    m = n - 1;

    for(int i = 0; i < n; i++)
        grafo[i].clear();
    memset(edgeFreq, 0, sizeof edgeFreq);
    edges.clear();
    currSum = 0;

    for(int i = 0; i < m; i++){
        int a, b, w;
        cin >> a >> b >> edgeWeight[i];
        a--, b--;

        grafo[a].push_back({b, i});
        grafo[b].push_back({a, i});
    }
}

int findEdgeFreq(int node, int padre){
    if(grafo[node].size() == 1 && node != ROOT_NODE)
        return 1;

    int totalEdgeFreq = 0;

    for(auto i:grafo[node]){
        int j = i.first, e = i.second;
        if(j != padre){
            edgeFreq[e]+= findEdgeFreq(j, node);
            totalEdgeFreq+= edgeFreq[e];
        }
    }

    return totalEdgeFreq;
}

long long int getComb(int e){
    return edgeFreq[e]*edgeWeight[e];
}

long long int getCombHalfed(int e){
    return edgeFreq[e]*(edgeWeight[e]/2);
}

void addEdge(int e){
    edges.insert({getCombHalfed(e) - getComb(e), e});
    currSum+= getComb(e);
}

void halfEdge(int e){
    currSum-= getComb(e);
    edges.erase(edges.begin());
    edgeWeight[e] >>= 1;
    addEdge(e);
}

int solve(){
    findEdgeFreq(ROOT_NODE, -1);

    /*for(int node = 0; node < n; node++){
        for(auto i:grafo[node]){
            int j = i.first, e = i.second;
            cout<<node<<" => "<<j<<" edge "<<"(w = "<<edgeWeight[e]<<" f = "<<edgeFreq[e]<<")\n";
        }
    }*/

    int moves = 0;

    for(int e = 0; e < m; e++){
        addEdge(e);
    }

    while(currSum > s){
        moves++;

        int e = edges.begin() -> second;

        halfEdge(e);
    }

    return moves;
}

int main(){
    int t;
    cin >> t;

    while(t--){
        init();
        cout<<solve()<<"\n";
    }
}
