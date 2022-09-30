#include <bits/stdc++.h>
#pragma GCC optimize ("O3")

using namespace std;

int n_rows, m_cols;
int grid[20][20];
int placed_count;
int max_placed;
int movr[20] = { 0, -1, -1, -1 };
int movc[20] = { -1, -1, 0, 1 };

inline bool in_range (int i, int j) {
    return i >= 0 && j >= 0 && i < n_rows && j < m_cols;
}

bool is_aligned (int i, int j, int m) {
    if (!in_range(i + movr[m] * 2, j + movc[m] * 2)) {
        return false;
    }
    return grid[i + movr[m]][j + movc[m]] && grid[i + movr[m] * 2][j + movc[m] * 2];
}

bool can_place (int i, int j) {
    // if there aren't 2 before, 2 above, or 2 diagonally '\' or '/' can place
    for (int m = 0; m < 4; m++) {
        if (is_aligned(i, j, m)) {
            return false;
        }
    }
    return true;
}

void print_grid () {
    for (int i = 0; i < n_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            cout << grid[i][j] << " \n"[j + 1 == m_cols];
        }
    }
    cout << "\n";
}

int remaining_cells (int i, int j) {
    int in_curr_row = (m_cols - j) % 3 + (m_cols - j) / 3 * 2;
    int in_next_rows = (n_rows - i) * (m_cols % 3 + (m_cols / 3) * 2);
    return in_curr_row + in_next_rows;
}

void solve (int i, int j) {
    if (remaining_cells(i, j) + placed_count < max_placed) {
        return ;
    }
    if (j == m_cols) {
        i++, j = 0;
        if (i == n_rows) {
            max_placed = max(max_placed, placed_count);
            return ;
        }
    }
    if (can_place(i, j)) {
        placed_count++;
        grid[i][j] = 1;
        solve(i, j + 1);
        placed_count--;
        grid[i][j] = 0;
    }
    solve(i, j + 1);
}

void print_all_solutions () {
    for (n_rows = 1; n_rows <= 10; n_rows++) {
        cout << "{ ";
        for (m_cols = 0; m_cols <= 10; m_cols++) {
            max_placed = 0;
            if (m_cols > 0 && n_rows * m_cols <= 36) {
                solve(0, 0);
            }
            cout << max_placed << ", ";
        }
        cout << "}\n";
    }
}

int main () {
    cin >> n_rows >> m_cols;
    solve(0, 0);
    cout << max_placed << "\n";
}
