#include <bits/stdc++.h>
#define GRID_SIZE 7
#define MOV 4

using namespace std;

string path_description;

int mov_r[] = {-1, 0, 1, 0}, mov_c[] = {0, -1, 0, 1};
char mov_name[] = {'U', 'L', 'D', 'R'};

inline bool in_range(int r, int c) {
    return 0 <= r && r < GRID_SIZE && 0 <= c && c < GRID_SIZE;
}

inline bool is_destination(int r, int c) {
    return r == GRID_SIZE - 1 && c == 0;
}

inline bool validate_path(char wanted, char actual) {
    return wanted == '?' || wanted == actual;
}

int find_paths(int r, int c, string &curr_path,
               int remaining_edges[][GRID_SIZE], bool visited[][GRID_SIZE]) {
    if (curr_path.size() > 0 &&
        !validate_path(path_description[curr_path.size() - 1],
                       curr_path.back())) {
        return 0;
    }

    if (is_destination(r, c)) {
        return curr_path.size() == GRID_SIZE * GRID_SIZE - 1;
    }

    visited[r][c] = true;

    int one_path_only = 0;
    vector<int> valid_m;

    for (int m = 0; m < 4; m++) {
        int new_r = r + mov_r[m], new_c = c + mov_c[m];
        if (!in_range(new_r, new_c) || visited[new_r][new_c]) {
            continue;
        }

        remaining_edges[new_r][new_c] -= 1;

        if (is_destination(new_r, new_c) &&
            curr_path.length() != GRID_SIZE * GRID_SIZE - 2) {
            continue;
        }

        if (remaining_edges[new_r][new_c] == 1) {
            one_path_only += 1;
            valid_m.clear();
            valid_m.push_back(m);
        } else if (one_path_only == 0) {
            valid_m.push_back(m);
        }
    }

    int res = 0;

    if (one_path_only == 1) {
        int m = valid_m.back();
        int new_r = r + mov_r[m], new_c = c + mov_c[m];
        curr_path.push_back(mov_name[m]);
        res += find_paths(new_r, new_c, curr_path, remaining_edges, visited);
        curr_path.pop_back();
    } else if (one_path_only == 0) {
        for (auto m : valid_m) {
            int new_r = r + mov_r[m], new_c = c + mov_c[m];
            curr_path.push_back(mov_name[m]);
            res +=
                find_paths(new_r, new_c, curr_path, remaining_edges, visited);
            curr_path.pop_back();
        }
    }

    for (int m = 0; m < 4; m++) {
        int new_r = r + mov_r[m], new_c = c + mov_c[m];
        if (!in_range(new_r, new_c) || visited[new_r][new_c]) {
            continue;
        }

        remaining_edges[new_r][new_c] += 1;
    }

    visited[r][c] = false;

    return res;
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int remaining_edges[GRID_SIZE][GRID_SIZE] = {};
    bool visited[GRID_SIZE][GRID_SIZE] = {};
    for (int r = 0; r < GRID_SIZE; r++) {
        for (int c = 0; c < GRID_SIZE; c++) {
            for (int m = 0; m < MOV; m++) {
                int new_r = r + mov_r[m], new_c = c + mov_c[m];
                remaining_edges[r][c] += in_range(new_r, new_c);
            }
        }
    }

    cin >> path_description;

    string curr_path = "";
    cout << find_paths(0, 0, curr_path, remaining_edges, visited) << "\n";
}
