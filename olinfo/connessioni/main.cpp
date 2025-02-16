#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

int parent[MAXN];
int ranks[MAXN];
int ccs = 0;

void inizia(int n) {
    ccs = n;
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        ranks[i] = 0;
    }
}

int get_parent(int x) {
    if (parent[x] == x) {
        return x;
    }
    return parent[x] = get_parent(parent[x]);
}

int collega(int x, int y) {
    x = get_parent(x);
    y = get_parent(y);
    if (x == y) {
        return ccs;
    }

    ccs -= 1;
    if (ranks[x] == ranks[y]) {
        ranks[x] += 1;
        parent[y] = x;
    } else if (ranks[x] < ranks[y]) {
        parent[x] = y;
    } else {
        parent[y] = x;
    }

    return ccs;
}
