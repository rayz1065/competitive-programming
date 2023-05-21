#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

int N, M;

vector<int> grafo[MAXN];
vector<int> revGrafo[MAXN];
stack<int> ord;

int comp[MAXN];
bool pointedAt[MAXN];

void init(){
    cin >> N >> M;
    for(int i = 0; i < N; i++)
        grafo[i].clear(), revGrafo[i].clear();

    fill(pointedAt, pointedAt + N, false);
    fill(comp, comp + N, -1);

    while(!ord.empty())
        ord.pop();

    for(int i = 0; i < M; i++){
        int da, a;
        cin >> da >> a;
        da--, a--;
        grafo[da].push_back(a);
        revGrafo[a].push_back(da);
    }
}

bool visited[MAXN];

void dfs(int nodo){
    visited[nodo] = true;
    for(auto i:grafo[nodo])
        if(!visited[i])
            dfs(i);
    ord.push(nodo);
}

int currComp;

void assignComp(int nodo){
    comp[nodo] = currComp;
    for(auto i:revGrafo[nodo])
        if(comp[i] == -1)
            assignComp(i);
}

int solve(){
    fill(visited, visited + N, false);
    for(int i = 0; i < N; i++)
        if(!visited[i])
            dfs(i);

    currComp = 0;
    while(!ord.empty()){
        int nodo = ord.top();
        ord.pop();
        if(comp[nodo] == -1)
            assignComp(nodo), currComp++;
    }

    for(int i = 0; i < N; i++){
        for(auto j:grafo[i]){
            if(comp[j] != comp[i])
                pointedAt[comp[j]] = true;
        }
    }

    int S = 0;
    for(int i = 0; i < currComp; i++)
        S+= !pointedAt[i];
    return S;
}

int main(){
    FILE *out = stdout;

    int T;
    cin >> T;

    for(int t = 1; t <= T; t++){
        init();
        fprintf(out, "%d\n", solve());
    }
}
