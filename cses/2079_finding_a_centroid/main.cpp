#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

int n;
vector<int> graph[MAXN];
int centroid = -1;

int solve(int node, int parent) {
    int res = 1;
    bool is_centroid = true;
    for (auto i : graph[node]) {
        if (i == parent) {
            continue;
        }
        int child = solve(i, node);
        if (child > n / 2) {
            is_centroid = false;
        }
        res += child;
    }

    is_centroid = is_centroid && (res >= n / 2);
    if (is_centroid) {
        centroid = node;
    }

    return res;
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    solve(0, -1);
    cout << centroid + 1 << "\n";
}
