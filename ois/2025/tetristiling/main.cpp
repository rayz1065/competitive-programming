#include <bits/stdc++.h>
#define MAXN 1005
#define TETRINO_COUNT 8

using namespace std;

int n;

int grid[MAXN][MAXN];
int remainders[4][MAXN][MAXN];
int tetrino_base;

int tetrinos_r[TETRINO_COUNT][4] = {{0, 0, 1, 1}, {0, 1, 1, 2}, {0, 1, 1, 2},
                                    {0, 0, 1, 1}, {0, 0, 0, 1}, {0, 1, 1, 2},
                                    {0, 1, 1, 1}, {0, 1, 1, 2}};
int tetrinos_c[TETRINO_COUNT][4] = {{0, 1, 1, 2}, {1, 0, 1, 0}, {0, 0, 1, 1},
                                    {1, 2, 0, 1}, {0, 1, 2, 1}, {1, 0, 1, 1},
                                    {1, 0, 1, 2}, {0, 0, 1, 0}};

bool in_range(int r, int c) { return 0 <= r && r < n && 0 <= c && c < n; }

bool can_place_tetrino(int r, int c, int tetrino) {
    for (int m = 0; m < 4; m++) {
        int dr = tetrinos_r[tetrino][m], dc = tetrinos_c[tetrino][m];
        int new_r = r + dr, new_c = c + dc;
        if (!in_range(new_r, new_c) || grid[new_r][new_c]) {
            return false;
        }
    }
    return true;
}

void place_tetrino(int r, int c, int tetrino, int amount) {
    for (int m = 0; m < 4; m++) {
        int dr = tetrinos_r[tetrino][m], dc = tetrinos_c[tetrino][m];
        int new_r = r + dr, new_c = c + dc;
        grid[new_r][new_c] += amount;
    }
}

void print_grid() {
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (grid[r][c] < 10) {
                cerr << " ";
            }
            cout << grid[r][c] << " \n"[c + 1 == n];
        }
    }
}

bool brute_force(int depth) {
    int target = n * n / 4 - (n == 3 || (n == 6 && grid[0][0] >= 0));
    if (depth == target) {
        return true;
    }

    for (int tetrino = 0; tetrino < TETRINO_COUNT; tetrino++) {
        int skipped = 0;
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n && skipped < 1; c++) {
                if (can_place_tetrino(r, c, tetrino)) {
                    place_tetrino(r, c, tetrino, depth + tetrino_base + 1);
                    if (brute_force(depth + 1)) {
                        return true;
                    }
                    place_tetrino(r, c, tetrino, -(depth + tetrino_base + 1));
                }
                skipped += grid[r][c] == 0;
            }
        }
    }

    return false;
}

void clear_grid() {
    for (int r = 0; r < n; r++) {
        fill(grid[r], grid[r] + n, 0);
    }
}

void find_remainders() {
    for (int i = 0; i < 4; i++) {
        n = 4 + i;
        for (int r = 0; r < i; r++) {
            for (int c = 0; c < i; c++) {
                grid[r][c] = -1;
            }
        }

        brute_force((i * i) / 4);

        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                remainders[i][r][c] = grid[r][c] - (i * i) / 4;
            }
        }

        clear_grid();
    }
}

void copy_remainder(int remainder_id, int r, int c) {
    for (int dr = 0; dr < 4 + remainder_id; dr++) {
        for (int dc = 0; dc < 4 + remainder_id; dc++) {
            if (remainders[remainder_id][dr][dc] < 0) {
                continue;
            }
            assert(grid[r + dr][c + dc] == 0);
            grid[r + dr][c + dc] =
                remainders[remainder_id][dr][dc] + tetrino_base;
        }
    }
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    find_remainders();

    cin >> n;
    int original_n = n;
    int remainder_id = n % 4;

    while (n > 10) {
        // fill the bottom right edge
        for (int i = 0; i < n - remainder_id - 4; i += 4) {
            copy_remainder(0, n - 4, i);
            tetrino_base += 4;
            copy_remainder(0, i, n - 4);
            tetrino_base += 4;
        }
        copy_remainder(remainder_id, n - remainder_id - 4,
                       n - remainder_id - 4);
        tetrino_base += 4 + remainder_id * 2;
        n -= 4;
    }

    brute_force(0);

    n = original_n;

    cout << n * n / 4 - (n == 2 || n == 3 || n == 6) << "\n";
    int empty = 0;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            empty += grid[r][c] == 0;
        }
    }

    print_grid();
}
