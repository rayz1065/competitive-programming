#include <bits/stdc++.h>
#define MEMO_SIZE 20000

using namespace std;

int n = 3;
int grid[3][3];

enum GameOutcome {
    UNKNOWN = -1,
    DEFEAT,
    EVEN,
    VICTORY
} memo[MEMO_SIZE];

int hash_grid () {
    int s = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            s = s * 3 + grid[i][j];
        }
    }
    return s;
}

int curr_winner () {
    // returns the winner or 0
    for (int i = 0; i < n; i++) { // rows
        bool all_eq = grid[i][0];
        for (int j = 1; j < n && all_eq; j++) {
            all_eq = grid[i][j] == grid[i][j - 1];
        }
        if (all_eq) return grid[i][0];
    }
    for (int j = 0; j < n; j++) { // cols
        bool all_eq = grid[0][j];
        for (int i = 1; i < n && all_eq; i++) {
            all_eq = grid[i][j] == grid[i - 1][j];
        }
        if (all_eq) return grid[0][j];
    }
    // diag '/'
    bool all_eq = grid[0][0];
    for (int i = 1, j = 1; i < n && all_eq; i++, j++) {
        all_eq = grid[i][j] == grid[i - 1][j - 1];
    }
    if (all_eq) return grid[0][0];
    // diag '\'
    all_eq = grid[n - 1][0];
    for (int i = n - 2, j = 1; i >= 0 && all_eq; i--, j++) {
        all_eq = grid[i][j] == grid[i + 1][j - 1];
    }
    if (all_eq) return grid[n - 1][0];
    return 0;
}

// void print_grid () {
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < n; j++) {
//             cout << grid[i][j] << " \n"[j + 1 == n];
//         }
//     }
// }

GameOutcome get_outcome (int player) {
    int state = hash_grid();
    if (memo[state] != UNKNOWN) return memo[state];
    int winner = curr_winner();
    if (winner) {
        return memo[state] = (winner == player) ? VICTORY : DEFEAT;
    }

    bool over = true, can_tie = false;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!grid[i][j]) {
                over = false;
                grid[i][j] = player;
                auto outcome = get_outcome(3 - player);
                if (outcome == DEFEAT) {
                    grid[i][j] = 0;
                    return memo[state] = VICTORY;
                } else if (outcome == EVEN) {
                    can_tie = true;
                }
                grid[i][j] = 0;
            }
        }
    }
    return memo[state] = over || can_tie ? EVEN : DEFEAT;
}

int first_player () {
    int more_x = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j]) {
                more_x += (grid[i][j] == 1 ? 1 : -1);
            }
        }
    }
    return more_x > 0 ? 2 : 1;
}

int main () {
#ifndef DEBUG
    fstream cin, cout;
    cin.open("input.txt", ios::in);
    cout.open("output.txt", ios::out);
#endif
    fill(memo, memo + MEMO_SIZE, UNKNOWN);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            char c;
            cin >> c;
            if (c != '.') {
                grid[i][j] = c == 'X' ? 1 : 2;
            }
        }
    }
    auto outcome = get_outcome(first_player());
    // cout << "first player is " << (first_player() == 1 ? 'X' : 'O') << ", outcome is " << outcome << "\n";
    if (first_player() == 1 && outcome == VICTORY) {
        cout << 1 << "\n";
    } else if (first_player() == 2 && outcome == DEFEAT) {
        cout << 1 << "\n";
    } else {
        cout << 0 << "\n";
    }
}
