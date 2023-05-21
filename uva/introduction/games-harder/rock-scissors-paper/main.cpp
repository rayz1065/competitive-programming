#include <bits/stdc++.h>

using namespace std;

int rows, columns;
int grid[105][105], grid_new[105][105];
int MOVR[] = {-1, +1, 0, 0}, MOVC[] = {0, 0, -1, +1};
const char* POPULATIONS = "RPS";

bool in_range(int r, int c) {
    return 0 <= r && r < rows && 0 <= c && c < columns;
}

bool has_adj_enemy(int r, int c) {
    int enemy = (grid[r][c] + 1) % 3;
    for (int mov = 0; mov < 4; mov++) {
        int r_new = r + MOVR[mov], c_new = c + MOVC[mov];
        if (in_range(r_new, c_new) && grid[r_new][c_new] == enemy) {
            return true;
        }
    }
    return false;
}

void simulate() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (has_adj_enemy(i, j)) {
                grid_new[i][j] = (grid[i][j] + 1) % 3;
            } else {
                grid_new[i][j] = grid[i][j];
            }
        }
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            grid[i][j] = grid_new[i][j];
        }
    }
}

void print_grid() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cout << POPULATIONS[grid[i][j]];
        }
        cout << "\n";
    }
}

int population_to_int(char c) {
    for (int i = 0; i < 3; i++) {
        if (c == POPULATIONS[i]) {
            return i;
        }
    }
    return -1;
}

void solve() {
    int n_generations;
    cin >> rows >> columns >> n_generations;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            char c;
            cin >> c;
            grid[i][j] = population_to_int(c);
        }
    }

    for (int i = 0; i < n_generations; i++) {
        simulate();
    }
    print_grid();
}

int main() {
    int t;
    cin >> t;

    for (int tc = 0; tc < t; tc++) {
        if (tc > 0) {
            cout << "\n";
        }
        solve();
    }
}
