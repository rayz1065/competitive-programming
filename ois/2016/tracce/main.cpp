#include <bits/stdc++.h>
#define MAXN 1000005
#define MOD 1000000007

using namespace std;

typedef long long ll;

int n, k;
int memo[MAXN];

inline int safe_mul(int a, int b) { return ((ll)a * b) % MOD; }
inline int safe_add(int a, int b) { return (a + b) % MOD; }
inline int safe_sub(int a, int b) { return (a - b + MOD) % MOD; }

int main() {
#ifndef DEBUG
    fstream cin, cout;
    cin.open("input.txt", ios::in);
    cout.open("output.txt", ios::out);
#else
    cin.tie(NULL);
    cout.tie(NULL);
#endif
    ios_base::sync_with_stdio(false);

    cin >> n;
    string s;
    cin >> s;
    k = s.length();

    memo[k] = 1;
    int pow10 = 1;

    for (int i = k; i <= n; i++) {
        int res = safe_sub(pow10, memo[i - k]);
        res = safe_add(res, safe_mul(10, memo[i - 1]));
        memo[i] = res;
        pow10 = safe_mul(pow10, 10);
    }

    cout << memo[n] << "\n";
}
