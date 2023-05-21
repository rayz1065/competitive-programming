#include <bits/stdc++.h>
#define MAXN 2005

using namespace std;

int N, M;

vector<int> grafo[MAXN];
stack<int> ord;
bool visited[MAXN];

bool init(){
    cin >> N >> M;
    if(N == 0 && M == 0)
        return false;
    while(!ord.empty())
        ord.pop();

    for(int i = 0; i < N; i++)
        grafo[i].clear();

    for(int i = 0; i < M; i++){
        int u, w, p;
        cin >> u >> w >> p;
        u--, w--;

        grafo[u].push_back(w);
        if(p == 2)
            grafo[w].push_back(u);
    }
    return true;
}

void dfs(int nodo){
    visited[nodo] = true;
    for(auto i:grafo[nodo])
        if(!visited[i])
            dfs(i);
    ord.push(nodo);
}

bool solve(){
    for(int i = 0; i < N; i++){
        fill(visited, visited + N, false);
        dfs(i);
        for(int j = 0; j < N; j++)
            if(!visited[j])
                return false;
    }
    return true;
}

int main(){
    while(init()){
        cout<<solve()<<"\n";
    }
}
