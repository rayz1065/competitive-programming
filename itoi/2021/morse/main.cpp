#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define MAXN 4005
#define MAXM 4005
#define MOD 1000000007

using namespace std;

int n, m;
int memo[MAXN];
char message[MAXN];
char mappings[MAXM][MAXN];

struct TrieNode {
    TrieNode** children;
    bool is_end;
    char *lazy_str;
} *trie_root;
int solve (int i);

void trie_add (TrieNode *node, char *str) {
    if (*str == '\0') {
        node->is_end = true;
        return ;
    }
    if (node->children != NULL) {
        int nxt = *str - 'a';
        if (node->children[nxt] == NULL) {
            node->children[nxt] = new TrieNode();
        }
        trie_add(node->children[nxt], str + 1);
    } else if (node->lazy_str) {
        if (node->children == NULL) {
            node->children = new TrieNode*[26];
        }
        char *lazy_str = node->lazy_str;
        node->lazy_str = NULL;
        trie_add(node, lazy_str);
        trie_add(node, str);
    } else {
        node->lazy_str = str;
    }
}

int trie_visit (TrieNode *node, int i) {
    int s = 0;
    if (node->is_end) {
        s += solve(i);
    }
    if (i == n) {
        return s;
    }
    int nxt = message[i] - 'a';
    if (node->children != NULL && node->children[nxt] != NULL) {
        s += trie_visit(node->children[nxt], i + 1);
    } else if (node->lazy_str) {
        int rem_chars = strlen(node->lazy_str);
        if (strncmp(node->lazy_str, message + i, rem_chars) == 0) {
            s += solve(i + rem_chars);
        }
    }
    return s % MOD;
}

int solve (int i) {
    if (i == n) {
        return 1;
    }
    if (memo[i] != -1) {
        return memo[i];
    }
    int s = trie_visit(trie_root, i);
    return memo[i] = s;
}

int main () {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> m;
    cin >> message;
    trie_root = new TrieNode();
    for (int i = 0; i < m; i++) {
        cin >> mappings[i];
        trie_add(trie_root, mappings[i]);
    }
    fill(memo, memo + n, -1);
    cout << solve(0) << "\n";
}
