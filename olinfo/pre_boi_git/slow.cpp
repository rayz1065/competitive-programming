#include <bits/stdc++.h>
#define MAXN 100005
using namespace std;

int n_nodes;
int state_idx;
long long states[100][MAXN];

void print_state () {
    cout << "State " << state_idx << "\n";
    for (int i = 0; i < n_nodes; i++) {
        cout << states[state_idx][i] << " \n"[i + 1 == n_nodes];
    }
}

void inizia (int N, vector<int> A) {
    ::n_nodes = N;
    state_idx = 0;
    for (int i = 0; i < n_nodes; i++) {
        states[0][i] = A[i];
    }
#ifdef DEBUG
    print_state();
#endif
}

void incrementa (int l, int r, int x) {
    state_idx++;
    for (int i = 0; i < n_nodes; i++) {
        states[state_idx][i] = states[state_idx - 1][i];
    }
    for (int i = l; i < r; i++) {
        // create a new state
        states[state_idx][i] += x;
    }
#ifdef DEBUG
    printf("Executed operation incrementa(%d, %d, %d)\n", l, r, x);
    print_state();
#endif
}

void resetta (int l, int r, int v) {
    state_idx++;
    for (int i = 0; i < n_nodes; i++) {
        states[state_idx][i] = states[state_idx - 1][i];
    }
    for (int i = l; i < r; i++) {
        // create a new state
        states[state_idx][i] = states[v][i];
    }
#ifdef DEBUG
    printf("Executed operation resetta(%d, %d, %d)\n", l, r, v);
    print_state();
#endif
}

long long somma (int l, int r) {
    long long s = 0;
    for (int i = l; i < r; i++) {
        s += states[state_idx][i];
    }
    return s;
}
