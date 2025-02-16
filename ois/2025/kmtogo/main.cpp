#include <bits/stdc++.h>

using namespace std;

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;
    int res[10] = {};

    for (int i = 0; i <= n; i++) {
        for (int j = i; j > 0; j /= 10) {
            res[j % 10] += 1;
        }
    }

    for (int i = 0; i < 10; i++) {
        cout << res[i] << " \n"[i + 1 == 10];
    }
}
