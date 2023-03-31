#include <bits/stdc++.h>
#define MAXN 1000005

using namespace std;

int n;
int heights[MAXN];

pair<int, int> chiedi(int x) {
    int l, r;
    for (l = x; l > 0 && heights[l] <= heights[x]; l--);
    for (r = x; r < n - 1 && heights[r] <= heights[x]; r++);
    return { l, r };
}

void cambia(int x, int h) {
    heights[x] = h;
}

void inizializza(int N, vector<int> H) {
    n = N;
    for (int i = 0; i < n; i++) {
        heights[i] = H[i];
    }
}
