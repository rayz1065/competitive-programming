#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

typedef long long ll;

int n;
int values[MAXN];
int nxt_max[MAXN];
int nxt_min[MAXN];

ll memo[MAXN];

int fastin() {
    int v = 0;
    char c = getchar_unlocked();
    while (c >= '0') {
        v = v * 10 + c - '0';
        c = getchar_unlocked();
    }
    return v;
}

void tc() {
    n = fastin();
    for (int i = 0; i < n; i++) {
        values[i] = fastin();
    }

    for (int i = 0; i < n;) {
        int nxt;
        for (nxt = i + 1; nxt < n && values[nxt] >= values[nxt - 1]; nxt++);
        fill(nxt_min + i, nxt_min + nxt, nxt - 1);
        i = nxt;
    }

    for (int i = 0; i < n;) {
        int nxt;
        for (nxt = i + 1; nxt < n && values[nxt] <= values[nxt - 1]; nxt++);
        fill(nxt_max + i, nxt_max + nxt, nxt - 1);
        i = nxt;
    }

    memo[n] = 0;
    for (int i = n - 1; i >= 0; i--) {
        ll res = memo[i + 1];
        int v = values[i];
        res = max(res, memo[nxt_max[i] + 1] + abs(values[nxt_max[i]] - v));
        res = max(res, memo[nxt_min[i] + 1] + abs(values[nxt_min[i]] - v));
        if (nxt_min[i] > i) {
            res = max(res, memo[nxt_min[i]] + abs(values[nxt_min[i] - 1] - v));
        }
        if (nxt_max[i] > i) {
            res = max(res, memo[nxt_max[i]] + abs(values[nxt_max[i] - 1] - v));
        }
        memo[i] = res;
    }

    cout << memo[0] << "\n";
}

int main() {
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int t = fastin();
    while (t--) tc();
}
