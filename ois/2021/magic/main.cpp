#include <bits/stdc++.h>
#define MAXL 20
#define MAXN 215

using namespace std;

int n_len, m_nodes;
int nodes[MAXL];
bool is_fixed[MAXL];
int nodes_pos[MAXN];
int nodes_magic[MAXN];
short memo[MAXL][10500000];

bool nhm[11][11];
int num_map[11][11]; // for len = l replace i with x[l][i]
int original_number[11][11]; // what number does the replacement map to
int mapping_size[11]; // how many numbers are needed to encode this distance?

// int repln (int n, int a, int b) {
//     vector<int> digits;
//     for (; n > 0; n /= 10) {
//         digits.push_back(n % 10);
//     }
//     int s = 0;
//     for (int i = digits.size() - 1; i >= 0; i--) {
//         if (digits[i] == a) digits[i] = b;
//         s = s * 10 + digits[i];
//     }
//     return s;
// }

// void compute_nhm () {
//     for (int i = 9; i >= 1; i--) {
//         for (int j = 1; j <= 9; j++) {
//             nhm[i][j] = i % j == 0 || j % i == 0 || nhm[i + 1][j];
//         }
//     }
// }

int enc_nodes (int i, int max_num) {
    int s = 0;
    for (int j = max_num; j >= 1; j--) {
        if (i - j >= 0) {
            s *= mapping_size[j];
            int k = nodes[i - j];
            k = num_map[j][k];
            s += k;
        }
    }
    return s;
}

int enc_nodes (int i) {
    return enc_nodes(i, 9);
}

bool valid_comb (int l, int activated_by) {
    return activated_by % l == 0 || l % activated_by == 0;
}

int solve (int i) {
    if (i == n_len) return 0;
    int hsh = enc_nodes(i);
    if (memo[i][hsh] != 0) return memo[i][hsh];
    if (nodes[i]) return memo[i][hsh] = solve(i + 1) + nodes[i];

    int s = 0;
    for (int j = 9; j >= 1; j--) {
        if (i - j >= 0 && valid_comb(j, nodes[i - j])) {
            nodes[i] = j;
            s = max(s, solve(i + 1) + j);
            nodes[i] = 0;
            // if (n_len > 15 && i > 11) {
            //     return memo[i][hsh] = s;
            // }
        }
    }
    return memo[i][hsh] = s;
}

void find_sol (int i, vector<int> &sol) {
    if (i == n_len) return ;
    if (nodes[i]) {
        sol.push_back(nodes[i]);
        find_sol(i + 1, sol);
        return ;
    }
    int s = solve(i);
    for (int j = 1; j <= 9; j++) {
        if (i - j >= 0 && valid_comb(j, nodes[i - j])) {
            nodes[i] = j;
            if (s == solve(i + 1) + j) {
                sol.push_back(nodes[i]);
                find_sol(i + 1, sol);
                nodes[i] = 0;
                return ;
            }
            nodes[i] = 0;
        }
    }
    cout << "for i = " << i << ", hash = " << enc_nodes(i) << " no solution\n";
    for (int j = 9; j >= 1; j--) {
        cout << nodes[i - j] << " ";
    }
    cout << "\n";
    cout << "Expected solution: " << s << "\n";
    exit(1);
    assert(false);
}

int sum (vector<int> &x) {
    int s = 0;
    for (auto i: x) s += i;
    return s;
}

bool behaves_like (int l, int i, int j) {
    if (l == 0) {
        return false;
    }
    for (; l <= 9; l++) {
        if (valid_comb(l, i) != valid_comb(l, j)) {
            return false;
        }
    }
    return true;
}

void compute_replacements () {
    for (int i = 1; i <= 9; i++) {
        num_map[0][i] = i;
    }
    for (int l = 1; l <= 9; l++) {
        for (int i = 1; i <= 9; i++) {
            num_map[l][i] = num_map[l - 1][i];
        }
        for (int i = 1; i <= 9; i++) {
            if (num_map[l][i] != i) continue ; // already found
            for (int j = 9; j > i; j--) {
                if (num_map[l][j] == j && behaves_like(l, i, j)) {
                    num_map[l][i] = j; // same behavior
                    break ;
                }
            }
        }
    }
    for (int i = 1; i <= 9; i++) {
        for (int l = 1; l <= 9; l++) {
            while (num_map[l][num_map[l][i]] != num_map[l][i]) {
                // merge
                num_map[l][i] = num_map[l][num_map[l][i]];
            }
        }
    }
    for (int l = 1; l <= 9; l++) {
        for (int i = 9; i >= 1; i--) {
            // flatten
            if (i != num_map[l][i]) {
                // already remapped
                num_map[l][i] = num_map[l][num_map[l][i]];
            } else {
                // needs to be mapped
                num_map[l][i] = mapping_size[l]++;
                original_number[l][num_map[l][i]] = i;
            }
        }
    }
}

int main () {
    // for (nodes[0] = 1; nodes[0] < 10; nodes[0]++) {
    //     cout << nodes[0] << "  ";
    //     for (int i = 1; i <= 9; i++) {
    //         cout << (valid_comb(i, nodes[0]) ? (char)(i + '0') : '-');
    //     }
    //     cout << "\n";
    // }
    compute_replacements();
    // compute_nhm();

    cin >> m_nodes >> n_len;
    for (int i = 0; i < m_nodes; i++) {
        cin >> nodes_pos[i];
        is_fixed[nodes_pos[i]] = true;
    }
    for (int i = 0; i < m_nodes; i++) {
        cin >> nodes_magic[i];
        nodes[nodes_pos[i]] = nodes_magic[i];
    }
    vector<int> s;
    find_sol(0, s);
#ifdef DEBUG
    cout << sum(s) << "\n";
#endif
    for (auto j: s) {
        cout << j << " ";
    }
    cout << "\n";
#ifdef DEBUG
    for (int i = 0; i < n_len; i++) {
        // set<int> possible_values;
        // for (auto j: memo[i]) {
        //     possible_values.insert(j.second);
        // }
        // cout << memo[i].size() << " -> " << possible_values.size() << "\t";
        // for (auto j: possible_values) {
        //     cout << j << " (";
        //     bool first = true;
        //     for (auto k: memo[i]) {
        //         if (k.second == j) {
        //             if (!first) cout << ", ";
        //             first = false;
        //             cout << k.first;
        //         }
        //     }
        //     cout << ")\t";
        // }
        cout << "\n";
    }
#endif
}
