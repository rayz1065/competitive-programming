#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int ContaOperazioni (int n, int k, int* secchi) {
    ll delta_p = 0, delta_m = 0;
    for (int i = 0; i < n; i++) {
        int c = secchi[i];
        if (c > k) delta_p += c - k;
        else delta_m += k - c;
    }
    return max(delta_p, delta_m);
}
