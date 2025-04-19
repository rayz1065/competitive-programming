#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

int n;
int team[MAXN];
vector<int> graph[MAXN];

bool dfs(int node) {
    for (auto i : graph[node]) {
        if (!team[i]) {
            team[i] = 3 - team[node];
            if (!dfs(i)) {
                return false;
            }
        } else if (team[i] == team[node]) {
            return false;
        }
    }

    return true;
}

bool solve() {
    for (int i = 0; i < n; i++) {
        if (!team[i]) {
            team[i] = 1;
            if (!dfs(i)) {
                return false;
            }
        }
    }

    return true;
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int m;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    if (!solve()) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    for (int i = 0; i < n; i++) {
        cout << team[i] << " \n"[i + 1 == n];
    }
}
