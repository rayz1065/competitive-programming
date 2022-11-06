#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define MAXR 505
#define MAXN 505
#define MAXD 100005 + MAXR * 4
#define POS(x) (x + 1000)

using namespace std;

void fastin (int &v) {
    v = 0;
    char c = getchar_unlocked();
    for (; c >= '0'; c = getchar_unlocked()) {
        v = v * 10 + c - '0';
    }
}

struct Crane {
    int x;
    int r;
    int t_turn_cost;
    int k_move_cost;
    int starting_pos;
} cranes[MAXN];

int d_dist, n;
int memo[2][MAXD];

bool in_range (int i, int x) {
    return cranes[i].x - cranes[i].r <= x && x <= cranes[i].x + cranes[i].r && cranes[i].x != x;
}

int move_cost (int i, int from, int to) {
    int s = 0;
    if ((from < cranes[i].x) != (to < cranes[i].x)) {
        // needs to turn
        s += cranes[i].t_turn_cost;
        int dist = from - cranes[i].x;
        from -= dist * 2;
    }
    // move the head
    int dist = abs(from - to);
    return s + cranes[i].k_move_cost * dist;
}

void move_crane (int i) {
    for (int b = cranes[i].x - cranes[i].r; b <= cranes[i].x + cranes[i].r; b++) {
        memo[1][b] = memo[0][b];
        if (b == cranes[i].x) continue ;
        for (int a = cranes[i].x - cranes[i].r; a <= cranes[i].x + cranes[i].r; a++) {
            if (a == cranes[i].x) {
                continue ;
            }
            int new_cost = move_cost(i, cranes[i].starting_pos, a) + move_cost(i, a, b);
            memo[1][b] = min(memo[1][b], new_cost + memo[0][a]);
            // cout << "for crane " << i << " cost[" << b << "] = " << memo[1][b] << " -> " <<
            //     memo[0][a] << " (" << a << ")" << " + " <<
            //     move_cost(i, cranes[i].starting_pos, a) << " + " <<
            //     move_cost(i, a, b) + memo[0][a] << "\n";
        }
    }
    for (int b = cranes[i].x - cranes[i].r; b <= cranes[i].x + cranes[i].r; b++) {
        memo[0][b] = memo[1][b];
    }
}

int solve () {
    fill(memo[0], memo[0] + MAXD, INT_MAX >> 1);
    memo[0][POS(0)] = 0; // start
    for (int i = 0; i < n && cranes[i].x - MAXD <= d_dist; i++) {
        move_crane(i);
    }
    return memo[0][d_dist];
}

int main () {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    fastin(d_dist), fastin(n);
    d_dist = POS(d_dist);
    for (int i = 0; i < n; i++) {
        int pointing_right;
        fastin(cranes[i].x), fastin(cranes[i].r), fastin(cranes[i].t_turn_cost);
        fastin(cranes[i].k_move_cost), fastin(pointing_right);
        cranes[i].x = POS(cranes[i].x);
        cranes[i].starting_pos = cranes[i].r * (pointing_right ? +1 : -1) + cranes[i].x;
    }
    cout << solve() << "\n";
}
