#include <bits/stdc++.h>
#define MAXN 205

using namespace std;

string words[MAXN];
string sorted[MAXN];

int main () {
#ifndef DEBUG
    fstream cin, cout;
    cin.open("input.txt", ios::in);
    cout.open("output.txt", ios::out);
#endif
    int n;
    cin >> n;
    map<string, int> freqs;
    for (int i = 0; i < n; i++) {
        cin >> words[i];
        sorted[i] = words[i];
        sort(sorted[i].begin(), sorted[i].end());
        freqs[sorted[i]] += 1;
    }
    for (int i = 0; i < n; i++) {
        cout << words[i][freqs[sorted[i]] - 1];
    }
    cout << "\n";
}
