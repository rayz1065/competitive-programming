#include <bits/stdc++.h>
#define MAXN 100005
#define MOD 666013

using namespace std;

int k, x;
int total_sum;
int true_sum;
int pw10[MAXN];

void find_pali (int i, int curr, int &found) {
    if (i == x / 2) {
        total_sum = (total_sum + curr) % MOD;
        found++;
        return ;
    }
    for (int j = (i == 0); j < 10; j++) {
        // add (10 ** i) * j + (10 ** (x - i)) * j
        find_pali(i + 1, curr + ((pw10[i] + pw10[x - i - 1]) * j) % MOD, found);
        if (found == k) return ;
    }
}


int main () {
    cin >> k >> x;
    pw10[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        pw10[i] = (pw10[i - 1] * 10) % MOD;
    }
    int found = 0;
    find_pali(0, 0, found);
    cout << total_sum << "\n";
}
