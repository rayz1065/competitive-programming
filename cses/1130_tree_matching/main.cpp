#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

int n;
vector<int> graph[MAXN];

pair<int, int> solve(int node, int parent) {
    // best-possible, best-not-using-(node, parent)
    pair<int, int> res = {node != parent, 0};

    int best_delta = 0;

    for (auto j : graph[node]) {
        if (j != parent) {
            auto child_res = solve(j, node);

            res.first += child_res.second;
            res.second += child_res.second;
            best_delta = max(best_delta, child_res.first - child_res.second);
        }
    }

    res.second += best_delta;

    return {max(res.first, res.second), res.second};
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    auto solution = solve(0, 0);

    cout << solution.first << "\n";
}
