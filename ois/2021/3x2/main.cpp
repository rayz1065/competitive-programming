#include <bits/stdc++.h>
#pragma GCC optimize("O3")

using namespace std;
int price_freq[1005];

int fastin() {
    int v = 0;
    char c = getchar_unlocked();
    while (c >= '0') {
        v = v * 10 + c - '0';
        c = getchar_unlocked();
    }
    return v;
}

int main () {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n = fastin();
    for (int i = 0; i < n; i++) {
        int p = fastin();
        price_freq[p]++;
    }
    int s = 0;
    int k = 0;
    for (int i = 1000; i >= 0; i--) {
        int must_buy = price_freq[i] - price_freq[i] % 3;
        price_freq[i]-= must_buy;
        s += (i * must_buy) / 3 * 2;
        while (price_freq[i] > 0) {
            price_freq[i]--;
            if (k < 2) {
                s += i;
            }
            k = (k + 1) % 3;
        }
    }
    cout << s << "\n";
}
