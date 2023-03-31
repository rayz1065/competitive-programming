#include <bits/stdc++.h>
#define MAXN 1000005

using namespace std;

int n, m;
long long figo[MAXN];

int main () {
#ifndef DEBUG
    fstream cin, cout;
    cin.open("input.txt", ios::in);
    cout.open("output.txt", ios::out);
#endif
    cin >> n >> m;
    figo[0] = -1;
    figo[1] = 0;
    int sum = m + figo[0];
    for (int i = 2; i <= n; i++) {
        figo[i] = (figo[i - 1] * (i - 1) - sum + m) % m;
        sum = (sum + figo[i - 1] + m) % m;
    }
    cout << figo[n] << "\n";
}
