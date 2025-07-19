#include <bits/stdc++.h>
#define MAX_FIBO 46
#define MAXN 100005

using namespace std;

typedef long long ll;

int fibo[MAX_FIBO];
int values[MAX_FIBO];
ll memo[MAX_FIBO][MAXN];

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
    int n = fastin(), k = fastin();
    fill(values, values + MAX_FIBO, 0);
    for (int i = 0; i < n; i++) {
        int cost = fastin(), value = fastin();
        if (cost < MAX_FIBO) {
            values[cost] = max(values[cost], value);
        }
    }

    for (int i = MAX_FIBO - 2; i >= 0; i--) {
        for (int j = fibo[i]; j <= k; j++) {
            memo[i][j] = max(memo[i + 1][j], memo[i][j - fibo[i]] + values[i]);
        }
    }

    cout << memo[0][k] << "\n";
}

int main() {
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    fibo[0] = fibo[1] = 1;
    for (int i = 2; i < MAX_FIBO; i++) {
        fibo[i] = fibo[i - 1] + fibo[i - 2];
    }

    int t = fastin();
    while (t--) tc();
}
