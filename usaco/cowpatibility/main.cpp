#include <bits/stdc++.h>
#define MAXN 50005

using namespace std;

typedef long long ll;

const int preferences_count = 5;

int preferences[MAXN][preferences_count];

struct TrieNode {
    map<int, int> children;
    int count;
} nodes[MAXN * (1 << preferences_count) + 5];
int nodes_count;

int get_node_idx(int curr, int flavor) {
    auto res = nodes[curr].children.find(flavor);

    if (res != nodes[curr].children.end()) {
        return res->second;
    }

    int nxt = nodes_count++;
    nodes[curr].children[flavor] = nxt;
    return nxt;
}

void add_cow(int cow_idx, int flavor_idx, int curr) {
    nodes[curr].count += 1;
    for (int j = flavor_idx; j < preferences_count; j++) {
        int nxt = get_node_idx(curr, preferences[cow_idx][j]);
        add_cow(cow_idx, j + 1, nxt);
    }
}

void print_trie(int curr, vector<int> &stack) {
    for (auto j : stack) cerr << j << " ";
    cerr << ":\t" << nodes[curr].count << "\n";
    for (auto j : nodes[curr].children) {
        stack.push_back(j.first);
        print_trie(j.second, stack);
        stack.pop_back();
    }
}

ll include_exclude(int curr) {
    ll res = (ll)nodes[curr].count * (nodes[curr].count - 1) / 2;

    for (auto j : nodes[curr].children) {
        res -= include_exclude(j.second);
    }

    return res;
}

int main() {
#ifndef DEBUG
    fstream cin, cout;
    cin.open("cowpatibility.in", ios::in);
    cout.open("cowpatibility.out", ios::out);
#endif
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < preferences_count; j++) {
            cin >> preferences[i][j];
        }
        sort(preferences[i], preferences[i] + preferences_count);
    }

    nodes_count = 1;
    for (int i = 0; i < n; i++) {
        add_cow(i, 0, 0);
    }

    cout << include_exclude(0) << "\n";
}
