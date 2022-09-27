#include <bits/stdc++.h>

#define MAXN 100005
#define ALF 26

using namespace std;

int n_flavors;
string flavors[MAXN];
int sol[MAXN];
int future_common_prefix[MAXN];

typedef struct TrieNode {
    TrieNode *others;
    bool is_end;
    bool counted;
    int lazy_flavor_id;
} TrieNode;

int build_trie (TrieNode &curr, int flavor_id, int depth) {
    if (flavors[flavor_id].size() == depth) {
        // reached the end
        curr.is_end = true;
        return depth;
    }
    // is there any ambiguity?
    if (curr.others == nullptr && curr.lazy_flavor_id == -1 && !curr.is_end) {
        // no ambiguity
        curr.lazy_flavor_id = flavor_id;
        return depth;
    }
    // need to split it up further...
    if (curr.others == nullptr) {
        curr.others = new TrieNode[ALF];
        for (int j = 0; j < ALF; j++) {
            curr.others[j] = { nullptr, 0, 0, -1 };
        }
    }
    if (curr.lazy_flavor_id != -1) {
        // move the lazy flavor further down
        int lazy_flavor_id = curr.lazy_flavor_id;
        curr.lazy_flavor_id = -1;
        build_trie(curr, lazy_flavor_id, depth);
    }
    // this should go to...
    int dest_j = flavors[flavor_id][depth] - 'a';
    return build_trie(curr.others[dest_j], flavor_id, depth + 1);
}

TrieNode *find_node (TrieNode *node, int flavor_id, int to_depth) {
    // find the node after depth iterations
    for (int depth = 0; depth < to_depth; depth++) {
        int dest_j = flavors[flavor_id][depth] - 'a';
        node = &(node->others[dest_j]);
    }
    return node;
}

int trie_clear (TrieNode &node, bool clear_first) {
    // clears all of the flavors and keeps a tally
    int s = 0;

    if (!clear_first) {
        // this prefix counts for all the further prefixes
        node.counted = true;
        s+= 1;
    } else if (node.counted) {
        node.counted = false;
        s-= 1;
    }

    if (node.others != nullptr) {
        for (int j = 0; j < ALF; j++) {
            s+= trie_clear(node.others[j], true);
        }
    }
    return s;
}

int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n_flavors;

    for (int i = 0; i < n_flavors; i++){
        cin >> flavors[i];
    }

    // construct the trie from the last element
    TrieNode trie_root = { nullptr, 0, 0, -1 };
    for (int i = n_flavors - 1; i >= 0; i--) {
        future_common_prefix[i] = max(1, build_trie(trie_root, i, 0));
    }

    // visit the trie keeping a tally
    int s = 0;
    for (int i = 0; i < n_flavors; i++) {
        // add this flavor
        TrieNode *node = find_node(&trie_root, i, future_common_prefix[i]);
        // printf("is_end = %d, lazy = %d\n", node.is_end, node.lazy_flavor_id);
        int diff = trie_clear(*node, false);
        s+= diff;
        sol[i] = s;
    }

    // print the result
    for (int i = 0; i < n_flavors; i++) {
        cout << sol[i] << '\n'; 
    }
    
    return 0;
}
