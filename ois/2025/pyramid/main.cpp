#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;

    int res = 0;
    for (int i = 1; n - i * i >= 0; i++) {
        n -= i * i;
        res = i;
    }

    cout << res << "\n";
}
