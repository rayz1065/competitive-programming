#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

typedef long long ll;

int n;
int parent[MAXN], ufds_ranks[MAXN];

int get_parent(int node) {
    if (parent[node] == node) {
        return node;
    }

    return parent[node] = get_parent(parent[node]);
}

void ufds_union(int a, int b) {
    a = get_parent(a), b = get_parent(b);

    if (ufds_ranks[a] > ufds_ranks[b]) {
        parent[b] = a;
    } else if (ufds_ranks[b] > ufds_ranks[a]) {
        parent[a] = b;
    } else {
        parent[a] = b;
        ufds_ranks[b] += 1;
    }
}

void ufds_init() {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }
}

int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int m;

    cin >> n >> m;
    ufds_init();

    set<pair<int, pair<int, int>>> edges;

    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        a--, b--;
        edges.insert({w, {a, b}});
    }

    int ccs = n;
    ll total_cost = 0;
    while (ccs > 1 && !edges.empty()) {
        int w = edges.begin()->first;
        int a = edges.begin()->second.first;
        int b = edges.begin()->second.second;
        edges.erase(edges.begin());

        if (get_parent(a) != get_parent(b)) {
            ccs -= 1;
            ufds_union(a, b);
            total_cost += w;
        }
    }

    if (ccs == 1) {
        cout << total_cost << "\n";
    } else {
        cout << "IMPOSSIBLE\n";
    }
}
