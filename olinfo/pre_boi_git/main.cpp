#include <bits/stdc++.h>
#define MAXN 100005
using namespace std;

struct StNode {
    int version;    // version for this node
    StNode *left;   // left child
    StNode *right;  // right child
    long long lazy_value; // lazy propagation
    long long sum;
};

int n_nodes;
vector<StNode*> versions;
int next_node_idx = 0;
StNode all_nodes[10000000];

StNode *new_node (StNode initial_value) {
    all_nodes[next_node_idx] = initial_value;
    return &(all_nodes[next_node_idx++]);
}

StNode *st_update (StNode *node, int node_l, int node_r, int l, int r, int version, long long x);

void lazy_propagate (StNode *node, int node_l, int node_r) {
    long long lazy_value = node->lazy_value;
    if (lazy_value == 0) {
        return ;
    }
    // assert(node_l < node_r);
    // propagate value to children
    node->lazy_value = 0;
    int mid = (node_l + node_r) / 2;
    node->left = st_update(node->left, node_l, mid, node_l, mid, node->version, lazy_value);
    node->right = st_update(node->right, mid + 1, node_r, mid + 1, node_r, node->version, lazy_value);
}

StNode *update_version (StNode *node, int version) {
    if (node->version == version) {
        return node;
    }
    // maintain the old version and create a new node
    return new_node({
        version,
        node->left,
        node->right,
        node->lazy_value,
        node->sum
    });
}

StNode *st_update (StNode *node, int node_l, int node_r, int l, int r, int version, long long x) {
    // assert(node_l <= node_r && node != NULL);
    if (node_r < l || node_l > r) {
        // nothing to update
        return node;
    }
    node = update_version(node, version);
    if (l <= node_l && node_r <= r) {
        // fully contained
        node->sum += x * (node_r - node_l + 1);
        if (node_l < node_r) {
            node->lazy_value += x;
        }
        return node;
    }
    // not fully contained
    lazy_propagate(node, node_l, node_r);
    int mid = (node_l + node_r) / 2;
    node->left = st_update(node->left, node_l, mid, l, r, version, x);
    node->right = st_update(node->right, mid + 1, node_r, l, r, version, x);
    node->sum = node->left->sum + node->right->sum;
    return node;
}

StNode* st_reset (StNode *node, int node_l, int node_r, int l, int r, int version, StNode *other_version) {
    // reset to version v, create new version version
    // assert(node_l <= node_r && node != NULL);
    if (node_r < l || node_l > r) {
        // nothing to update
        return node;
    }
    node = update_version(node, version);
    if (l <= node_l && node_r <= r) {
        // fully contained
        node->left = other_version->left;
        node->right = other_version->right;
        node->sum = other_version->sum;
        node->lazy_value = other_version->lazy_value;
        return node;
    }
    // not fully contained
    lazy_propagate(node, node_l, node_r);
    lazy_propagate(other_version, node_l, node_r);
    int mid = (node_l + node_r) / 2;
    node->left = st_reset(node->left, node_l, mid, l, r, version, other_version->left);
    node->right = st_reset(node->right, mid + 1, node_r, l, r, version, other_version->right);
    node->sum = node->left->sum + node->right->sum;
    return node;
}

StNode *st_make (int node_l, int node_r, vector<int> &values) {
    // assert(node_l <= node_r);
    // create the new node
    StNode *node = new_node({});
    if (node_l == node_r) {
        // fully contained
        node->sum = values[node_l];
        return node;
    }
    // not fully contained
    int mid = (node_l + node_r) / 2;
    node->left = st_make(node_l, mid, values);
    node->right = st_make(mid + 1, node_r, values);
    node->sum = node->left->sum + node->right->sum;
    return node;
}

long long st_sum (StNode *node, int node_l, int node_r, int l, int r) {
    // assert(node_l <= node_r && node != NULL);
    if (node_r < l || node_l > r) {
        // completely outside
        return 0;
    }
    if (l <= node_l && node_r <= r) {
        // fully contained
        return node->sum;
    }
    // not fully contained
    lazy_propagate(node, node_l, node_r);
    int mid = (node_l + node_r) / 2;
    long long left_s = st_sum(node->left, node_l, mid, l, r);
    long long right_s = st_sum(node->right, mid + 1, node_r, l, r);
    return left_s + right_s;
}

void print_st (StNode *st) {
    for (int i = 0; i < n_nodes; i++) {
        // complete lazy propagation
        st_sum(st, 0, n_nodes - 1, i, i);
    }
    for (int i = 0; i < n_nodes; i++) {
        cout << st_sum(st, 0, n_nodes - 1, i, i) << " \n"[i + 1 == n_nodes];
    }
}

void inizia (int N, vector<int> A) {
    ::n_nodes = N;
    versions.push_back(st_make(0, n_nodes - 1, A));
#ifdef DEBUG
    cout << "State 0\n";
    print_st(versions[0]);
#endif
}

void incrementa (int l, int r, int x) {
    // create a new state and increase [l, r) by v
    int new_version = versions.size();
    auto root = st_update(*versions.rbegin(), 0, n_nodes - 1, l, r - 1, new_version, x);
    versions.push_back(root);
#ifdef DEBUG
    printf("Executed operation incrementa(%d, %d, %d)\n", l, r, x);
    cout << "State " << new_version << "\n";
    print_st(*versions.rbegin());
#endif
}

void resetta (int l, int r, int v) {
    // create a new state and restore [l, r) to version v
    int new_version = versions.size();
    auto root = st_reset(*versions.rbegin(), 0, n_nodes - 1, l, r - 1, new_version, versions[v]);
    versions.push_back(root);
#ifdef DEBUG
    printf("Executed operation resetta(%d, %d, %d)\n", l, r, v);
    cout << "State " << new_version << "\n";
    print_st(*versions.rbegin());
#endif
}

long long somma (int l, int r) {
    // return the current sum in range [l, r)
    return st_sum(*versions.rbegin(), 0, n_nodes - 1, l, r - 1);
}
