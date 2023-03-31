#include <bits/stdc++.h>
#define MAXN 10005

using namespace std;

int n;
short memo[MAXN][MAXN];
int numbers[MAXN];
int pos[MAXN];

int solve(int l, int r) {
    if (l > r) {
        // already empty
        return 0;
    }
    if (memo[l][r] != -1) {
        return memo[l][r];
    }
    int sol = r - l + 1;
    for (int i = l; i < r; i++) {
        // split the array
        sol = min(sol, solve(l, i) + solve(i + 1, r));
    }
    int seeked_number = numbers[l] ^ numbers[r];
    if (seeked_number < n) {
        int j = pos[seeked_number];
        if (l < j && j < r && solve(l + 1, j - 1) == 0 && solve(j + 1, r - 1) == 0) {
            // we removed everything from l to r
            sol = 0;
        }
    }
    // if (r - l + 1 >= 3)
    // printf("memo[%d][%d] = %d\n", l, r, sol);
    return memo[l][r] = sol;
}

int conta(int N, vector<int> V) {
    // write here your solution...
    ::n = N;
    for (int i = 0; i < n; i++) {
        fill(memo[i], memo[i] + n, -1);
        numbers[i] = V[i];
        pos[numbers[i]] = i;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            cout << "  ";
        }
        for (int j = i; j < n; j++) {
            if ((j - i + 1) % 3 == 0) {
                cout << (solve(i, j) == 0) << " ";
            } else {
                cout << "  ";
            }
        }
        cout << "\n";
    }
    cout << "\n";
    return n - solve(0, n - 1);
}
