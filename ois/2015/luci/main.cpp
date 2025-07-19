#include <bits/stdc++.h>

using namespace std;

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

    int n;
    cin >> n;

    int nsqrt = sqrt(n);
    while (nsqrt * nsqrt > n) nsqrt--;
    while ((nsqrt + 1) * (nsqrt + 1) <= n) nsqrt++;

    cout << n - nsqrt << "\n";
}
