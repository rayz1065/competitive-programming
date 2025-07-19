#include <bits/stdc++.h>
#define MAXN 1000005

using namespace std;

int n, f;
int cities[MAXN];

bool test(int distance) {
    int prev = cities[0];
    int i = 0;
    for (int missing = f - 1; missing; missing--) {
        for (; i < n && cities[i] < prev + distance; i++);
        if (cities[i] - prev < distance) {
            return false;
        }
        prev = cities[i];
    }
    return true;
}

int solve() {
    int l = 0, r = cities[n - 1] - cities[0], s = -1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (test(m)) {
            s = m;
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    return s;
}

int main() {
#ifndef DEBUG
    fstream cin, cout;
    cin.open("input.txt", ios::in);
    cout.open("output.txt", ios::out);
#else
    cin.tie(NULL);
    cout.tie(NULL);
#endif
    ios_base::sync_with_stdio(false);

    cin >> n >> f;
    for (int i = 0; i < n; i++) {
        cin >> cities[i];
    }

    cout << solve() << "\n";
}
