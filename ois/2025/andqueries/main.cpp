#include <bits/stdc++.h>
#define MAXN 100005
#define MAXQ 100005
#define ST_SIZE (MAXQ * 4 + 5)
#define ST_ROOT 1
#define ST_LEFT(x) ((x) << 1)
#define ST_RIGHT(x) (((x) << 1) + 1)

using namespace std;

typedef long long ll;

int n, q;
unordered_map<ll, int> edges_indexes;

struct {
    int u, v, value;
} edges[MAXN];
struct {
    int u, v, value;
} queries[MAXQ];
int dsu_parent[MAXN];
int dsu_rank[MAXN];
int dsu_size[MAXN];
struct DsuUndo {
    int u, v;
    int parent_u, parent_v;
    int rank_u, rank_v;
    int size_u, size_v;
    ll dsu_weight;
};
stack<DsuUndo> dsu_stack;
struct DsuOp {
    int u, v;
};

ll dsu_weight;
ll solutions[MAXQ];

ll get_edge_key(int u, int v) {
    if (u > v) swap(u, v);
    return (ll)u * n + v;
}

int dsu_find(int u) {
    if (dsu_parent[u] == u) {
        return u;
    }
    return dsu_find(dsu_parent[u]);
}

ll get_cc_weight(int cc_size) { return (ll)cc_size * (cc_size - 1) / 2; }

void dsu_merge(int u, int v) {
    u = dsu_find(u), v = dsu_find(v);
    assert(u != v);
    if (dsu_rank[u] > dsu_rank[v]) {
        swap(u, v);
    }
    dsu_stack.push({u, v, dsu_parent[u], dsu_parent[v], dsu_rank[u],
                    dsu_rank[v], dsu_size[u], dsu_size[v], dsu_weight});
    dsu_parent[u] = v;

    dsu_weight -= get_cc_weight(dsu_size[v]);
    dsu_weight -= get_cc_weight(dsu_size[u]);

    dsu_size[v] += dsu_size[u];

    dsu_weight += get_cc_weight(dsu_size[v]);

    if (dsu_rank[u] == dsu_rank[v]) {
        dsu_rank[v] += 1;
    }
}

void dsu_undo() {
    auto op = dsu_stack.top();
    dsu_stack.pop();
    dsu_rank[op.u] = op.rank_u;
    dsu_rank[op.v] = op.rank_v;
    dsu_size[op.u] = op.size_u;
    dsu_size[op.v] = op.size_v;
    dsu_parent[op.u] = op.parent_u;
    dsu_parent[op.v] = op.parent_v;
    dsu_weight = op.dsu_weight;
}

void dsu_init() {
    dsu_weight = 0;
    for (int i = 0; i < n; i++) {
        dsu_size[i] = 1;
        dsu_parent[i] = i;
        dsu_rank[i] = 0;
    }
}

struct StNode {
    vector<DsuOp> operations;
} st[ST_SIZE];

void _add_operation(int node, int l, int r, int tl, int tr, DsuOp &op) {
    if (tl > r || tr < l) return;
    if (tl <= l && r <= tr) {
        st[node].operations.push_back(op);
        return;
    }
    int mid = (l + r) / 2;
    _add_operation(ST_LEFT(node), l, mid, tl, tr, op);
    _add_operation(ST_RIGHT(node), mid + 1, r, tl, tr, op);
}

void _st_dfs(int bit, int node, int l, int r) {
    for (auto &operation : st[node].operations) {
        dsu_merge(operation.u, operation.v);
    }

    if (l != r) {
        int mid = (l + r) / 2;
        _st_dfs(bit, ST_LEFT(node), l, mid);
        _st_dfs(bit, ST_RIGHT(node), mid + 1, r);
    } else {
        solutions[l] += (1 << bit) * dsu_weight;
    }

    for (auto &operation : st[node].operations) {
        dsu_undo();
    }
}

void add_operation(int tl, int tr, DsuOp &op) {
    _add_operation(ST_ROOT, 0, q, tl, tr, op);
}
void st_dfs(int bit) { _st_dfs(bit, ST_ROOT, 0, q); }

void compute_solutions(int bit) {
    vector<pair<pair<int, int>, DsuOp>> operations;
    vector<int> present_since(n - 1, -1);

    for (int i = 0; i < n - 1; i++) {
        if (edges[i].value & (1 << bit)) {
            present_since[i] = 0;
        }
    }

    for (int i = 0; i < q; i++) {
        auto query = queries[i];
        int edge_idx = edges_indexes[get_edge_key(query.u, query.v)];
        bool was_present = present_since[edge_idx] != -1;
        bool new_present = query.value & (1 << bit);
        if (was_present && !new_present) {
            operations.push_back(
                {{present_since[edge_idx], i}, {query.u, query.v}});
            present_since[edge_idx] = -1;
        } else if (!was_present && new_present) {
            present_since[edge_idx] = i + 1;
        }
    }

    for (int i = 0; i < n - 1; i++) {
        if (present_since[i] != -1) {
            operations.push_back(
                {{present_since[i], q}, {edges[i].u, edges[i].v}});
        }
    }

    for (int i = 0; i < ST_SIZE; i++) {
        st[i].operations.clear();
    }
    for (auto &i : operations) {
        add_operation(i.first.first, i.first.second, i.second);
    }

    dsu_init();
    st_dfs(bit);
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;

    for (int i = 0; i < n - 1; i++) {
        int u, v, value;
        cin >> u >> v >> value;
        edges[i] = {u, v, value};
        edges_indexes[get_edge_key(u, v)] = i;
    }

    cin >> q;
    for (int i = 0; i < q; i++) {
        int u, v, value;
        cin >> u >> v >> value;
        queries[i] = {u, v, value};
    }

    for (int i = 0; i < 30; i++) {
        compute_solutions(i);
    }

    for (int i = 0; i < q + 1; i++) {
        cout << solutions[i] << " \n"[i + 1 == q + 1];
    }
}
