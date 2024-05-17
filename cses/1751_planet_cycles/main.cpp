#include <bits/stdc++.h>
#define MAXN 200005
#define LOGMAXN 20

using namespace std;

int n;
int teleporters[MAXN];
int start_time[MAXN], end_time[MAXN], curr_time;
int cycle_id[MAXN], cycle_delta[MAXN], depth[MAXN], cycle_length[MAXN];

int up[MAXN][LOGMAXN];

void set_cycle_length(int node, int length) {
    while (cycle_length[node] == 0) {
        cycle_length[node] = length;
        node = teleporters[node];
    }
}

void dfs(int node) {
    start_time[node] = ++curr_time;

    int next = teleporters[node];

    if (end_time[next]) {
        depth[node] = depth[next] + 1;
    } else if (start_time[next]) {
        cycle_id[node] = next;
        cycle_delta[node] = 1;
    } else {
        dfs(next);

        if (depth[next] == 0 && cycle_id[next] != next) {
            cycle_id[node] = cycle_id[next];
            cycle_delta[node] = cycle_delta[node] = cycle_delta[next] + 1;
        } else {
            depth[node] = depth[next] + 1;
        }
    }

    if (cycle_id[node] == node) {
        set_cycle_length(node, cycle_delta[node]);
    }

    end_time[node] = ++curr_time;
}

void find_cycles() {
    fill(cycle_id, cycle_id + n, -1);

    for (int i = 0; i < n; i++) {
        if (!start_time[i]) {
            dfs(i);
        }
    }
}

void make_up() {
    for (int i = 0; i < n; i++) {
        up[i][0] = teleporters[i];
    }

    for (int j = 1; j < LOGMAXN; j++) {
        for (int i = 0; i < n; i++) {
            up[i][j] = up[up[i][j - 1]][j - 1];
        }
    }
}

int get_cycle_distance(int node) {
    int res = 0;

    // get to the same depth
    for (int j = LOGMAXN - 1; j >= 0; j--) {
        int new_depth = depth[node] - (1 << j);
        if (new_depth >= 0) {
            res += 1 << j;
            node = up[node][j];
        }
    }

    int cycle = cycle_id[node];
    int length = cycle_length[cycle];
    res += length;

    return res;
}

int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> teleporters[i];
        teleporters[i]--;
    }

    find_cycles();

    make_up();

    for (int i = 0; i < n; i++) {
        cout << get_cycle_distance(i) << " \n"[i + 1 == n];
    }
}
