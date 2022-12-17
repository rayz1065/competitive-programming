#include <bits/stdc++.h>
#define MAXN 61
#define USEFULV 15
#define TTTV 32770
#define ENDTIME 30
using namespace std;

int n;
int valves[MAXN];
vector<int> graph[MAXN];
int memo[MAXN][TTTV][ENDTIME + 5];
vector<short> memo_2[MAXN][MAXN][ENDTIME + 1];

int solve_1 (int pos, bitset<USEFULV> found, int curr_t) {
    int s = 0;
    if (curr_t == ENDTIME) {
        return s;
    }
    if (memo[pos][found.to_ulong()][curr_t] != 0) {
        return memo[pos][found.to_ulong()][curr_t] - 1;
    }
    if (valves[pos] > 0 && !found[pos]) {
        bitset<USEFULV> new_found = found;
        new_found[pos] = true;
        s = max(s, (valves[pos] * (ENDTIME - curr_t)) + solve_1(pos, new_found, curr_t + 1));
    }
    for (auto adj: graph[pos]) {
        s = max(s, solve_1(adj, found, curr_t + 1));
    }
    memo[pos][found.to_ulong()][curr_t] = s + 1;
    return s;
}

int solve_2 (int pos_1, int pos_2, bitset<USEFULV> found, int curr_t) {
    int s = 0;
    if (curr_t == ENDTIME) {
        return s;
    }
    if (memo_2[pos_1][pos_2][curr_t][found.to_ulong()] != 0) {
        return memo_2[pos_1][pos_2][curr_t][found.to_ulong()] - 1;
    }
    for (auto adj_1: graph[pos_1]) {
        for (auto adj_2: graph[pos_2]) {
            bitset<USEFULV> new_found = found;
            int score = 0;
            if (pos_1 == adj_1 && !new_found[pos_1]) {
                new_found[pos_1] = true;
                score += valves[pos_1] * (ENDTIME - curr_t);
            }
            if (pos_2 == adj_2 && !new_found[pos_2]) {
                new_found[pos_2] = true;
                score += valves[pos_2] * (ENDTIME - curr_t);
            }
            s = max(s, score + solve_2(adj_1, adj_2, new_found, curr_t + 1));
        }
    }
    memo_2[pos_1][pos_2][curr_t][found.to_ulong()] = s + 1;
    return s;
}

int main () {
    int m;
    int starting_loc;
    cin >> n >> m >> starting_loc;
    for (int i = 0; i < n; i++) {
        cin >> valves[i];
        if (valves[i] > 0) {
            graph[i].push_back(i); // self loop
        }
    }
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int f = 0; f <= ENDTIME; f++) {
                memo_2[i][j][f].resize(TTTV, 0);
            }
        }
    }

    cout << solve_1(starting_loc, {}, 1) << "\n";
    cout << solve_2(starting_loc, starting_loc, {}, 5) << "\n";
}
