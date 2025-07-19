#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

int n, heights[MAXN];
pair<int, int> order[MAXN];
int ufds_p[MAXN];
int ufds_max[MAXN];
int ufds_rank[MAXN];

void ufds_init() {
    for (int i = 0; i < n; i++) {
        ufds_max[i] = 0;
        ufds_rank[i] = 0;
        ufds_p[i] = i;
    }
}

int ufds_getp(int node) {
    if (ufds_p[node] == node) {
        return node;
    }
    return ufds_p[node] = ufds_getp(ufds_p[node]);
}

void ufds_merge(int a, int b) {
    a = ufds_getp(a), b = ufds_getp(b);
    if (a == b) {
        return;
    }

    if (ufds_rank[a] < ufds_rank[b]) {
        swap(a, b);
    } else if (ufds_rank[a] == ufds_rank[b]) {
        ufds_rank[a] += 1;
    }
    ufds_p[b] = a;
    ufds_max[a] = max(ufds_max[a], ufds_max[b]);
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> heights[i];
        order[i] = {heights[i], i};
    }

    sort(order, order + n);
    ufds_init();

    for (int ord_id = 0; ord_id < n;) {
        int height = order[ord_id].first, start = ord_id;
        for (; order[ord_id].first == height; ord_id++) {
            int i = order[ord_id].second;
            ufds_max[i] = 1;
            if (i > 0 && height > heights[i - 1]) {
                ufds_max[i] = max(ufds_max[i], ufds_max[ufds_getp(i - 1)] + 1);
            }
            if (i + 1 < n && height > heights[i + 1]) {
                ufds_max[i] = max(ufds_max[i], ufds_max[ufds_getp(i + 1)] + 1);
            }
        }
        for (int ord_id_2 = start; ord_id_2 < ord_id; ord_id_2++) {
            int i = order[ord_id_2].second;
            if (i > 0 && height >= heights[i - 1]) {
                ufds_merge(i, i - 1);
            }
            if (i + 1 < n && height >= heights[i + 1]) {
                ufds_merge(i, i + 1);
            }
        }
    }

    cout << ufds_max[ufds_getp(0)] << "\n";
}
