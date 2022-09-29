#include <bits/stdc++.h>
#define MAXN 200005
#define LOG 20
using namespace std;
int N, Q;
int tempoEntrata[MAXN], tempoUscita[MAXN], tempo = 0;
vector<int> albero[MAXN];
int up[MAXN][LOG];
int depth[MAXN];

void computeUp(int nodo, int padre, int d){
    tempoEntrata[nodo] = tempo++;
    depth[nodo] = d;

    if(padre != 0){
        int nodoScorre;
        up[nodo][0] = nodoScorre = padre;
        for(int i = 1; i < LOG; i++){
            up[nodo][i] = up[nodoScorre][i - 1];
            nodoScorre = up[nodoScorre][i - 1];
        }
    }
    for(auto i:albero[nodo])
        if(i != padre)
            computeUp(i, nodo, d + 1);

    tempoUscita[nodo] = tempo++;
}

bool isAncestor(int a, int b){ // se a è una discendenza di b
    return (tempoEntrata[a] >= tempoEntrata[b] && tempoUscita[a] <= tempoUscita[b]);
}

int lca(int a, int b){
    if(isAncestor(a, b))
        return b;
    if(isAncestor(b, a))
        return a;
    for(int i = LOG - 1; i >= 0; i--){
        if(up[a][i] > 0 && !isAncestor(b, up[a][i]))
            a = up[a][i];
    }
    return up[a][0];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin>>N>>Q;
    for(int i = 0; i < N - 1; i++){
        int a, b;
        cin>>a>>b;
        albero[a].push_back(b);
        albero[b].push_back(a);
    }

    computeUp(1, 0, 0);

    /*cout<<"\nTabella lca\n\n";
    for(int i = 1; i <= N; i++){
        cout<<i<<" -> ";
        for(int j = 1; j <= N; j++){
            cout<<lca(i, j)<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n-----------------\n\n";*/

    for(int i = 0; i < Q; i++){
        int a, b;
        cin>>a>>b;
        int lowComAnc = lca(a, b);
        int d = depth[b] - depth[lowComAnc]*2 + depth[a];
        cout<<d<<"\n";
    }
}
