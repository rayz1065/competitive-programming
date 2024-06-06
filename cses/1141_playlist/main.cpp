#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

int n;
int values[MAXN];

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> values[i];
    }

    map<int, int> frequencies;

    int best = 0;

    for (int i = 0, j = 0; i < n; i++) {
        frequencies[values[i]] += 1;
        while (frequencies[values[i]] > 1) {
            frequencies[values[j]] -= 1;
            j += 1;
        }

        best = max(best, i - j + 1);
    }

    cout << best << "\n";
}
