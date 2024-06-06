#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

typedef long long ll;

int n;
int sticks[MAXN];

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> sticks[i];
    }

    nth_element(sticks, sticks + n / 2, sticks + n);

    ll res = 0;
    for (int i = 0; i < n; i++) {
        res += abs(sticks[i] - sticks[n / 2]);
    }

    cout << res << "\n";
}
