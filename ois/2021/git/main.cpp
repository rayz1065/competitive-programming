#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;

struct Node {
    bool has_changes = false;
    bool has_unchanged = false;
    map<string, int> children;
};

int next_node_idx = 0;
Node nodes[500005];

void tree_update (int node_idx, vector<string> &segments, int i, bool changed) {
    // cout << "Visiting " << node_idx << "\n";
    if (changed) {
        nodes[node_idx].has_changes = true;
    }
    if (i < segments.size()) {
        if (!changed) {
            nodes[node_idx].has_unchanged = true;
        }
        if (nodes[node_idx].children.find(segments[i]) == nodes[node_idx].children.end()) {
            int child_idx = next_node_idx++;
            // cout << "Created a new node " << child_idx << " for " << segments[i] << "\n";
            nodes[node_idx].children[segments[i]] = child_idx;
            // for (auto j: nodes[node_idx].children) {
            //     cout << j.first << " -> " << j.second << ", ";
            // }
            // cout << "\n";
        }
        // cout << "Now i will visit " << nodes[node_idx].children[segments[i]] << "\n";
        tree_update(nodes[node_idx].children[segments[i]], segments, i + 1, changed);
    }
}

void print_tree (Node node, vector<string> &curr_path) {
    if (!node.has_changes) {
        return ;
    }
    if (!node.has_unchanged) {
        cout << '/';
        bool first = true;
        for (auto j: curr_path) {
            if (!first) {
                cout << '/';
            }
            first = false;
            cout << j;
        }
        cout << "\n";
        return ;
    }
    for (auto child: node.children) {
        curr_path.push_back(child.first);
        print_tree(nodes[child.second], curr_path);
        curr_path.pop_back();
    }
}

vector<string> split (string path) {
    vector<string> s;
    string curr;

    for (int i = 1; i < path.length(); i++) {
        if (path[i] == '/') {
            s.push_back(curr);
            curr = "";
        } else {
            curr += path[i];
        }
    }
    s.push_back(curr);
    return s;
}

int main () {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    next_node_idx++;

    for (int i = 0; i < n; i++) {
        bool changed;
        string path;
        cin >> changed >> path;
        vector<string> segments = split(path);
        tree_update(0, segments, 0, changed);
    }

    vector<string> curr_path;
    print_tree(nodes[0], curr_path);
}