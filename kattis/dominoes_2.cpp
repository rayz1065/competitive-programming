#include <bits/stdc++.h>
#define MAXN 10005

using namespace std;

int n, m, l;

vector<int> graph[MAXN];

bool visited[MAXN];

void dfs(int i) {
    if(visited[i]) {
        return ;
    }
    visited[i] = true;

    for(auto j:graph[i]) {
        dfs(j);
    }
}

int main() {
    int t;
    cin >> t;

    while(t--) {
        cin >> n >> m >> l;
        fill(visited, visited + n + 1, 0);
        for(int i = 0; i <= n; i++) {
            graph[i].clear();
        }
        while(m--) {
            int x, y;
            cin >> x >> y;
            graph[x].push_back(y);
        }
        while(l--) {
            int x;
            cin >> x;
            dfs(x);
        }

        int s = 0;
        for(int i = 0; i < n + 1; i++) {
            s+= visited[i];
        }
        cout << s << "\n";
    }
}