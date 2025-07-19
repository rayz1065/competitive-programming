#include <bits/stdc++.h>
#define MAXN 300005
#define MAXQ 300005
#define ST_SIZE (MAXQ * 4 + 5)
#define ST_LEFT(x) ((x) << 1)
#define ST_RIGHT(x) (((x) << 1) + 1)
#define ST_ROOT 1

using namespace std;

typedef long long ll;

int n, q;

struct Query {
    char type;
    int u, v;
} queries[MAXQ];
struct UfdsUndo {
    int u, v;
    int parent_u, parent_v;
    int rank_u, rank_v;
};
stack<UfdsUndo> ufds_stack;
int ufds_parent[MAXN];
int ufds_rank[MAXN];
int components;
int solutions[MAXQ];

struct StQuery {
    int u, v;
};
struct StNode {
    vector<StQuery> queries;
} st[ST_SIZE];

ll get_edge_key(int u, int v) {
    if (u < v) swap(u, v);
    return (ll)u * n + v;
}

void ufds_init() {
    components = n;
    for (int i = 0; i < n; i++) {
        ufds_parent[i] = i;
        ufds_rank[i] = 0;
    }
}

int ufds_find(int u) {
    if (ufds_parent[u] == u) {
        return u;
    }
    return ufds_find(ufds_parent[u]);
}

void ufds_join(int u, int v) {
    u = ufds_find(u), v = ufds_find(v);
    assert(u != v);
    if (ufds_rank[u] > ufds_rank[v]) {
        swap(u, v);
    }

    ufds_stack.push(
        {u, v, ufds_parent[u], ufds_parent[v], ufds_rank[u], ufds_rank[v]});

    ufds_parent[u] = v;
    if (ufds_rank[u] == ufds_rank[v]) {
        ufds_rank[v] += 1;
    }
    components -= 1;
}

void ufds_pop() {
    auto op = ufds_stack.top();
    ufds_stack.pop();
    int u = op.u, v = op.v;
    ufds_parent[u] = op.parent_u;
    ufds_parent[v] = op.parent_v;
    ufds_rank[u] = op.rank_u;
    ufds_rank[v] = op.rank_v;
    components += 1;
}

void _st_add(int node, int l, int r, int tl, int tr, StQuery &query) {
    if (tl > r || tr < l) {
        return;
    }
    if (tl <= l && r <= tr) {
        st[node].queries.push_back(query);
        return;
    }
    int mid = (l + r) / 2;
    _st_add(ST_LEFT(node), l, mid, tl, tr, query);
    _st_add(ST_RIGHT(node), mid + 1, r, tl, tr, query);
}

void _st_dfs(int node, int l, int r) {
    int pushed = 0;
    for (auto &query : st[node].queries) {
        int u = ufds_find(query.u), v = ufds_find(query.v);
        if (u != v) {
            ufds_join(u, v);
            pushed += 1;
        }
    }

    if (l != r) {
        int mid = (l + r) / 2;
        _st_dfs(ST_LEFT(node), l, mid);
        _st_dfs(ST_RIGHT(node), mid + 1, r);
    } else {
        solutions[l] = components;
    }

    for (int i = 0; i < pushed; i++) {
        ufds_pop();
    }
}

void st_add(int l, int r, StQuery &query) {
    _st_add(ST_ROOT, 0, q, l, r, query);
}

void st_dfs() { _st_dfs(ST_ROOT, 0, q); }

int main() {
#ifndef DEBUG
    fstream cin, cout;
    cin.open("connect.in", ios::in);
    cout.open("connect.out", ios::out);
#else
    cin.tie(NULL);
    cout.tie(NULL);
#endif
    ios_base::sync_with_stdio(false);

    cin >> n >> q;
    unordered_map<ll, pair<int, int>> edges;
    for (int i = 0; i < q; i++) {
        char type;
        int u = 0, v = 0;
        cin >> type;
        if (type != '?') {
            cin >> u >> v;
            u--, v--;
            edges[get_edge_key(u, v)] = {u, v};
        }
        queries[i] = {type, u, v};
    }

    unordered_map<ll, int> added_at;
    for (int i = 0; i < q; i++) {
        if (queries[i].type == '?') {
            continue;
        }

        ll edge_key = get_edge_key(queries[i].u, queries[i].v);
        if (queries[i].type == '+') {
            added_at[edge_key] = i;
        } else if (queries[i].type == '-') {
            int l = added_at[edge_key];
            StQuery st_query = {queries[i].u, queries[i].v};
            st_add(l, i, st_query);
            assert(added_at.erase(edge_key));
        }
    }
    for (auto i : added_at) {
        auto edge = edges[i.first];
        StQuery st_query = {edge.first, edge.second};
        st_add(i.second, q, st_query);
    }

    ufds_init();
    st_dfs();

    for (int i = 0; i < q; i++) {
        if (queries[i].type == '?') {
            cout << solutions[i] << "\n";
        }
    }
}
