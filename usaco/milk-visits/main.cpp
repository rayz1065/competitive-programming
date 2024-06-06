#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

int n;
vector<int> graph[MAXN];
int milk_type[MAXN];
int depth[MAXN], heavy[MAXN], parent[MAXN];

// heavy light
int hl_next_index, hl_index[MAXN], hl_root[MAXN];

set<int> cow_locations[MAXN];

int dfs(int node) {
    int res = 1;
    int max_size = -1;
    heavy[node] = -1;

    for (auto j : graph[node]) {
        if (j != parent[node]) {
            parent[j] = node;
            depth[j] = depth[node] + 1;
            int sub_res = dfs(j);
            res += sub_res;

            if (sub_res > max_size) {
                max_size = sub_res;
                heavy[node] = j;
            }
        }
    }

    return res;
}

void hl_decompose(int node) {
    hl_index[node] = hl_next_index++;

    if (heavy[node] != -1) {
        hl_root[heavy[node]] = hl_root[node];
        hl_decompose(heavy[node]);
    }

    for (auto j : graph[node]) {
        if (j != parent[node] && j != heavy[node]) {
            hl_root[j] = j;
            hl_decompose(j);
        }
    }
}

bool find_on_path(int a, int b, int value) {
    while (hl_root[a] != hl_root[b]) {
        if (depth[hl_root[a]] > depth[hl_root[b]]) {
            swap(a, b);
        }

        int lo = hl_index[hl_root[b]];
        int hi = hl_index[b];
        auto it = cow_locations[value].lower_bound(lo);

        if (it != cow_locations[value].end() && *it <= hi) {
            return true;
        }

        b = parent[hl_root[b]];
    }

    if (depth[a] > depth[b]) {
        swap(a, b);
    }

    int lo = hl_index[a];
    int hi = hl_index[b];
    auto it = cow_locations[value].lower_bound(lo);

    return it != cow_locations[value].end() && *it <= hi;
}

int main() {
#ifndef DEBUG
    fstream cin, cout;
    cin.open("milkvisits.in", ios::in);
    cout.open("milkvisits.out", ios::out);
#endif
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int q;
    cin >> n >> q;

    for (int i = 0; i < n; i++) {
        cin >> milk_type[i];
    }

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    dfs(0);
    hl_decompose(0);

    for (int i = 0; i < n; i++) {
        cow_locations[milk_type[i]].insert(hl_index[i]);
    }

    while (q--) {
        int a, b, value;
        cin >> a >> b >> value;
        a--, b--;

        cout << find_on_path(a, b, value);
    }

    cout << "\n";
}
