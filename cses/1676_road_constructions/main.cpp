#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

typedef long long ll;

int n;
int parent[MAXN], ufds_ranks[MAXN];
int ufds_size[MAXN];

int get_parent(int node) {
    if (parent[node] == node) {
        return node;
    }

    return parent[node] = get_parent(parent[node]);
}

void ufds_union(int a, int b) {
    a = get_parent(a), b = get_parent(b);

    if (ufds_ranks[a] > ufds_ranks[b]) {
        swap(a, b);
    }

    parent[a] = b;

    if (ufds_ranks[b] == ufds_ranks[a]) {
        ufds_ranks[b] += 1;
    }

    ufds_size[b] += ufds_size[a];
}

void ufds_init() {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        ufds_size[i] = 1;
    }
}

int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int m;

    cin >> n >> m;
    ufds_init();

    int ccs = n, largest_cc = 1;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;

        if (get_parent(a) != get_parent(b)) {
            ccs -= 1;
            ufds_union(a, b);
            a = get_parent(a);
            largest_cc = max(largest_cc, ufds_size[a]);
        }

        cout << ccs << " " << largest_cc << "\n";
    }
}
