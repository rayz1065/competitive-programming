#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

typedef long long ll;

int n, k, values[MAXN];

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> values[i];
    }

    ll res = 0;
    map<int, int> found;
    for (int i = 0, j = 0; i < n; i++) {
        found[values[i]] += 1;
        while (found.size() > k) {
            int erased = values[j++];
            auto curr = found.find(erased);
            if (curr->second == 1) {
                found.erase(curr);
            } else {
                found[erased]--;
            }
        }
        res += i - j + 1;
    }

    cout << res << "\n";
}
