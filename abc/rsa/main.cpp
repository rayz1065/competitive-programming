#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int fast_pow (int c, int d, int mod) {
    if (!d) return 1;
    ll s = fast_pow(c, d >> 1, mod);
    if (d & 1) return (((s * s) % mod) * c) % mod;
    return (s * s) % mod;
}

void decifra (int n, int d, int l, int* messaggio, char* plaintext) {
    for (int i = 0; i < l; i++) {
        plaintext[i] = fast_pow(messaggio[i], d, n);
    }
}
