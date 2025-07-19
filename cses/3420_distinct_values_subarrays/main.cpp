#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

typedef long long ll;

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

    unordered_set<int> found;
    ll res = 0;
    for (int j = 0, i = 0; i < n; i++) {
        while (found.find(values[i]) != found.end()) {
            res += found.size();
            found.erase(values[j++]);
        }

        found.insert(values[i]);
    }
    res += (ll)found.size() * (found.size() + 1) / 2;

    cout << res << "\n";
}
