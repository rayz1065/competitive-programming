#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

int n;
int values[MAXN];

int fastin() {
    int v = 0;
    char c = getchar_unlocked();
    while (c >= '0') {
        v = v * 10 + c - '0';
        c = getchar_unlocked();
    }
    return v;
}

bool check_sorted(int first_idx) {
    for (int i = 0; i < n - 1; i++) {
        int j = (i + first_idx) % n;
        if (values[j] > values[(j + 1) % n]) {
            return false;
        }
    }

    return true;
}

int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    n = fastin();
    for (int i = 0; i < n; i++) {
        values[i] = fastin();
    }

    int min_idx = min_element(values, values + n) - values;
    if (!check_sorted(min_idx)) {
        cout << "-1\n";
        return 0;
    }

    cout << (n - min_idx) % n << "\n";
}
