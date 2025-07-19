#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

typedef long long ll;

int n;
int books[MAXN];

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    ll res = 0;
    for (int i = 0; i < n; i++) {
        cin >> books[i];
        res += books[i];
    }

    res = max(res, (*max_element(books, books + n)) * 2ll);
    cout << res << "\n";
}
