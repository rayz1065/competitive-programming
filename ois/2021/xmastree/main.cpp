#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define MAXN 200005

using namespace std;

typedef long long ll;

int n;
vector<int> graph[MAXN];
int niceness[MAXN];
struct NodeInfo {
    ll best_odd;
    ll best_even;
};

NodeInfo solve (int node, int parent) {
    vector<NodeInfo> ch_sols;
    for (auto j: graph[node]) {
        if (j != parent) {
            ch_sols.push_back(solve(j, node));
        }
    }
    if (ch_sols.size() == 0) {
        return { 0, niceness[node] };
    }
    NodeInfo s;
    ll best_sum = 0, min_diff = LLONG_MAX >> 1;
    bool best_sum_odd = false;
    for (auto &j: ch_sols) {
        if (j.best_even >= j.best_odd) {
            best_sum += j.best_even;
            min_diff = min(min_diff, j.best_even - j.best_odd);
        } else {
            best_sum += j.best_odd;
            best_sum_odd = !best_sum_odd;
            min_diff = min(min_diff, j.best_odd - j.best_even);
        }
    }
    if (best_sum_odd) {
        s.best_odd = best_sum;
        s.best_even = best_sum - min_diff;
    } else {
        s.best_odd = best_sum - min_diff;
        s.best_even = best_sum;
    }
    s.best_even += niceness[node];
    // cout << "For " << node << " best sum = " << best_sum << " (" << best_sum_odd << "), solve(" << node << ") = " << s.best_odd << ", " << s.best_even << "\n";
    return s;
}

int main () {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    for (int i = 0; i < n; i++) {
        cin >> niceness[i];
    }
    auto res = solve(0, -1);
    cout << max(res.best_even, res.best_odd) << "\n";
}
