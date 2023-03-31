#include <bits/stdc++.h>
#define MAXN 30005
#define ALF 26

using namespace std;

int n;
char passphrases[MAXN];
int chr_positions[ALF][MAXN];
int chr_count[ALF];
int chr_curr[ALF];

int find_next (int i, int k) {
    for (int j = ALF - 1; j >= 0; j--) {
        while (chr_positions[j][chr_curr[j]] < i) chr_curr[j]++;
        int pos = chr_positions[j][chr_curr[j]];
        if (pos <= i + k) {
            return pos;
        }
    }
    assert(false);
}

int main () {
    int k;
    cin >> n >> k >> passphrases;
    for (int i = 0; i < ALF; i++) {
        chr_positions[i][0] = INT_MAX >> 1;
    }
    for (int i = 0; i < n; i++) {
        char c = passphrases[i];
        chr_positions[c - 'a'][chr_count[c - 'a']++] = i;
        chr_positions[c - 'a'][chr_count[c - 'a'] + 1] = INT_MAX >> 1;
    }

    for (int i = 0; i + k < n; i++) {
        int nxt = find_next(i, k);
        k -= nxt - i; // subtract skipped ones
        cout << passphrases[nxt];
        i = nxt;
    }
    cout << "\n";
}
