#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll fastin() {
    ll v = 0;
    char c = getchar_unlocked();
    while (c >= '0') {
        v = v * 10 + c - '0';
        c = getchar_unlocked();
    }
    return v;
}

int main() {
    int n = fastin();

    ll res = 0;

    while (n--) {
        ll books = fastin();
        ll target = (1ll << (64 - __builtin_clzll(books))) - 1;

        res += target - books;
    }

    cout << res << "\n";
}
