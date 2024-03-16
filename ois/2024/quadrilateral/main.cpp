#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

typedef long long ll;

int n;
ll sides[MAXN];

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
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    n = fastin();
    for (int i = 0; i < n; i++) {
        sides[i] = fastin();
    }

    sort(sides, sides + n);

    for (int i = 0; i + 3 < n; i++) {
        if (sides[i] + sides[i + 1] + sides[i + 2] > sides[i + 3]) {
            cout << sides[i] << " " << sides[i + 1] << " " << sides[i + 2]
                 << " " << sides[i + 3] << "\n";
            return 0;
        }
    }
    cout << "-1\n";
}
