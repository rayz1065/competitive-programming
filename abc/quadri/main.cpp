#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
int quadri (int n, ll m, int* v) {
    ll s = 0;
    int r = 0;
    for (; r < n && s + v[r] <= m; s += v[r++]);
    int b = r, l = 0;
    while (r < n) {
        if (s + v[r] <= m) s += v[r++];
        else s -= v[l++], b = min(b, r - l + 1);
    }
    return b;
}
