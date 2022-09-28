#include <iostream>
#include <unordered_map>
#include <vector>
#pragma GCC optimize("O3")
#define MAXN 100005

using namespace std;

int n;
int parent[MAXN];
vector<int> graph[MAXN];
int color[MAXN];

struct NodeInfo {
    int x; // max freq
    int max_freq_am; // how many are colored this way
    unordered_map<int, int> freqs;
} node_infos[MAXN];

int sol = 0;

NodeInfo* count_freqs (int node) {
    // cout << "Visiting " << node << "\n";
    vector<NodeInfo*> children_info;
    for (auto i: graph[node]) {
        auto child_info = count_freqs(i);
        children_info.push_back(child_info);
    }

    NodeInfo* node_info = NULL;
    if (!children_info.empty()) {
        // find the largest map, small to large merging
        int best = 0;
        for (int i = 1; i < children_info.size(); i++) {
            if (children_info[i]->freqs.size() > children_info[best]->freqs.size()) {
                best = i;
            }
        }
        // copy the info from the child and update it
        node_info = children_info[best];
        for (int i = 0; i < children_info.size(); i++) {
            if (i != best) {
                // merge
                for (auto j: children_info[i]->freqs) {
                    node_info->freqs[j.first] += j.second;
                    // check if the frequency is now higher or equal
                    if (node_info->freqs[j.first] == node_info->x) {
                        // this improves our solution
                        node_info->max_freq_am++;
                    } else if (node_info->freqs[j.first] > node_info->x) {
                        // a new more frequent node was found
                        node_info->x = node_info->freqs[j.first];
                        node_info->max_freq_am = 1;
                    }
                }
            }
        }
    } else {
        node_info = &(node_infos[node]);
    }
    auto x = (node_info->freqs).begin();
    // if ((node_info->freqs).find(color[node]) == (node_info->freqs).end()) {
    //     node_info->freqs[color[node]] = 0;
    // }
    node_info->freqs[color[node]]++;
    if (node_info->freqs[color[node]] == node_info->x) {
        // this improves our solution
        node_info->max_freq_am++;
    } else if (node_info->freqs[color[node]] > node_info->x) {
        // a new more frequent node was found
        node_info->x = node_info->freqs[color[node]];
        node_info->max_freq_am = 1;
    }
    sol = max(sol, node_info->max_freq_am);

#ifdef DEBUG
    cout << node << ", x = " << node_info->x << ", max_freq_am = " << node_info->max_freq_am << "\n";
    for (auto j: node_info->freqs) {
        cout << j.first << ": " << j.second << "\n";
    }
    cout << "\n";
#endif
    return node_info;
}

int main () {
#ifndef DEBUG
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
#endif

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> color[i];
    }
    for (int i = 1; i < n; i++) {
        cin >> parent[i];
        graph[parent[i]].push_back(i);
    }

    count_freqs(0);
    cout << sol << "\n";
}
