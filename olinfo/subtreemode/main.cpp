#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define MAXN 1000005

using namespace std;

struct TreapNode {
    int key;
    int priority;
    int freq;
    TreapNode *l;
    TreapNode *r;
};
typedef TreapNode* TreapNodeP;

inline bool compare_freqs (int new_freq, int new_color, int old_freq, int old_color) {
    return new_freq > old_freq || \
          (new_freq == old_freq && new_color < old_color);
}

TreapNode* treap_merge (TreapNode *l, TreapNode *r) {
    if (l == NULL) {
        return r;
    }
    if (r == NULL) {
        return l;
    }
    // all keys in l are smaller than keys in r
    // pick the new root
    if (l->priority > r->priority) {
        l->r = treap_merge(l->r, r);
        return l;
    } else {
        r->l = treap_merge(l, r->l);
        return r;
    }
}

void split (TreapNode *node, int x, TreapNodeP &l, TreapNodeP &r, TreapNodeP &eq) {
    if (node == NULL) {
        l = r = eq = NULL;
        return ;
    }
    // splits the treap by x, with L having keys less or equal, and R having keys greater
    if (node->key < x) {
        // left tree is all on the left
        split(node->r, x, node->r, r, eq);
        l = node;
    } else if (node->key == x) {
        // same value encountered
        l = node->l, r = node->r, eq = node;
    } else {
        // right tree is all on the right
        split(node->l, x, l, node->l, eq);
        r = node;
    }
}

/**
 * does not check whether the node is already present...
 */
TreapNode *insert (TreapNode *node, int x, int y) {
    if (node == NULL) {
        return new TreapNode({ x, y, 1, NULL, NULL });
    }
    // explore the BST, find place where node->priority < y
    if (node->priority < y) {
        // insert here
        TreapNodeP l, r, eq;
        split(node, x, l, r, eq);
        return new TreapNode({ x, y, 1, l, r });
    }
    if (x > node->key) {
        node->r = insert(node->r, x, y);
    } else {
        node->l = insert(node->l, x, y);
    }
    return node;
}

TreapNode *treap_find (TreapNode *node, int x) {
    if (node == NULL) {
        return NULL;
    }
    if (x > node->key) {
        return treap_find(node->r, x);
    } else if (x == node->key) {
        return node;
    } else {
        return treap_find(node->l, x);
    }
}

struct UnionInfo {
    TreapNode *merged;
    int max_freq;
    int color;
};

UnionInfo treap_union (TreapNode *t1, TreapNode *t2) {
    if (t1 == NULL) {
        return { t2, 0, 0 };
    }
    if (t2 == NULL) {
        return { t1, 0, 0 };
    }
    if (t1->priority < t2->priority) {
        swap(t1, t2);
    }
    // t1 has highest priority
    TreapNode *root = t1, *l, *r, *eq;
    split(t2, t1->key, l, r, eq);
    if (eq) {
        root->freq += eq->freq;
        // delete info.eq;
    }
    int max_freq = root->freq, color = root->key;
    auto union_l = treap_union(t1->l, l);
    auto union_r = treap_union(t1->r, r);
    root->l = union_l.merged;
    root->r = union_r.merged;
    if (compare_freqs(union_l.max_freq, union_l.color, max_freq, color)) {
        max_freq = union_l.max_freq;
        color = union_l.color;
    }
    if (compare_freqs(union_r.max_freq, union_r.color, max_freq, color)) {
        max_freq = union_r.max_freq;
        color = union_r.color;
    }
    return { root, max_freq, color };
}

struct NodeInfo {
    int best_color;
    int max_freq;
    TreapNode *freqs;
};

vector<int> color;
vector<int> parent;
vector<int> graph[MAXN];
vector<int> sol;
NodeInfo node_info[MAXN];

void calc_freqs (int node) {
    if (graph[node].size() == 0) {
        sol[node] = color[node];
        node_info[node] = {
            color[node], 1, insert(NULL, color[node], rand())
        };
        return ;
    }
    int best_node;
    for (auto i: graph[node]) {
        auto info = node_info[i];
        if (!node_info[node].freqs) {
            node_info[node] = info;
            best_node = i;
        } else if (info.freqs->priority > node_info[node].freqs->priority) {
            best_node = i;
            node_info[node] = info;
        }
    }

    auto found = treap_find(node_info[node].freqs, color[node]);
    int node_color_freq;
    if (found) {
        found->freq++;
        node_color_freq = found->freq;
    } else {
        node_info[node].freqs = insert(node_info[node].freqs, color[node], rand());
        node_color_freq = 1;
    }
    if (compare_freqs(node_color_freq, color[node], node_info[node].max_freq, node_info[node].best_color)) {
        // node color overtakes as best
        node_info[node].best_color = color[node];
        node_info[node].max_freq = node_color_freq;
    }

    for (auto i: graph[node]) {
        if (i == best_node) {
            continue ;
        }
        if (compare_freqs(node_info[i].max_freq, node_info[i].best_color, node_info[node].max_freq, node_info[node].best_color)) {
            node_info[node].best_color = node_info[i].best_color;
            node_info[node].max_freq = node_info[i].max_freq;
        }
        auto union_info = treap_union(node_info[node].freqs, node_info[i].freqs);
        node_info[node].freqs = union_info.merged;
        if (compare_freqs(union_info.max_freq, union_info.color, node_info[node].max_freq, node_info[node].best_color)) {
            node_info[node].best_color = union_info.color;
            node_info[node].max_freq = union_info.max_freq;
        }
    }
    sol[node] = node_info[node].best_color;
    return ;
}

vector<int> solve(int n, vector<int> p, vector<int> a) {
    srand(time(NULL));
    color = a;
    parent = p;
    for (int i = 1; i < n; i++) {
        graph[p[i]].push_back(i);
    }
    sol.resize(n);
    for (int i = n - 1; i >= 0; i--) {
        calc_freqs(i);
    }
    return sol;
}
