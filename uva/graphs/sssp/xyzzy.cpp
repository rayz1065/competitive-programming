#include <bits/stdc++.h>
#define MAXN 105

using namespace std;

int maxEnergy[MAXN];
int energy[MAXN];
vector<int> grafo[MAXN];
bool visited[MAXN];

int N;
int M;

bool init(){
    cin >> N;
    if(N == -1)
        return false;

    M = 0;

    for(int i = 0; i < N; i++)
        grafo[i].clear();

    fill(maxEnergy, maxEnergy + N, -1);
    fill(visited, visited + N, false);

    for(int i = 0; i < N; i++){
        cin >> energy[i];
        int m;
        cin >> m;

        M+= m;

        for(int j = 0; j < m; j++){
            int a;
            cin >> a;
            a--;
            grafo[i].push_back(a);
        }
    }

    return true;
}

void dfs(int da){
    if(visited[da])
        return ;
    visited[da] = true;
    for(auto j:grafo[da])
        dfs(j);
}

bool dfs(int da, int a){
    dfs(da);
    return visited[a];
}

bool solve(){
    maxEnergy[0] = 100;
    for(int v = 0; v < N - 1; v++)
        for(int i = 0; i < N; i++){
            if(maxEnergy[i] <= 0)
                continue ;
            for(auto j:grafo[i])
                maxEnergy[j] = max(maxEnergy[i] + energy[j], maxEnergy[j]);
        }

    if(maxEnergy[N - 1] > 0)
        return true;

    for(int i = 0; i < N; i++){
        for(auto j:grafo[i])
            if(maxEnergy[i] > 0 && maxEnergy[i] + energy[j] > maxEnergy[j] && dfs(i, N - 1))
                return true;
    }
    return false;
}

int main(){
    FILE *out = fopen("output.txt", "w");

    for(int t = 1; init(); t++){
        fprintf(out, "%s\n", solve() ? "winnable" : "hopeless");
    }
}
