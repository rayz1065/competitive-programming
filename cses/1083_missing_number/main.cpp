#include <bits/stdc++.h>
#define MAXN 500001

using namespace std;

int n;
bool found[MAXN];

int main () {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        found[x] = true;
    }
    for (int i = 1; i <= n; i++) {
        if (!found[i]) {
            cout << i << "\n";
            break ;
        }
    }
}