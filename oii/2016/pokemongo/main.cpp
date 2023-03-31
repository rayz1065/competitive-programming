#include <bits/stdc++.h>
#define MAXN 5000005
#define MAXK 25
using namespace std;

int k_max_lives;
int n_max;
bool attack(int);
int memo[200005][MAXK];
int strat[200005][MAXK];
vector<int> strat_changes[MAXK];

int apply_strat (int n, int k) {
    auto pos = upper_bound(strat_changes[k].begin(), strat_changes[k].end(), n);
    pos--;
    return n - *pos;
}

int worst (int n, int k) {
    assert (k > 0 && n >= 0);
    if (k == 1 || n == 0) return n;
    if (memo[n][k]) return memo[n][k];
    if (n > 5) assert(memo[n - 1][k]);
    int s = worst(n - 1, k) + 1;
    strat[n][k] = 0;
    int prev_strat = strat[n - 1][k] + 1;
    for (int i = prev_strat; i < n && i < prev_strat + 1; i++) {
        // try the previous strategy again
        int curr = max(worst(i, k - 1), worst(n - i - 1, k)) + 1;
        // if (i == prev_strat)
        //     cout << n << ", " << k << " using prev strat " << i << " is " << curr << "\n";
        if (curr < s) {
            s = curr;
            strat[n][k] = i;
        }
    }
    // if (n < 100)
    // cout << n << "," << k << ": " << s << "\n";
    return memo[n][k] = s;
}

void compute_strat_4 () {
    vector<int> v = { 0, 1, 1, 2, 4, 8 };
    int x = 0;
    for (int i = 0; i < 6; i++) {
        x += v[i];
        strat_changes[4].push_back(x);
    }
    for (int i = v.size(); x < MAXN; i++) {
        int aa = (v[i - 1] - v[i - 2]) - (v[i - 2] - v[i - 3]);
        aa++;
        int a = v[i - 1] - v[i - 2] + aa;
        v.push_back(v[i - 1] + a);
        x += v[i];
        strat_changes[4].push_back(x);
    }
    // for (int n = 0; n < 5000; n++) {
    //     worst(n, 4);
    //     assert(apply_strat(n, 4) == strat[n][4]);
    // }
}

void compute_strat_3 () {
    vector<int> v = { 0, 1, 1, 2, 4 };
    int x = 0;
    for (auto v_i: v) {
        x += v_i;
        strat_changes[3].push_back(x);
    }
    for (int i = v.size(); x < MAXN; i++) {
        int aa = (v[i - 1] - v[i - 2]) - (v[i - 2] - v[i - 3]);
        int a = v[i - 1] - v[i - 2] + aa;
        v.push_back(v[i - 1] + a);
        x += v[i];
        strat_changes[3].push_back(x);
    }
    // for (int n = 0; n < 5000; n++) {
    //     worst(n, 3);
    //     assert(apply_strat(n, 3) == strat[n][3]);
    // }
}

void compute_strat_2 () {
    vector<int> v = { 0, 1, 1, 2 };
    int x = 0;
    for (auto v_i: v) {
        x += v_i;
        strat_changes[2].push_back(x);
    }
    for (int i = v.size(); x < MAXN; i++) {
        int a = 1;
        v.push_back(v[i - 1] + a);
        x += v[i];
        strat_changes[2].push_back(x);
    }
    // for (int n = 0; n < 50000; n++) {
    //     worst(n, 2);
    //     assert(apply_strat(n, 2) == strat[n][2]);
    // }
}

void init(int N, int K) {
    for (int k = 2; k <= K; k++) {
        // cout << "finding solutions for " << k << "\n";
        // cout.flush();
        for (int n = 1; n < 200000; n++) {
            worst(n, k);
            assert(memo[n][k]);
        }
    }
    if (K >= 2) compute_strat_2();
    if (K >= 3) compute_strat_3();
    if (K >= 4) compute_strat_4();
    k_max_lives = K;
    n_max = N;
    // cout << "Worst case is " << worst(N, K) << "\n";
    // for (int k = 1; k < 10; k++) {
    //     cout << "k = " << k << ", x = \t";
    //     int last_0 = 0;
    //     int last_last_0 = 0;
    //     for (int n = 0; n < 2000; n++) {
    //         int w = worst(n, k);
    //         w = strat[n][k];
    //         if (w == 0) {
    //             cout << n << " ";
    //             last_last_0 = last_0;
    //             last_0 = n;
    //         }
    //     }
    //     cout << "\n";
    //     cout << "k = " << k << ", v = \t";
    //     last_0 = 0, last_last_0 = 0;
    //     for (int n = 0; n < 2000; n++) {
    //         int w = worst(n, k);
    //         w = strat[n][k];
    //         if (w == 0) {
    //             // cout << (n - last_0) - (last_0 - last_last_0) << " ";
    //             cout << last_0 - last_last_0 << " ";
    //             last_last_0 = last_0;
    //             last_0 = n;
    //         }
    //     }
    //     cout << "\n";
    //     cout << "k = " << k << ", a = \t";
    //     last_0 = 0, last_last_0 = 0;
    //     for (int n = 0; n < 2000; n++) {
    //         int w = worst(n, k);
    //         w = strat[n][k];
    //         if (w == 0) {
    //             cout << (n - last_0) - (last_0 - last_last_0) << " ";
    //             last_last_0 = last_0;
    //             last_0 = n;
    //         }
    //     }
    //     cout << "\n";
    // }
}

int solve_k_1 (int l, int n) {
    for (int i = 0; i < n; i++) {
        // cout << "attacking " << l << " + " << i << "\n";
        if (!attack(l + i)) {
            return l + i;
        }
    }
    return l + n;
}

int solve_fast (int l, int n, int k) {
    while (n > 0 && k > 0) {
        if (k == 1) {
            return solve_k_1(l, n);
        }
        int i = apply_strat(n, k);
        // cout << "next i will try " << "apply_strat(" << n << ", " << k << ") = " << apply_strat(n, k) << "\n";
        if (!attack(l + i)) {
            n = i;
            k--;
        } else {
            l += i + 1;
            n -= i + 1;
        }
    }
    return l;
}

int solve_bin (int l, int n, int k) {
    while (n > 0) {
        if (k <= 4) {
            return solve_fast(l, n, k);
        }
        int i = n / 2;
        if (!attack(l + i)) {
            n = i;
            k--;
        } else {
            l += i + 1;
            n -= i + 1;
        }
    }
    return l + n;
}

int solve_accurate (int l, int n, int k) {
    while (n > 0 && k > 0) {
        worst(n, k);
        int i = strat[n][k];
        // cout << "strat[" << n << "][" << k << "] = " << i << " -> attack(" << l + i << ")\n";
        if (!attack(l + i)) {
            n = i;
            k--;
        } else {
            l += i + 1;
            n -= i + 1;
        }
    }
    return l;
}

int new_pokemon() {
    if (n_max <= 200000) {
        return solve_accurate(0, n_max, k_max_lives);
    } else {
        return solve_bin(0, n_max, k_max_lives);
    }
    return -1;
}
