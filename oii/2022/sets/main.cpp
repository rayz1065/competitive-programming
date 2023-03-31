#include <bits/stdc++.h>
#define MAXN 10005

using namespace std;

int n;
int zero_pos;
bool memo[MAXN][MAXN];
bool solved[MAXN][MAXN];
int numbers[MAXN];
int pos[MAXN];
int sol[MAXN];
int cumul_xor[MAXN];
vector<int> sols_at[MAXN];

bool calc_xor (int l, int r) {
    return (cumul_xor[l] ^ cumul_xor[r + 1]);
}

bool is_deletable(int l, int r) {
    if (l > r) {
        // already empty
        return true;
    }
    if (solved[l][r]) {
        return memo[l][r];
    }
    solved[l][r] = true;
    if ((r - l + 1) % 3 != 0 || (l <= zero_pos && zero_pos <= r) || calc_xor(l, r) != 0) {
        // no solution for sure
        return false;
    }

    int seeked_number = numbers[l] ^ numbers[r];
    if (seeked_number < n) {
        int j = pos[seeked_number];
        if (l < j && j < r && is_deletable(l + 1, j - 1) && is_deletable(j + 1, r - 1)) {
            // we removed everything from l to r
            memo[l][r] = true;
        }
    }

    if (!memo[l][r]) {
        is_deletable(l, r - 3);
        for (auto i: sols_at[l]) {
            if (is_deletable(l, i) && is_deletable(i + 1, r)) {
                return memo[l][r] = true;
            }
        }
    }
    if (memo[l][r]) {
        sols_at[l].push_back(r);
    }
    return memo[l][r];
}

int conta(int N, vector<int> V) {
    // write here your solution...
    ::n = N;
    for (int i = 0; i < n; i++) {
        numbers[i] = V[i];
        pos[numbers[i]] = i;
        cumul_xor[i + 1] = cumul_xor[i] ^ numbers[i];
        if (numbers[i] == 0) {
            zero_pos = i;
        }
    }

    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < i; j++) {
    //         cout << "  ";
    //     }
    //     for (int j = i; j < n; j++) {
    //         cout << is_deletable(i, j) << " ";
    //     }
    //     cout << "\n";
    // }
    // cout << "\n";

    // sol[n] = 0;
    for (int i = n - 1; i >= 0; i--) {
        // find the best solution for [i, n)
        sol[i] = sol[i + 1] + 1;
        for (int j = i + 2; j < n; j+= 3) {
            // try removing everything in [i, j]
            if (is_deletable(i, j)) {
                sol[i] = min(sol[i], sol[j + 1]);
            }
        }
    }
    // for (int i = 0; i < n; i++) {
    //     cout << sol[i] << " ";
    // }
    // cout << "\n";
    return n - sol[0];
}
