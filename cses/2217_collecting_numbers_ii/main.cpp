#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

int n;
int values[MAXN];
int position[MAXN];

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int q_queries;
    cin >> n >> q_queries;

    for (int i = 0; i < n; i++) {
        cin >> values[i];
        values[i]--;
        position[values[i]] = i;
    }

    int res = 1;
    for (int i = 1; i < n; i++) {
        res += position[i] < position[i - 1];
    }

    while (q_queries--) {  // noqa
        int a, b;
        cin >> a >> b;
        a--, b--;

        // removes the effect of values[a] and values[b]
        // avoids double counting
        res -= values[a] == 0 ? 0 : (a < position[values[a] - 1]);
        res -= values[a] == n - 1 ? 0 : (position[values[a] + 1] < a);
        res -= values[b] == 0 || values[a] == values[b] - 1
                   ? 0
                   : (b < position[values[b] - 1]);
        res -= values[b] == n - 1 || values[a] == values[b] + 1
                   ? 0
                   : (position[values[b] + 1] < b);

        swap(values[a], values[b]);
        position[values[a]] = a;
        position[values[b]] = b;

        // adds back the effect of values[a] and values[b]
        // avoids double counting
        res += values[a] == 0 ? 0 : (a < position[values[a] - 1]);
        res += values[a] == n - 1 ? 0 : (position[values[a] + 1] < a);
        res += values[b] == 0 || values[a] == values[b] - 1
                   ? 0
                   : (b < position[values[b] - 1]);
        res += values[b] == n - 1 || values[a] == values[b] + 1
                   ? 0
                   : (position[values[b] + 1] < b);

        cout << res << "\n";
    }
}
