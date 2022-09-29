#include <bits/stdc++.h>
#define MAXN 1000005

using namespace std;

int n;
bool in_set[MAXN];

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;
    if (n % 4 == 1 || n % 4 == 2) {
        cout << "NO\n";
        return 0;
    }
    if (n % 4 == 0) {
        for (int i = 1; i < n / 2; i += 2) {
            in_set[i] = in_set[n - i + 1] = true;
        }
    } else {
        for (int i = 1; i < (n + 1) / 2; i += 2) {
            in_set[i - 1] = in_set[(n + 1) - i] = true;
        }
    }

    cout << "YES\n";
    cout << n / 2 << "\n";
    for (int i = 1; i <= n; i++) {
        if (in_set[i]) {
            cout << i << " ";
        }
    }
    cout << "\n";
    cout << (n + 1) / 2 << "\n";
    for (int i = 1; i <= n; i++) {
        if (!in_set[i]) {
            cout << i << " ";
        }
    }
    cout << "\n";
}
