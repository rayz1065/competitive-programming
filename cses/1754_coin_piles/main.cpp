#include <bits/stdc++.h>

using namespace std;

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int t;
    cin >> t;

    while (t--) {
        int a, b;
        cin >> a >> b;

        if (a < b) {
            swap(a, b);
        }

        if (a > b * 2 || (a + b) % 3 != 0) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
        }
    }
}
