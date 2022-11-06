#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define MAXN 10005

using namespace std;

int n, m;
bitset<105> dna_seq[MAXN];
bool in_mst[MAXN];
int dist[MAXN];
int mst_size;

int count_differences (int i, int j) {
    return (dna_seq[i] ^ dna_seq[j]).count();
}

void mst_add (int i) {
    mst_size += dist[i];
    in_mst[i] = true;
    for (int j = 0; j < n; j++) {
        if (!in_mst[j]) {
            dist[j] = min(dist[j], count_differences(i, j));
        }
    }
    dist[i] = INT_MAX >> 1; // do not count as closest
}

int mst_closest () {
    return min_element(dist, dist + n) - dist;
}

int prim () {
    fill(in_mst, in_mst + n, false);
    fill(dist, dist + n, INT_MAX >> 1);
    dist[0] = m;
    mst_size = 0;
    for (int k = 0; k < n; k++) {
        int node = mst_closest();
        mst_add(node);
    }
    return mst_size;
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        string dna;
        cin >> dna;
        for (int j = 0; j < m; j++) {
            dna_seq[i].set(j, dna[j] == '1');
        }
    }
    cout << prim() << "\n";
}