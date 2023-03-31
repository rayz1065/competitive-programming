#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

struct StNode {
    StNode *l;
    StNode *r;
    long long am;
    long long lazy_value;
};
struct SolInfo {
    long long sol;
    StNode* st;
};

int d_days;
vector<int> graph[MAXN];
int fruit_day[MAXN];
int fruit_am[MAXN];

StNode* st_set (StNode *curr, int node_l, int node_r, int l, int r, long long am);

long long st_am (StNode *curr) {
    if (!curr) return 0;
    return curr->am;
}

void st_lazy (StNode *curr, int node_l, int node_r) {
    if (!curr->lazy_value) return ;
    int mid = (node_l + node_r) >> 1;
    curr->l = st_set(curr->l, node_l, mid, node_l, mid, curr->lazy_value);
    curr->r = st_set(curr->r, mid + 1, node_r, mid + 1, node_r, curr->lazy_value);
    curr->lazy_value = 0;
}

void st_recalc (StNode *curr) {
    curr->am = max(st_am(curr->l), st_am(curr->r));
}

// first position which is greater than am
int st_ub (StNode *curr, int node_l, int node_r, long long am) {
    if (curr == NULL || curr->am <= am) return -1;
    if (node_l == node_r) return node_l;
    st_lazy(curr, node_l, node_r);
    int mid = (node_l + node_r) >> 1;
    int res_l = st_ub(curr->l, node_l, mid, am);
    if (res_l != -1) return res_l;
    return st_ub(curr->r, mid + 1, node_r, am);
}

StNode* st_set (StNode *curr, int node_l, int node_r, int l, int r, long long am) {
    if (node_l > r || node_r < l) return curr;
    if (curr == NULL) {
        curr = new StNode({ NULL, NULL, 0, 0 });
    }
    if (l <= node_l && node_r <= r) {
        if (node_l != node_r) {
            curr->lazy_value = am;
        }
        curr->am = am;
        return curr;
    }
    st_lazy(curr, node_l, node_r);
    int mid = (node_l + node_r) >> 1;
    curr->l = st_set(curr->l, node_l, mid, l, r, am);
    curr->r = st_set(curr->r, mid + 1, node_r, l, r, am);
    st_recalc(curr);
    return curr;
}

StNode* st_merge (StNode *a, StNode *b, int node_l, int node_r) {
    if (a == NULL) return b;
    if (b == NULL) return a;
    if (node_l == node_r) {
        a->am += b->am;
        delete b;
        return a;
    }
    st_lazy(a, node_l, node_r);
    st_lazy(b, node_l, node_r);
    int mid = (node_l + node_r) >> 1;
    a->l = st_merge(a->l, b->l, node_l, mid);
    a->r = st_merge(a->r, b->r, mid + 1, node_r);
    delete b;
    st_recalc(a);
    return a;
}

long long st_max (StNode *curr, int node_l, int node_r, int l, int r) {
    if (node_l > r || node_r < l || curr == NULL) return 0;
    if (l <= node_l && node_r <= r) {
        return curr->am;
    }
    st_lazy(curr, node_l, node_r);
    int mid = (node_l + node_r) >> 1;
    return max(st_max(curr->l, node_l, mid, l, r), \
               st_max(curr->r, mid + 1, node_r, l, r));
}

StNode* solve (int node) {
    StNode* sol = NULL;
    for (auto j: graph[node]) {
        StNode* info = solve(j);
        sol = st_merge(sol, info, 0, d_days - 1);
    }
    // cout << "sol[" << node << "] = " << sol.sol << "\n";
    if (fruit_am[node]) {
        for (int i = 0; i < d_days; i++) {
            // cout << st_max(sol, 0, d_days - 1, i, i) << " \n"[i + 1 == d_days];
        }
        // cut on day fruit_day[node], get all prev rewards
        long long take_curr = st_max(sol, 0, d_days - 1, 0, fruit_day[node]) + fruit_am[node];
        int ub = st_ub(sol, 0, d_days - 1, take_curr);
        if (ub == -1) {
            ub = d_days;
        }
        // cout << "For node " << node << ", day " << fruit_day[node] << " ub=" << ub << "\n";
        // update st
        if (ub - 1 >= fruit_day[node]) {
            // cout << "Setting [" << fruit_day[node] << ", " << ub - 1 << "] to " << take_curr << "\n";
            sol = st_set(sol, 0, d_days - 1, fruit_day[node], ub - 1, take_curr);
        } else {
            assert(false);
        }
        // cout << "Adding to " << node << "." << fruit_day[node] << " " << fruit_am[node] << "\n";
    }
    // cout << "tot sum " << node << " is " << st_sum(sol, 0, d_days - 1, 0, d_days - 1) << "\n";
    // for (int i = 0; i < d_days; i++) {
    //     cout << st_max(sol, 0, d_days - 1, i, i) << " \n"[i + 1 == d_days];
    // }
    return sol;
}

long long harvest(int n, int m, int k, vector<int>& p,
                  vector<int>& v, vector<int>& d, vector<int>& w) {
    // compress indexes in d
    for (int i = 1; i < n; i++) {
        graph[p[i]].push_back(i);
    }
    d_days = k + 1;
    for (int i = 0; i < m; i++) {
        fruit_day[v[i]] = d[i];
        fruit_am[v[i]] = w[i];
    }
    StNode *root = solve(0);
    return st_max(root, 0, d_days - 1, 0, d_days - 1);
}
