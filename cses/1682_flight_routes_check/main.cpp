#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

int n;
vector<int> graph[MAXN];
vector<int> reverse_graph[MAXN];
bool visited[MAXN];

void dfs(int node) {
    visited[node] = true;

    for (auto j : graph[node]) {
        if (!visited[j]) {
            dfs(j);
        }
    }
}

void reverse_dfs(int node) {
    visited[node] = true;

    for (auto j : reverse_graph[node]) {
        if (!visited[j]) {
            reverse_dfs(j);
        }
    }
}

int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int m;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        graph[a].push_back(b);
        reverse_graph[b].push_back(a);
    }

    dfs(0);

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            cout << "NO\n" << 1 << " " << i + 1 << "\n";
            return 0;
        }
    }

    fill(visited, visited + n, false);
    reverse_dfs(0);

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            cout << "NO\n" << i + 1 << " " << 1 << "\n";
            return 0;
        }
    }

    cout << "YES\n";
}
