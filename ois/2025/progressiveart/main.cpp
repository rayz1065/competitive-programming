#include <bits/stdc++.h>

using namespace std;

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n, m, l, k;
    cin >> n >> m >> l >> k;

    if ((l % 3 != 0 && k > 0) || (n - l + 1) * (m - l + 1) < k) {
        cout << "NO\n";
        return 0;
    }

    cout << "YES\n";

    int last_color_index = k == 0 ? 1 : -1;
    char colors[] = {'R', 'G', 'B'};

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (last_color_index != -1) {
                cout << colors[(last_color_index + 2) % 3];
            } else {
                cout << colors[i % 3];
                k -= i >= l - 1 && j >= l - 1;
                if (k == 0) {
                    last_color_index = i;
                }
            }
        }
        cout << "\n";
    }
}
