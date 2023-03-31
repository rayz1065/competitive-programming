// https://training.olinfo.it/#/task/figurines/statement
#include <bits/stdc++.h>
#define MAXD 100005

using namespace std;

struct StNode {
    int day;
    int sum;
    StNode *l;
    StNode *r;
} *roots[MAXD];

StNode *st_add (StNode *node, int l, int r, int day, int x, int am) {
    if (node == NULL) {
        node = new StNode({ day, 0, NULL, NULL });
    }
    if (r < x || l > x) return node;
    if (node->day != day) {
        node = new StNode({ day, node->sum, node->l, node->r });
    }
    if (l == r) {
        node->sum += am;
        return node;
    }
    int mid = (l + r) >> 1;
    node->l = st_add(node->l, l, mid, day, x, am);
    node->r = st_add(node->r, mid + 1, r, day, x, am);
    node->sum = node->l->sum + node->r->sum;
    return node;
}

int st_sum (StNode *node, int l, int r, int from, int to) {
    if (!node || r < from || l > to) return 0;
    if (from <= l && r <= to) return node->sum;
    int mid = (l + r) >> 1;
    return st_sum(node->l, l, mid, from, to) + st_sum(node->r, mid + 1, r, from, to);
}

int n;
int curr_day;
vector<int> states[MAXD];

void init(int n) {
    ::n = n;
}

void log(vector<int>& added, vector<int>& removed) {
    curr_day++;
    StNode *root = roots[curr_day - 1];
    for (auto i: added) root = st_add(root, 0, n - 1, curr_day, i, +1);
    for (auto i: removed) root = st_add(root, 0, n - 1, curr_day, i, -1);
    roots[curr_day] = root;
}

int answer(int d, int x) {
    return st_sum(roots[d], 0, n - 1, x, n - 1);
}
