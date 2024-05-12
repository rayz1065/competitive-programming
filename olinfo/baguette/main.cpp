#include <bits/stdc++.h>
#define ALF 26
#define MAXN 10000005

using namespace std;

int n, k;
string baguette;
int memo[MAXN];

int solve_for_letter(int j) {
    // memo[i] = best solution for [0:i) for flavor [j]
    for (int i = 0; i < n; i++) {
        int old_i = max(i + 1 - k, 0);
        int sol = memo[old_i] + 1;  // cut the baguette from [old_i, i)
        if (baguette[i] == 'a' + j) {
            // we can keep the current character
            sol = memo[i];
        }

        memo[i + 1] = sol;
    }

    return memo[n];
}

int affetta(int n, int k, string baguette) {
    ::n = n;
    ::k = k;
    ::baguette = baguette;
    int res = n + 1;
    for (int j = 0; j < ALF; j++) {
        res = min(res, solve_for_letter(j));
    }

    return res;
}
