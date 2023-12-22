#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define MAXN 1005
#define MOV 8

using namespace std;

typedef enum {
    TOP_LEFT,
    TOP_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_RIGHT,
} SubCell;

typedef enum {
    UP,
    UP_RIGHT,
    RIGHT,
    DOWN_RIGHT,
    DOWN,
    DOWN_LEFT,
    LEFT,
    UP_LEFT
} Direction;

int standard_mov_r[] = {-1, -1, 0, +1, +1, +1, 0, -1};
int standard_mov_c[] = {0, +1, +1, +1, 0, -1, -1, -1};

// movements described as [SubCell][Direction] -> delta
int mov_r[4][MOV];
int mov_c[4][MOV];
// movements described as [SubCell][Direction] -> new sub cell
SubCell mov_sub[4][MOV];

int r_rows, c_cols;
int distances[MAXN][MAXN][4];
short poison[MAXN][MAXN];
// movements as [SubCell][Direction][Poison] -> valid
bool valid_movement[4][8][16];

void compile_sub_movements() {
    SubCell test_grid_sub[4][4];
    int test_grid_r[4][4];
    int test_grid_c[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            test_grid_sub[i][j] = (SubCell)((i % 2) * 2 + (j % 2));
            test_grid_r[i][j] = i / 2;
            test_grid_c[i][j] = j / 2;
        }
    }

    for (int i = 1; i <= 2; i++) {
        for (int j = 1; j <= 2; j++) {
            for (int mov = 0; mov < MOV; mov++) {
                int new_i = i + standard_mov_r[mov];
                int new_j = j + standard_mov_c[mov];

                int r = test_grid_r[i][j], new_r = test_grid_r[new_i][new_j];
                int c = test_grid_c[i][j], new_c = test_grid_c[new_i][new_j];

                SubCell starting_sub = test_grid_sub[i][j],
                        ending_sub = test_grid_sub[new_i][new_j];

                mov_sub[starting_sub][mov] = ending_sub;
                mov_r[starting_sub][mov] = (new_r - r);
                mov_c[starting_sub][mov] = (new_c - c);
            }
        }
    }
}

bool in_range(int r, int c) {
    return 0 <= r && r < r_rows && 0 <= c && c < c_cols;
}

bool is_valid_movement(SubCell sub, int mov, int poison_) {
    int r = 0, c = 0;
    int new_r = r + mov_r[sub][mov];
    int new_c = c + mov_c[sub][mov];
    SubCell new_sub = mov_sub[sub][mov];

    if (mov == UP_RIGHT || mov == UP_LEFT || mov == DOWN_RIGHT ||
        mov == DOWN_LEFT) {
        // diagonal movements must change both the row and column
        return (r != new_r && c != new_c);
    }

    if (r != new_r || c != new_c) {
        return true;
    }

    // check for poison
    if (sub > new_sub) {
        swap(sub, new_sub);
    }

    if (sub == TOP_LEFT && new_sub == TOP_RIGHT) {
        return (poison_ & 1) == 0;
    }
    if (sub == TOP_RIGHT && new_sub == BOTTOM_RIGHT) {
        return (poison_ & 2) == 0;
    }
    if (sub == BOTTOM_LEFT && new_sub == BOTTOM_RIGHT) {
        return (poison_ & 4) == 0;
    }
    if (sub == TOP_LEFT && new_sub == BOTTOM_LEFT) {
        return (poison_ & 8) == 0;
    }

    // impossible, moving through the center is not allowed
    assert(false);
}

void bfs() {
    int r = 0, c = 0;
    SubCell sub = TOP_LEFT;

    // alternate between the two queues
    queue<tuple<int, int, SubCell>> ff[2];
    int current_queue = 0;

    for (int r = 0; r < r_rows; r++) {
        for (int c = 0; c < c_cols; c++) {
            for (int sub = 0; sub < 4; sub++) {
                distances[r][c][sub] = INT_MAX >> 1;
            }
        }
    }
    distances[r][c][sub] = 0;
    ff[current_queue].push({r, c, sub});

    while ((!ff[0].empty() || !ff[1].empty())) {
        if (ff[current_queue].empty()) {
            current_queue = !current_queue;
        }

        tie(r, c, sub) = ff[current_queue].front();
        ff[current_queue].pop();
        int distance = distances[r][c][sub];
        // cerr << r << " " << c << " " << sub << " " << distance << "\n";

        for (int mov = 0; mov < MOV; mov++) {
            int new_r = r + mov_r[sub][mov], new_c = c + mov_c[sub][mov];
            SubCell new_sub = mov_sub[sub][mov];
            if (!in_range(new_r, new_c)) {
                continue;
            }

            if (!valid_movement[sub][mov][poison[r][c]]) {
                continue;
            }

            bool is_farther = (r != new_r || c != new_c);
            int new_distance = is_farther ? distance + 1 : distance;

            if (distances[new_r][new_c][new_sub] != INT_MAX >> 1) {
                continue;
            }

            distances[new_r][new_c][new_sub] = new_distance;
            ff[current_queue xor is_farther].push({new_r, new_c, new_sub});

            if (new_r == r_rows - 1 && new_c == c_cols - 1 && new_sub == BOTTOM_RIGHT) {
                return ;
            }
        }
    }
}

void compile_valid_movements() {
    for (int sub = 0; sub < 4; sub++) {
        for (int mov = 0; mov < MOV; mov++) {
            for (int poison_ = 0; poison_ < 16; poison_++) {
                valid_movement[sub][mov][poison_] =
                    is_valid_movement((SubCell)sub, mov, poison_);
            }
        }
    }
}

int main() {
#ifndef DEBUG
    fstream cin, cout;
    cin.open("input.txt", ios::in);
    cout.open("output.txt", ios::out);
#endif
    compile_sub_movements();
    compile_valid_movements();

    int poison_acc = 0;
    cin >> r_rows >> c_cols;
    for (int r = 0; r < r_rows; r++) {
        for (int c = 0; c < c_cols; c++) {
            cin >> poison[r][c];
            poison_acc |= poison[r][c];
        }
    }

    if (poison_acc == 0) {
        cout << max(r_rows, c_cols) << "\n";
        return 0;
    }

    bfs();

    int distance = distances[r_rows - 1][c_cols - 1][BOTTOM_RIGHT];
    if (distance == INT_MAX >> 1) {
        cout << -1 << "\n";
    } else {
        cout << distance + 1 << "\n";
    }
}
