#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

struct StNode {
    StNode *l;
    StNode *r;
    long long am;
};

int d_days;
vector<int> graph[MAXN];
int fruit_day[MAXN];
int fruit_am[MAXN];

void st_recalc (StNode *curr) {
    curr->am = (curr->l ? curr->l->am : 0) + \
               (curr->r ? curr->r->am : 0);
}

long long st_sum (StNode *curr, int node_l, int node_r, int l, int r) {
    if (node_l > r || node_r < l || curr == NULL) return 0;
    if (l <= node_l && node_r <= r) return curr->am;
    int mid = (node_l + node_r) >> 1;
    return st_sum(curr->l, node_l, mid, l, r) +
           st_sum(curr->r, mid + 1, node_r, l, r);
}

long long st_prefix_sum (StNode *root, int i) {
    return st_sum(root, 0, d_days - 1, 0, i);
}

// first position which is greater than am
int st_ub (StNode *curr, int node_l, int node_r, long long am, long long &curr_sum) {
    if (curr == NULL) return -1;
    if (curr_sum + curr->am <= am) {
        curr_sum += curr->am;
        return -1;
    }
    if (node_l == node_r) return node_l;
    int mid = (node_l + node_r) >> 1;
    int l_res = st_ub(curr->l, node_l, mid, am, curr_sum);
    if (l_res != -1) return l_res;
    return st_ub(curr->r, mid + 1, node_r, am, curr_sum);
}

StNode* st_drop (StNode *curr, int node_l, int node_r, int l, int r, long long &sum) {
    if (node_l > r || node_r < l || curr == NULL) return curr;
    if (l <= node_l && node_r <= r) {
        sum += curr->am;
        // delete curr;
        return NULL;
    }
    int mid = (node_l + node_r) >> 1;
    curr->l = st_drop(curr->l, node_l, mid, l, r, sum);
    curr->r = st_drop(curr->r, mid + 1, node_r, l, r, sum);
    st_recalc(curr);
    return curr;
}

StNode* st_add (StNode *curr, int node_l, int node_r, int x, long long am) {
    if (node_l > x || node_r < x) return curr;
    if (curr == NULL) {
        curr = new StNode({ NULL, NULL, 0 });
    }
    if (node_l == node_r) {
        curr->am += am;
        return curr;
    }
    int mid = (node_l + node_r) >> 1;
    curr->l = st_add(curr->l, node_l, mid, x, am);
    curr->r = st_add(curr->r, mid + 1, node_r, x, am);
    st_recalc(curr);
    return curr;
}

StNode* st_merge (StNode *a, StNode *b, int node_l, int node_r) {
    if (a == NULL) return b;
    if (b == NULL) return a;
    if (node_l == node_r) {
        a->am += b->am;
        // delete b;
        return a;
    }
    int mid = (node_l + node_r) >> 1;
    a->l = st_merge(a->l, b->l, node_l, mid);
    a->r = st_merge(a->r, b->r, mid + 1, node_r);
    // delete b;
    st_recalc(a);
    return a;
}

StNode *st_add_range (StNode *curr, int l, int r, long long am) {
    curr = st_add(curr, 0, d_days - 1, l, am);
    curr = st_add(curr, 0, d_days - 1, r + 1, -am);
    return curr;
}

StNode* solve (int node) {
    StNode* sol = NULL;
    for (auto j: graph[node]) {
        StNode* info = solve(j);
        sol = st_merge(sol, info, 0, d_days - 1);
    }
#ifdef DEBUG
    cout << node << "\t";
    for (int i = 0; i < d_days; i++) {
        cout << st_prefix_sum(sol, i) << " \n"[i + 1 == d_days];
    }
#endif
    if (fruit_am[node]) {
        // cut on day fruit_day[node], get all prev rewards
        long long take_curr = st_prefix_sum(sol, fruit_day[node]) + fruit_am[node];
        long long curr_sum = 0;
        int ub = st_ub(sol, 0, d_days - 1, take_curr, curr_sum);
        if (ub == -1) {
            ub = d_days;
        }
        // update st
#ifdef DEBUG
        cout << "For node " << node << ", " << take_curr << ", day " << fruit_day[node] << ", ub=" << ub << "\n";
        cout << "Setting [" << fruit_day[node] << ", " << ub - 1 << "] to " << take_curr << "\n";
#endif
        if (fruit_day[node] + 1 < ub) {
            long long sum = 0;
            sol = st_drop(sol, 0, d_days - 1, fruit_day[node] + 1, ub - 1, sum);
            sol = st_add_range(sol, ub, d_days, sum);
#ifdef DEBUG
            cout << "Dropped [" << fruit_day[node] + 1 << ", " << ub - 1 << "]\n";
            cout << node << "\t";
            for (int i = 0; i < d_days; i++) {
                cout << st_prefix_sum(sol, i) << " \n"[i + 1 == d_days];
            }
#endif
        }
        sol = st_add_range(sol, fruit_day[node], ub - 1, fruit_am[node]);
    }
#ifdef DEBUG
    cout << node << "\t";
    for (int i = 0; i < d_days; i++) {
        cout << st_prefix_sum(sol, i) << " \n"[i + 1 == d_days];
    }
    cout.flush();
#endif
    return sol;
}

long long harvest(int n, int m, int k, vector<int>& p,
                  vector<int>& v, vector<int>& d, vector<int>& w) {
    StNode *curr = NULL;
    d_days = k + 1;

    for (int i = 1; i < n; i++) {
        graph[p[i]].push_back(i);
    }
    for (int i = 0; i < m; i++) {
        fruit_day[v[i]] = d[i];
        fruit_am[v[i]] = w[i];
    }
    StNode *root = solve(0);
    return st_prefix_sum(root, d_days - 1);
}
