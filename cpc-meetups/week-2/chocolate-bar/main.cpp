#include <bits/stdc++.h>
#define MAXN 55

using namespace std;

int memo[MAXN][MAXN][MAXN];

int solve(int rows, int cols, int k) {
    if (memo[rows][cols][k] != 0) {
        return memo[rows][cols][k] - 1;
    } else if (rows * cols == k or k == 0) {
        return 0;
    } else if (rows * cols < k) {
        return INT_MAX >> 2;
    }

    int res = INT_MAX >> 2;

    // we split over the rows, keeping split_size on one side
    // and (rows - split_size) on the other side
    for (int split_size = 1; split_size < rows; split_size++) {
        // we want to get exactly side_k on the first side and
        // (k - side_k) on the other side
        for (int side_k = 0; side_k <= k; side_k++) {
            int new_res_1 = solve(split_size, cols, side_k) +
                            solve(rows - split_size, cols, k - side_k) +
                            cols * cols;
            int new_res_2 = solve(cols, split_size, side_k) +
                            solve(cols, rows - split_size, k - side_k) +
                            cols * cols;
            res = min(res, min(new_res_1, new_res_2));
        }
    }

    memo[rows][cols][k] = res + 1;

    return res;
}

int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int t;
    cin >> t;

    while (t--) {
        int rows, cols, k;
        cin >> rows >> cols >> k;
        cout << min(solve(rows, cols, k), solve(cols, rows, k)) << "\n";
    }
}
