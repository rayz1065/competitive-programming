#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

int values[MAXN];

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> values[i];
    }

    sort(values, values + n);

    int res = 1;
    for (int i = 1; i < n; i++) {
        if (values[i] != values[i - 1]) {
            res += 1;
        }
    }

    cout << res << "\n";
}
