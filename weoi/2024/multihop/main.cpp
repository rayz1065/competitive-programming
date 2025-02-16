#include <bits/stdc++.h>
#define MAXN 100005
#define LOGMAXN 20

using namespace std;

typedef long long ll;

int n, keep_moving_cost;
vector<int> low_power, high_power;
vector<int> graph[MAXN];

struct DeliveryCosts {
    ll stab2stab;
    ll stab2move;
    ll move2stab;
    ll move2move;
};

struct AncNode {
    int anc;
    DeliveryCosts up;
    DeliveryCosts down;
} ancestors[MAXN][LOGMAXN];
int depth[MAXN];

void dfs(int node, int parent) {
    ancestors[node][0].anc = parent;
    for (auto j : graph[node]) {
        if (j != parent) {
            depth[j] = depth[node] + 1;
            dfs(j, node);
        }
    }
}

DeliveryCosts combine_costs(DeliveryCosts a, DeliveryCosts b) {
    DeliveryCosts res;
    res.stab2stab = min(a.stab2stab + b.stab2stab, a.stab2move + b.move2stab);
    res.stab2move = min(a.stab2stab + b.stab2move, a.stab2move + b.move2move);
    res.move2stab = min(a.move2stab + b.stab2stab, a.move2move + b.move2stab);
    res.move2move = min(a.move2stab + b.stab2move, a.move2move + b.move2move);
    return res;
}

void make_anc() {
    dfs(0, -1);
    for (int i = 0; i < n; i++) {
        int anc = ancestors[i][0].anc;

        if (anc == -1) {
            continue;
        }

        ancestors[i][0].up.stab2stab =
            min(low_power[i], high_power[i] + keep_moving_cost);
        ancestors[i][0].up.stab2move = high_power[i] + keep_moving_cost;
        ancestors[i][0].up.move2move = keep_moving_cost;
        ancestors[i][0].up.move2stab = keep_moving_cost;

        ancestors[i][0].down.stab2stab =
            min(low_power[anc], high_power[anc] + keep_moving_cost);
        ancestors[i][0].down.stab2move = high_power[anc] + keep_moving_cost;
        ancestors[i][0].down.move2move = keep_moving_cost;
        ancestors[i][0].down.move2stab = keep_moving_cost;
    }

    for (int j = 1; j < LOGMAXN; j++) {
        for (int i = 0; i < n; i++) {
            int anc = ancestors[i][j - 1].anc;
            if (anc == -1) {
                ancestors[i][j].anc = -1;
                continue;
            }
            int ancanc = ancestors[anc][j - 1].anc;
            if (ancanc == -1) {
                ancestors[i][j].anc = -1;
                continue;
            }

            ancestors[i][j].anc = ancanc;
            ancestors[i][j].up =
                combine_costs(ancestors[i][j - 1].up, ancestors[anc][j - 1].up);
            ancestors[i][j].down = combine_costs(ancestors[anc][j - 1].down,
                                                 ancestors[i][j - 1].down);
        }
    }
}

ll lca(int u, int v) {
    DeliveryCosts u_res = {0, LLONG_MAX >> 1, 0, 0},
                  v_res = {0, LLONG_MAX >> 1, 0, 0};

    for (int j = LOGMAXN - 1; j >= 0; j--) {
        if (depth[v] - (1 << j) >= depth[u]) {
            v_res = combine_costs(ancestors[v][j].down, v_res);
            v = ancestors[v][j].anc;
        } else if (depth[u] - (1 << j) >= depth[v]) {
            u_res = combine_costs(u_res, ancestors[u][j].up);
            u = ancestors[u][j].anc;
        }
    }

    for (int j = LOGMAXN - 1; j >= 0; j--) {
        if (ancestors[u][j].anc != ancestors[v][j].anc) {
            u_res = combine_costs(u_res, ancestors[u][j].up);
            v_res = combine_costs(ancestors[v][j].down, v_res);
            u = ancestors[u][j].anc;
            v = ancestors[v][j].anc;
        }
    }

    if (u != v) {
        u_res = combine_costs(u_res, ancestors[u][0].up);
        v_res = combine_costs(ancestors[v][0].down, v_res);
    }

    return combine_costs(u_res, v_res).stab2stab;
}

void init(int n, int keep_moving_cost, vector<int> low_power,
          vector<int> high_power, vector<int> u, vector<int> v) {
    assert(low_power.size() != 0);
    ::n = n;
    ::keep_moving_cost = keep_moving_cost;
    ::low_power = low_power;
    ::high_power = high_power;

    for (int i = 0; i < n - 1; i++) {
        graph[u[i]].push_back(v[i]);
        graph[v[i]].push_back(u[i]);
    }

    make_anc();
}

long long query(int u, int v) { return lca(u, v); }
