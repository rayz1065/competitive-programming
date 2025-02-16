#include <bits/stdc++.h>
#define MAXN 200005
#define LOGMAX 25

using namespace std;

int n;
int values[MAXN];
vector<int> connections[LOGMAX];
int distances[LOGMAX][MAXN];

void bfs(bool found_bits[LOGMAX], int curr_d, int curr_distances[MAXN],
         queue<int> &ff) {
    vector<int> new_found_bits;

    while (!ff.empty()) {
        int node = ff.front();
        ff.pop();

        for (int j = 0; j < LOGMAX; j++) {
            if (!found_bits[j] && (values[node] & (1 << j))) {
                found_bits[j] = true;
                new_found_bits.push_back(j);
            }
        }
    }

    if (new_found_bits.size() == 0) {
        return;
    }

    for (auto j : new_found_bits) {
        for (auto i : connections[j]) {
            if (curr_distances[i] > curr_d + 1) {
                ff.push(i);
                curr_distances[i] = curr_d + 1;
            }
        }
    }

    bfs(found_bits, curr_d + 1, curr_distances, ff);
}

void compute_distances() {
    for (int j = 0; j < LOGMAX; j++) {
        fill(distances[j], distances[j] + n, INT_MAX >> 1);
        queue<int> ff;
        for (auto i : connections[j]) {
            ff.push(i);
            distances[j][i] = 0;
        }

        bool found_bits[LOGMAX] = {};
        found_bits[j] = true;
        bfs(found_bits, 0, distances[j], ff);
    }
}

int solve(int x, int y) {
    int res = INT_MAX >> 1;

    for (int j = 0; j < LOGMAX; j++) {
        if (values[x] & (1 << j)) {
            res = min(res, distances[j][y] + 1);
        }
    }

    return res == (INT_MAX >> 1) ? -1 : res;
}

int fastin() {
    int v = 0;
    char c = getchar_unlocked();
    while (c >= '0') {
        v = v * 10 + c - '0';
        c = getchar_unlocked();
    }
    return v;
}

int main() {
    int q_queries;
    n = fastin(), q_queries = fastin();

    for (int i = 0; i < n; i++) {
        values[i] = fastin();

        for (int j = 0; j < LOGMAX; j++) {
            if (values[i] & (1 << j)) {
                connections[j].push_back(i);
            }
        }
    }

    compute_distances();

    while (q_queries--) {
        int x = fastin(), y = fastin();
        x--, y--;

        cout << solve(x, y) << "\n";
    }
}
