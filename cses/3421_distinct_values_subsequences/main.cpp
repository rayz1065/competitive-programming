#include <bits/stdc++.h>
#define MAXN 200005
#define MODV 1000000007
#define MOD(x) ((x) % MODV)

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
    sort(values, values + n);

    int res = 1;
    for (int i = 0; i < n;) {
        int freq = 0;
        for (int v = values[i]; values[i] == v; i++, freq++);
        res = MOD((ll)res * (freq + 1));
    }
    res = MOD(res + MODV - 1);

    cout << res << "\n";
}
