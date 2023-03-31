#include <bits/stdc++.h>
#define MAXN 1000005
#define MAXSC 10000005
using namespace std;

int n_length, s_states, c_cell_values;
int cells[MAXN];
struct Transition {
    int new_state;
    int delta;
} transitions[MAXSC];
int dfs_state[MAXN];
enum Result {
    UNDECIDED,
    HALTS,
    LOOPS,
} memo[MAXN];

int state_to_node (int state, int pos) {
    return state * n_length + pos;
}

int input_to_trans (int state, int value) {
    return state * c_cell_values + value;
}

Result dfs (int state, int pos) {
    stack<pair<int, int>> ff;
    ff.push({ state, pos });
    Result res = memo[state_to_node(state, pos)];
    while (res == UNDECIDED) {
        dfs_state[state_to_node(state, pos)] = 1; // visiting
        auto transition = transitions[input_to_trans(state, cells[pos])];
        // printf("From [%d, %d] to [%d, %d]\n", state, pos, transition.new_state, pos + transition.delta);
        state = transition.new_state;
        pos += transition.delta;
        if (memo[state_to_node(state, pos)] != UNDECIDED) {
            res = memo[state_to_node(state, pos)];
        } else if (dfs_state[state_to_node(state, pos)] == 1) {
            // still visiting, found a loop
            res = LOOPS;
        } else {
            ff.push({ state, pos });
        }
    }

    while (!ff.empty()) {
        auto x = ff.top();
        ff.pop();
        state = x.first;
        pos = x.second;
        dfs_state[state_to_node(state, pos)] = 2; // visited
        memo[state_to_node(state, pos)] = res;
    }

    return memo[state_to_node(state, pos)];
}

int main () {
#ifndef DEBUG
    fstream cin, cout;
    cin.open("input.txt", ios::in);
    cout.open("output.txt", ios::out);
#endif
    cin >> n_length >> s_states >> c_cell_values;
    for (int i = 0; i < s_states * c_cell_values; i++) {
        int state, value, new_state, delta;
        cin >> state >> value >> new_state >> delta;
        transitions[input_to_trans(state, value)] = { new_state, delta };
    }
    for (int i = 0; i < n_length; i++) {
        cin >> cells[i];
    }
    for (int i = 0; i < s_states; i++) {
        memo[state_to_node(i, 0)] = HALTS;
    }

    vector<int> halt_states;
    for (int i = 0; i < n_length; i++) {
        int res = dfs(0, i);
        if (res == HALTS) {
            halt_states.push_back(i);
        }
    }

    cout << halt_states.size() << "\n";
    for (auto i: halt_states) {
        cout << i << "\n";
    }
}