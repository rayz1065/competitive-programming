#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

typedef long long ll;

int n;
vector<int> graph[MAXN];
int distances[2][MAXN];
int fenwick[MAXN];

void fenwick_add(int idx, int amount) {
    idx += 1;
    while (idx < MAXN) {
        fenwick[idx] += amount;
        idx += idx & -idx;
    }
}

int fenwick_sum(int idx) {
    int res = 0;
    idx += 1;
    while (idx > 0) {
        res += fenwick[idx];
        idx -= idx & -idx;
    }
    return res;
}

void bfs(int source, int distances[]) {
    queue<int> ff;
    ff.push(source);
    for (int i = 0; i < n; i++) {
        distances[i] = INT_MAX >> 1;
    }
    distances[source] = 0;

    while (!ff.empty()) {
        int node = ff.front();
        ff.pop();
        for (auto j : graph[node]) {
            if (distances[j] == INT_MAX >> 1) {
                distances[j] = distances[node] + 1;
                ff.push(j);
            }
        }
    }
}

int fastin() {
    int v = 0;
    char c = getchar_unlocked();
    while (c >= '0') {
        v = v * 10 + c - '0';
        c = getchar_unlocked();
    }
    return v;
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    n = fastin();
    int m = fastin();
    for (int i = 0; i < m; i++) {
        int a = fastin(), b = fastin();
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    bfs(0, distances[0]);
    bfs(n - 1, distances[1]);

    int max_distance = distances[0][n - 1];

    vector<pair<int, int>> sorted_by_dist_0;
    vector<pair<int, int>> sorted_by_dist_1;
    for (int i = 0; i < n; i++) {
        sorted_by_dist_0.push_back({distances[0][i], i});
        sorted_by_dist_1.push_back({distances[1][i], i});
    }
    sort(sorted_by_dist_0.begin(), sorted_by_dist_0.end());
    sort(sorted_by_dist_1.begin(), sorted_by_dist_1.end());

    int l1 = n - 1;  // decrease distance from n - 1

    ll res = 0;
    for (auto sorted_iter : sorted_by_dist_0) {
        int i = sorted_iter.second;

        // include all vertices with distance >= target_distance
        int target_distance = max_distance - distances[0][i] - 1;
        while (l1 >= 0 && sorted_by_dist_1[l1].first >= target_distance) {
            int j = sorted_by_dist_1[l1].second;
            fenwick_add(distances[0][j], 1);
            l1 -= 1;
        }

        // only those with distance >= source_distance can be included
        int source_distance = max_distance - distances[1][i] - 1;
        res += fenwick_sum(n) - fenwick_sum(source_distance - 1);
    }

    res -= n;  // self-loops
    assert(res % 2 == 0);
    res /= 2;  // double-counting
    res -= m;  // already existing edges

    cout << res << "\n";
}
