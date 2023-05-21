#include <bits/stdc++.h>
#define MAXN 1005

using namespace std;

vector<pair<int, int>> grafo[MAXN];
int dist[MAXN];

int N, M;

void init(){
    cin >> N >> M;

    fill(dist, dist + N, INT_MAX >> 1);
    for(int i = 0; i < N; i++)
        grafo[i].clear();

    for(int i = 0; i < M; i++){
        int a, b, w;
        cin >> a >> b >> w;

        grafo[a].push_back({b, w});
    }
}

bool solve(){
    for(int i = 0; i < M; i++)
        for(int i = 0; i < N; i++)
            for(auto j:grafo[i])
                dist[j.first] = min(dist[j.first], dist[i] + j.second);

    for(int i = 0; i < N; i++)
        for(auto j:grafo[i])
            if(dist[j.first] > dist[i] + j.second)
                return true;
    return false;
}

int main(){
    FILE *out = stdout;

    int T;
    cin >> T;

    for(int t = 1; t <= T; t++){
        init();

        fprintf(out, "%s\n", solve() ? "possible" : "not possible");
    }
}
