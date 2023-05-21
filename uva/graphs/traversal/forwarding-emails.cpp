#include <bits/stdc++.h>
#define MAXN 50005

using namespace std;


int N;
//vector<int> grafo[MAXN];
int dire[MAXN];
bool visited[MAXN];
int memo[MAXN];

void init(){
    cin >> N;
    /*for(int i = 1; i <= N; i++)
        grafo[i].clear();*/
    fill(visited + 1, visited + N + 1, false);
    fill(memo + 1, memo + N + 1, -1);

    for(int i = 0; i < N; i++){
        int da, a;
        cin >> da >> a;
        dire[da] = a;
        //grafo[a].push_back(da);
    }
}

void dfs(int node){
    visited[node] = true;
    memo[node] = -1;

    if(visited[dire[node]]){
        if(memo[dire[node]] == -1){
            int dim = 1, orageno = node;
            node = dire[node];
            while(node != orageno)
                dim++, node = dire[node];
            memo[node] = dim, node = dire[node];
            while(node != orageno)
                memo[node] = dim, node = dire[node];
        }
        else
            memo[node] = memo[dire[node]] + 1;
    }
    else{
        dfs(dire[node]);
        if(memo[node] == -1)
            memo[node] = memo[dire[node]] + 1;
    }
}

int solve(){
    int maxD = 0, bestNode;
    for(int i = 1; i <= N; i++){
        if(!visited[i]){
            dfs(i);
            if(memo[i]> maxD)
                maxD = memo[i], bestNode = i;
        }
    }
    return bestNode;
}

int main(){
    FILE *out = stdout;

    int T;
    cin >> T;

    for(int t = 1; t <= T; t++){
        init();
        fprintf(out, "Case %d: %d\n", t, solve());
    }
}
