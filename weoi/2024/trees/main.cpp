#include <bits/stdc++.h>
#define MAXN 500005
#define MOD 1000000007

using namespace std;

typedef long long ll;

struct Solution {
    int picked_1;
    int picked_2;
};

vector<int> graph[MAXN];

Solution solve(int node, int parent) {
    Solution res = {1, 0};

    for (auto j : graph[node]) {
        if (j == parent) {
            continue;
        }
        auto child = solve(j, node);
        res.picked_1 = ((ll)res.picked_1 * (child.picked_1 + 1)) % MOD;
        res.picked_2 =
            ((ll)res.picked_2 + child.picked_2 + child.picked_1) % MOD;
    }

    return res;
}

int count_sets(int n, vector<int> u, vector<int> v) {
    for (int i = 0; i < n - 1; i++) {
        graph[u[i]].push_back(v[i]);
        graph[v[i]].push_back(u[i]);
    }

    auto solution = solve(0, -1);

    return (solution.picked_1 + solution.picked_2) % MOD;
}
