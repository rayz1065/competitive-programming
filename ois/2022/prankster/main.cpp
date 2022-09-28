#include <bits/stdc++.h>
#pragma GCC OPTIMIZE("O3")

using namespace std;

int n_safes;
vector<int> safes;

int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n_safes;
    safes.resize(n_safes);

    int s = 0;
    int swaps = 0;

    for (int i = 0; i < n_safes; i++) {
        cin >> safes[i];
    }
    safes.push_back(0);
    for (int i = 0; i <= n_safes; i++) {
        if (safes[i] == 0) {
            if (swaps > 0) {
                s += swaps / 2 + 1;
                swaps = 0;
            }
        }
        else if (i == 0 || safes[i] != safes[i - 1]) {
            swaps++;
        }
    }

    // Print the result
    cout << s << endl;
    return 0;
}
