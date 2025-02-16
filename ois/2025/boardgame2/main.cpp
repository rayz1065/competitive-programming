#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

typedef long long ll;

int n;
vector<pair<int, int>> graph[MAXN];
short can_win_memo[MAXN];
ll memo[MAXN];

int fastin() {
    int v = 0;
    char c = getchar_unlocked();
    while (c >= '0') {
        v = v * 10 + c - '0';
        c = getchar_unlocked();
    }
    return v;
}

bool can_win(int i) {
    if (can_win_memo[i]) {
        return can_win_memo[i] - 1;
    }

    can_win_memo[i] = 1;

    for (auto j : graph[i]) {
        if (!can_win(j.first)) {
            can_win_memo[i] = 2;
            break;
        }
    }

    return can_win_memo[i] - 1;
}

ll solve(int i, bool is_winner) {
    if (memo[i]) {
        return memo[i] - 1;
    }

    memo[i] = is_winner ? LLONG_MAX >> 1 : 1;

    for (auto j : graph[i]) {
        if (is_winner && can_win(j.first)) {
            continue;
        }

        ll sub_res = solve(j.first, !is_winner);
        if (is_winner) {
            memo[i] = min(memo[i], sub_res + j.second + 1);
        } else {
            memo[i] = max(memo[i], sub_res + 1);
        }
    }

    return memo[i] - 1;
}

int main() {
    n = fastin();
    int m = fastin();
    while (m--) {
        int a = fastin() - 1, b = fastin() - 1, cost = fastin();
        graph[a].push_back({b, cost});
    }

    bool winner_is_alice = can_win(0);
    cout << (winner_is_alice ? "Alice" : "Bob") << "\n";
    cout << solve(0, winner_is_alice) << "\n";
}
