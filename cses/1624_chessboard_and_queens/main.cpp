#include <bits/stdc++.h>

using namespace std;

const int n = 8;
char grid[n + 5][n + 5];
int solution;

int col_used[n + 5];
int diag_used[2 * n + 5];
int rev_diag_used[2 * n + 5];

void solve(int r) {
    if (r == n) {
        solution += 1;
        return;
    }

    for (int c = 0; c < n; c++) {
        if (!col_used[c] && !diag_used[r + c] && !rev_diag_used[n - r + c] &&
            grid[r][c] == '.') {
            col_used[c] = diag_used[r + c] = rev_diag_used[n - r + c] = true;
            solve(r + 1);
            col_used[c] = diag_used[r + c] = rev_diag_used[n - r + c] = false;
        }
    }
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    solve(0);

    cout << solution << "\n";
}
