#include <bits/stdc++.h>
#define MAXN 105
#define MAXV 1005005

using namespace std;

int n;
int coins[MAXN];
bool found[2][MAXV];

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int maxv = 1;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> coins[i];
        maxv += coins[i];
    }

    found[1][0] = true;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < maxv; j++) {
            found[i % 2][j] =
                found[(i + 1) % 2][j] ||
                (j - coins[i] >= 0 && found[(i + 1) % 2][j - coins[i]]);
        }
    }

    vector<int> res;
    res.reserve(maxv);

    for (int i = 1; i < maxv; i++) {
        if (found[(n + 1) % 2][i]) {
            res.push_back(i);
        }
    }

    cout << res.size() << "\n";
    for (auto i : res) {
        cout << i << " ";
    }
    cout << "\n";
}
