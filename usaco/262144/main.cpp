#include <bits/stdc++.h>
#define MAXN 263000

using namespace std;

int n;
int values[MAXN];

struct Node {
    int left;
    int right;
    int value;
    int freq;
} nodes[MAXN];
vector<int> free_indexes;

void merge(int i) {
    int left = nodes[i].left, right = nodes[i].right;

    if (left != -1 && nodes[left].value == nodes[i].value) {
        // merge
        free_indexes.push_back(left);
        nodes[i].left = nodes[left].left;
        nodes[i].freq += nodes[left].freq;
        nodes[left] = {-1, -1, -1, -1};
        left = nodes[i].left;
        if (left != -1) {
            nodes[left].right = i;
        }
    }

    if (right != -1 && nodes[right].value == nodes[i].value) {
        // merge
        free_indexes.push_back(right);
        nodes[i].right = nodes[right].right;
        nodes[i].freq += nodes[right].freq;
        nodes[right] = {-1, -1, -1, -1};
        right = nodes[i].right;
        if (right != -1) {
            nodes[right].left = i;
        }
    }
}

void sweep(int value) {
    for (int i = 0; i < n; i++) {
        if (nodes[i].freq <= 1 || nodes[i].value != value) {
            continue;
        }

        if (nodes[i].freq % 2 == 0) {
            // cerr << "merging node " << i << " with freq " << nodes[i].freq
            //      << "\n";
            nodes[i].freq /= 2;
            nodes[i].value += 1;

            merge(i);
        } else {
            // cerr << "merging node " << i << " with freq " << nodes[i].freq
            //      << "\n";
            int free = free_indexes.back();
            free_indexes.pop_back();

            int left = nodes[i].left;
            int right = nodes[i].right;

            nodes[free] = {left, -1, nodes[i].value + 1, nodes[i].freq / 2};
            nodes[i] = {-1, right, nodes[i].value + 1, nodes[i].freq / 2};

            merge(i);
            merge(free);
        }
    }
}

int main() {
#ifndef DEBUG
    fstream cin, cout;
    cin.open("262144.in", ios::in);
    cout.open("262144.out", ios::out);
#endif
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> values[i];
        nodes[i] = {-1, -1, -1, -1};
    }

    int n_nodes = 1;
    nodes[n_nodes - 1] = {-1, -1, values[0], 0};

    for (int i = 0; i < n; i++) {
        if (nodes[n_nodes - 1].value != values[i]) {
            nodes[n_nodes - 1].right = n_nodes;
            n_nodes += 1;
            nodes[n_nodes - 1] = {n_nodes - 2, -1, values[i], 0};
        }

        nodes[n_nodes - 1].freq += 1;
    }

    for (int i = n_nodes; i < n; i++) {
        free_indexes.push_back(i);
    }

    for (int i = 1; i < 40; i++) {
        sweep(i);
    }

    int best = 0;

    for (int i = 0; i < n; i++) {
        if (nodes[i].value == -1) {
            continue;
        }

        int value = nodes[i].value, freq = nodes[i].freq;
        while (freq > 1) {
            freq /= 2;
            value += 1;
        }

        best = max(value, best);
    }

    cout << best << "\n";
}
