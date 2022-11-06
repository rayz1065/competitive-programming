#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

int n, m;
struct Branch {
    int i;
    int to;
    int delta;
};

int potential[MAXN];
vector<Branch> graph[MAXN];

bool dfs (int k, int node) {
    for (auto j: graph[node]) {
        if (j.i <= k) {
            int new_pot = potential[node] + j.delta;
            if (potential[j.to] == (INT_MAX >> 1)) {
                potential[j.to] = new_pot;
                if (!dfs(k, j.to)) {
                    return false;
                }
            } else if (potential[j.to] != new_pot) {
                return false;
            }
        }
    }
    return true;
}

bool is_sol (int k) {
    fill(potential, potential + MAXN, INT_MAX >> 1);
    for (int i = 0; i < n; i++) {
        if (potential[i] == (INT_MAX >> 1)) {
            potential[i] = 0;
            if (!dfs(k, i)) {
                return false;
            }
        }
    }
    return true;
}

int solve () {
    int l = 0, r = m - 1, s = -1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (is_sol(mid)) {
            l = mid + 1, s = mid;
        } else {
            r = mid - 1;
        }
    }
    return s;
}

int main () {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b, delta;
        cin >> a >> b >> delta;
        graph[a].push_back({ i, b, delta });
        graph[b].push_back({ i, a, -delta });
    }
    cout << solve() + 1 << "\n";
}
