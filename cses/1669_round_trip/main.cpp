#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

int n;
vector<int> graph[MAXN];
int parent[MAXN];
int depth[MAXN];

pair<int, int> dfs(int node) {
    for (auto i : graph[node]) {
        if (parent[node] == i) {
            continue;
        } else if (parent[i] != -1) {
            return {node, i};
        }
        parent[i] = node;
        depth[i] = depth[node] + 1;
        auto res = dfs(i);
        if (res.first != -1) {
            return res;
        }
    }
    return {-1, -1};
}

pair<int, int> solve() {
    fill(parent, parent + n, -1);

    for (int i = 0; i < n; i++) {
        if (parent[i] != -1) {
            continue;
        }
        parent[i] = i;
        auto res = dfs(i);
        if (res.first != -1) {
            return res;
        }
    }
    return {-1, -1};
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    auto res = solve();
    if (res.first == -1) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    vector<int> loop_a, loop_b;
    int a = res.first, b = res.second;
    while (a != b) {
        if (depth[a] > depth[b]) {
            loop_a.push_back(a);
            a = parent[a];
        } else if (depth[b] > depth[a]) {
            loop_b.push_back(b);
            b = parent[b];
        } else {
            loop_a.push_back(a);
            loop_b.push_back(b);
            a = parent[a];
            b = parent[b];
        }
    }
    loop_a.push_back(a);
    loop_b.push_back(a);

    reverse(loop_a.begin(), loop_a.end());

    cout << loop_a.size() + loop_b.size() << "\n";
    for (auto i : loop_a) {
        cout << i + 1 << " ";
    }
    for (auto i : loop_b) {
        cout << i + 1 << " ";
    }
    cout << "\n";
}
