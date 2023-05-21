#include <bits/stdc++.h>
#define MAXN 60

using namespace std;

int n, m;
bool obstacle[MAXN][MAXN];
int cost[MAXN][MAXN];
int value[MAXN][MAXN];

int MOV_X[] = { 1, 0, -1, 0 };
int MOV_Y[] = { 0, 1, 0, -1 };

bool in_range (int x, int y) {
    return 1 < x && x < m && 1 < y && y < n;
}

int simulate (int x, int y, int direction, int lifetime) {
    int score = 0;
    while (lifetime > 1) {
        int dx = MOV_X[direction], dy = MOV_Y[direction];
        x += dx, y += dy;
        lifetime -= 1;

        if (obstacle[x][y]) {
            score += value[x][y];
            lifetime -= cost[x][y];
            direction = (direction - 1 + 4) % 4;
            x -= dx, y -= dy;
        }
    }
    return score;
}

int main () {
    int cost_wall, p_bumpers;
    cin >> m >> n >> cost_wall >> p_bumpers;

    for (int x = 1; x <= m; x++) {
        for (int y = 1; y <= n; y++) {
            if (!in_range(x, y)) {
                obstacle[x][y] = true;
                cost[x][y] = cost_wall;
                value[x][y] = 0;
            }
        }
    }

    for (int i = 0; i < p_bumpers; i++) {
        int x, y;
        cin >> x >> y;
        obstacle[x][y] = true;
        cin >> value[x][y];
        cin >> cost[x][y];
    }

    int total_score = 0;
    while (true) {
        int x, y, direction, lifetime;
        if (!(cin >> x >> y >> direction >> lifetime)) {
            break ;
        }
        int score = simulate(x, y, direction, lifetime);
        total_score += score;
        cout << score << "\n";
    }
    cout << total_score << "\n";
}
